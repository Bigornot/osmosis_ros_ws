//July2017 J.Guiochet @ LAAS with cc/paste from C.Lesire @ ONERA
#include <osmosis_control/osmosisControl.hpp>

////////////////////// PRIVATE //////////////////////

void OsmosisControl::osmosisControlFSM()
{
	switch(state_)
	{
		case WAIT_GOAL:
			ROS_INFO("WAIT\n");
			stop();
			if(new_goal())
				state_=MOVE_TO_GOAL;
			if(emergency_stop_)
			{
				stop();
				state_=EMERGENCY_STOP;
			}
			break;

		case MOVE_TO_GOAL:
			ROS_INFO("MOVE\n");
			ROS_INFO("x: %f  y:%f", robot_pose.x , robot_pose.y );
			if (new_goal())
				state_=MOVE_TO_GOAL;
			else if (is_arrived())
				state_=ARRIVED_GOAL;
			else
				updateMove();
			if(emergency_stop_)
			{
				stop();
				state_=EMERGENCY_STOP;
			}
			break;

		case ARRIVED_GOAL:
			ROS_INFO("ARRIVED\n");
			publish_is_arrived();
			stop();
			state_=WAIT_GOAL;
			if(emergency_stop_)
			{
				stop();
				state_=EMERGENCY_STOP;
			}
			break;

		case EMERGENCY_STOP:
			ROS_INFO("EMERGENCY_STOP\n");
			if(!emergency_stop_)
				state_=WAIT_GOAL;
			break;

		default: break;
	}
}

bool OsmosisControl::new_goal()
{
	bool new_goal=false;
	if (fabs(target_.point.x-old_goal_.x)>0.1 || fabs(target_.point.y-old_goal_.y)>0.1)
	{
		new_goal = true;
		old_goal_=target_.point;
	}
	return new_goal;
}

bool OsmosisControl::is_arrived()
{
	double xPos = robot_pose.x - target_.point.x;
	double yPos = robot_pose.y - target_.point.y;
	bool is_arrived = false;

	if (sqrt( pow(xPos,2) + pow(yPos,2) ) < 0.2)
		is_arrived = true;
	return is_arrived;
}

void OsmosisControl::stop()
{
	cmd_.linear.x=0;
	cmd_.linear.y=0;
	cmd_.angular.x=0;
	cmd_.angular.y=0;
	cmd_.angular.z=0;
}

void OsmosisControl::updateMove()
{
	geometry_msgs::Twist cmd; //0,0

	// if no obstacle or taxi mode on -> avoid
	if(!obstacleFromScan(scan_) || target_.taxi)
	{
		double xPos = robot_pose.x - target_.point.x;
		double yPos = robot_pose.y - target_.point.y;
		double wPos = robot_pose.theta;
		if ( wPos < 0) wPos += 2 * M_PI;
		double obs_dist = sqrt(pow(obstacle.x,2) + pow(obstacle.y,2));
		double obsG_x = (xPos) + obs_dist*cos(wPos + obstacle_lw);
		double obsG_y = (yPos) + obs_dist*sin(wPos + obstacle_lw);

		ROS_INFO("Ob_X: %f",obsG_x);
		ROS_INFO("Ob_Y: %f",obsG_y);
		cmd = PF(xPos,yPos,wPos,obsG_x,obsG_y);
	}
	cmd_=cmd;
}

bool OsmosisControl::obstacleFromScan(const sensor_msgs::LaserScan& scan)
{
	bool obs=false;

	double xmin = numeric_limits<double>::max();
	double xmax = numeric_limits<double>::min();
	double ymin = numeric_limits<double>::max();
	double ymax = numeric_limits<double>::min();
	double far = obstacle_distance;

	for (int i = 0; i < scan.ranges.size(); i++)
	{
		//if (scan.ranges[i] < scan.range_min) continue; //avoid use of continue see below
		if (scan.ranges[i] >= scan.range_min)
		{
			if (scan.ranges[i] <= far)
			{
				obs=true;

				double dist = scan.ranges[i];
				double ang = scan.angle_min + (scan.angle_max - scan.angle_min) * i / scan.ranges.size();
				double px = dist * cos(ang);
				double py = dist * sin(ang);
				if (px < xmin) xmin = px;
				if (px > xmax) xmax = px;
				if (py < ymin) ymin = py;
				if (py > ymax) ymax = py;
			}
		}
	}
	obstacle.x = xmin;
	obstacle.y = ymin;
	obstacle_lw = atan2(obstacle.y, obstacle.x);

	return obs;
}

//Potential Field Algo
geometry_msgs::Twist OsmosisControl::PF(double x_p, double y_p,double theta_p, double obs_dx, double obs_dy)
{
	geometry_msgs::Twist control;

	double nu = nu;
	double dist_safe = safety_distance;
	double Psi = psi;

	//Collision Avoidance gains and parameters
	double Fatt1=0, Fatt2=0;
	double Frep1=0, Frep2=0;
	double F1, F2;
	double epsilon = 0.11;
	double V1=0, V2=0;
	double alpharep=4;
	double umax = 1.0;
	double wmax = 1.0;

	if (theta_p < -M_PI)
		theta_p = theta_p + 2*M_PI;
	else if (theta_p >M_PI)
		theta_p = theta_p - 2*M_PI;

	double dist_g = sqrt(pow(x_p,2)+pow(y_p,2));

	double dist = sqrt(pow((x_p-obs_dx),2)+pow((y_p-obs_dy),2));

	///////// attractive force
	if (dist_g <= nu)
	{
		Fatt1 = -2*x_p;
		Fatt2 = -2*y_p;
	}
	if (dist_g > Psi)
	{
		Fatt1 = -x_p/dist_g;
		Fatt2 = -y_p/dist_g;
	}

	///////// repulsive force
	if (dist < dist_safe)
	{
		double value = pow(dist_safe,2) - pow(dist,2);
		Frep1 = 4 * alpharep*fmax(0,value)*(x_p-obs_dx);
		Frep2 = 4*alpharep*fmax(0,value)*(y_p-obs_dy);
	}
	///////// composition
	F1 = Fatt1 +Frep1;
	F2 = Fatt2 +Frep2;
	///////// Eventual V
	if (sqrt(pow(F1,2)+pow(F2,2)) <= epsilon)
	{
		double rho = y_p - (obs_dy/obs_dx) * x_p;
		int s = sign(rho);
		V1 = ( (s*epsilon) / dist_g ) * y_p;
		V2 = ( (s*epsilon) / dist_g ) * (-x_p);
	}
	/////////
	F1 = Fatt1 + Frep1 - V1;
	F2 = Fatt2 + Frep2 - V2;

	double theta_d = atan2(F2,F1);
	double err = theta_d - theta_p;
	if (err < -M_PI)
		err = err + 2*M_PI;
	else if (err > M_PI)
		err = err - 2*M_PI;
	int s = sign(err);

	control.angular.z = wmax * sqrt(fabs(err)) * s;
	control.linear.x = (umax / (1+epsilon)) * (sqrt(pow(F1,2)+pow(F2,2)));

	return control;
}

void OsmosisControl::publish_is_arrived()
{
	std_msgs::Bool a;
	a.data=true;
	goal_reach_pub_.publish(a);
}


////////////////////// PUBLIC //////////////////////

OsmosisControl::OsmosisControl()
{
	//set up the publishers and subscribers
	cmd_vel_pub_   = nh_.advertise<geometry_msgs::Twist>("cmd_vel_control", 1);
	goal_reach_pub_= nh_.advertise<std_msgs::Bool>("target_reached", 10);
	scan_sub_ = nh_.subscribe("/summit_xl_a/front_laser/scan", 1, &OsmosisControl::callbackScan, this);
	goal_sub_ = nh_.subscribe("/target", 1, &OsmosisControl::callbackGoal, this);
	odom_sub_ = nh_.subscribe("/pose", 1, &OsmosisControl::callbackPose, this);
	emergency_stop_sub_ = nh_.subscribe("/do_emergency_stop", 1, &OsmosisControl::callbackEmergencyStop, this);

	//initialization of attributes
	target_.point.x = old_goal_.x =target_.point.y = old_goal_.y=0;
	state_=WAIT_GOAL;
	emergency_stop_=false;
	freq_=10;
}

bool OsmosisControl::run()
{
	ros::Rate loop_rate(freq_); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo
	while (nh_.ok())
	{
		osmosisControlFSM();
		cmd_vel_pub_.publish(cmd_);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}

	return true;
}

void OsmosisControl::callbackGoal(const osmosis_control::GoalMsg & thegoal)
{
	target_=thegoal;
	ROS_INFO("GOAL : x: [%f], y:[%f]",target_.point.x,target_.point.y);
}

void OsmosisControl::callbackScan(const sensor_msgs::LaserScan & thescan)
{
	scan_=thescan;
}

void OsmosisControl::callbackPose(const geometry_msgs::Pose2D & msg)
{
	robot_pose = msg;
}

void OsmosisControl::callbackEmergencyStop(const std_msgs::Bool &emergency_stop)
{
	emergency_stop_=emergency_stop.data;
}

////////////////////// MAIN //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "osmosis_control_node");
	OsmosisControl myOsmosisControl;
	//launch the control node
	myOsmosisControl.run();
}
