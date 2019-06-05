//July2017 J.Guiochet @ LAAS with cc/paste from C.Lesire @ ONERA
#include <osmosis_control/osmosisControl.hpp>


void OsmosisControl::osmosisControlCallbackGoal(const geometry_msgs::Point & thegoal)
	{
	  this->goal=thegoal;
	 ROS_INFO("GOAL : x: [%f], y:[%f]",goal.x,goal.y);
	}


void OsmosisControl::osmosisControlCallbackScan(const sensor_msgs::LaserScan & thescan)
	{
	  this->scan_=thescan;
	}

void OsmosisControl::osmosisControlCallbackPose(const geometry_msgs::Pose2D & msg)
	{
	this->robot_pose = msg;
	}

void OsmosisControl::publish_is_arrived()
{
	std_msgs::Bool a;
	a.data=true;
	goal_reach_pub_.publish(a);
}

//! ROS node initialization
  OsmosisControl::OsmosisControl()
  {

	//set up the publishers and subscribers
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel_control", 1);
	goal_reach_pub_=nh_.advertise<std_msgs::Bool>("target_reached", 10);
	scan_sub_  = nh_.subscribe("/summit_xl_a/front_laser/scan", 1, &OsmosisControl::osmosisControlCallbackScan, this);
	goal_sub_=nh_.subscribe("/target", 1, &OsmosisControl::osmosisControlCallbackGoal, this);
	odom_sub_=nh_.subscribe("/pose", 1, &OsmosisControl::osmosisControlCallbackPose, this);

	//initialization of attributes
	goal.x = old_goal_.x = goal.y = old_goal_.y=0;
	state_=wait_goal;
  }

// paste from MAUVE

bool OsmosisControl::new_goal() {
    //auto g = shell().goal.read();
    //logger().debug("Current goal {}", g);
    bool new_goal=false;
    //if (g.status == runtime::DataStatus::NEW_DATA) {
	//ROS_INFO("delta goal en x[%f]",fabs(goal.x-old_goal_.x));
	if (fabs(goal.x-old_goal_.x)>0.1 || fabs(goal.y-old_goal_.y)>0.1)
      		{
		//goal = g.value;
	      //logger().info("Received new goal {}", goal);
	      	new_goal = true;
		old_goal_=goal;
    		}
    return new_goal;

  }


bool OsmosisControl::is_arrived()
{
  double xPos = robot_pose.x - goal.x;
  double yPos = robot_pose.y - goal.y;
  bool is_arrived = false;

   if (sqrt( pow(xPos,2) + pow(yPos,2) ) < 0.2) {
      //logger().info("Arrived at goal {}", goal);
      is_arrived = true;
    }
   return is_arrived;
}




  void OsmosisControl::stop() {
    //shell().command.write({0, 0});

	cmd_.linear.x=0;
	cmd_.linear.y=0;
	cmd_.angular.x=0;
	cmd_.angular.y=0;
	cmd_.angular.z=0;

  }

  void OsmosisControl::updateMove() {

	//robot_pose = shell().pose.read();

	obstacleFromScan(scan_);

    double xPos = robot_pose.x - goal.x;
    double yPos = robot_pose.y - goal.y;
    double wPos = robot_pose.theta;
    if ( wPos < 0) wPos += 2 * M_PI;

    double obs_dist = sqrt(pow(obstacle.x,2) + pow(obstacle.y,2));
   // logger().debug("obstacle {} distance: {}", obstacle, obs_dist);

   // _arrived = false;
    geometry_msgs::Twist cmd; //0,0

  //  if (sqrt( pow(xPos,2) + pow(yPos,2) ) < 0.2) {
      //logger().info("Arrived at goal {}", goal);
  //    _arrived = true;
   // }
   // else {
      double obsG_x = (xPos) + obs_dist*cos(wPos + obstacle_lw);
      double obsG_y = (yPos) + obs_dist*sin(wPos + obstacle_lw);
      cmd = PF(xPos,yPos,wPos,obsG_x,obsG_y);
      //logger().debug("command: {}", cmd);
    //}

   // shell().command.write(cmd);
this->cmd_=cmd;
  }


void OsmosisControl::obstacleFromScan(const sensor_msgs::LaserScan& scan) {
    double xmin = std::numeric_limits<double>::max();
    double xmax = std::numeric_limits<double>::min();
    double ymin = std::numeric_limits<double>::max();
    double ymax = std::numeric_limits<double>::min();

    double far = obstacle_distance;

    for (int i = 0; i < scan.ranges.size(); i++)
	{
      //if (scan.ranges[i] < scan.range_min) continue; //avoid use of continue see below
	if (scan.ranges[i] >= scan.range_min)
	  {
      	  if (scan.ranges[i] <= far) {
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
  }

//Potential Field Algo
geometry_msgs::Twist OsmosisControl::PF(double x_p, double y_p,
    double theta_p, double obs_dx, double obs_dy)
  {
    geometry_msgs::Twist control;

   // double nu = this->nu.get();
   // double dist_safe = this->safety_distance.get();
   // double Psi = this->psi.get();
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
  //  logger().debug("dist_g = {}", dist_g);
  //  shell().distance_to_goal.write(dist_g);

    double dist = sqrt(pow((x_p-obs_dx),2)+pow((y_p-obs_dy),2));
  //  logger().debug("dist = {}", dist);

    ///////// attractive force
    if (dist_g <= nu) {
      Fatt1 = -2*x_p;
      Fatt2 = -2*y_p;
     // logger().debug("vicino Fatt1={} Fatt2={}", Fatt1, Fatt2);
    }
    if (dist_g > Psi) {
      Fatt1 = -x_p/dist_g;
      Fatt2 = -y_p/dist_g;
     // logger().debug("lontano Fatt1={}, Fatt2={}", Fatt1, Fatt2);
    }

    ///////// repulsive force
    if (dist < dist_safe) {
      double value = pow(dist_safe,2) - pow(dist,2);
    	Frep1 = 4 * alpharep*fmax(0,value)*(x_p-obs_dx);
    	Frep2 = 4*alpharep*fmax(0,value)*(y_p-obs_dy);
     // logger().debug("Frep1={}, Frep2={}", Frep1, Frep2);
    }
    ///////// composition
    F1 = Fatt1 +Frep1;
    F2 = Fatt2 +Frep2;
    ///////// Eventual V
    if (sqrt(pow(F1,2)+pow(F2,2)) <= epsilon) {
    	double rho = y_p - (obs_dy/obs_dx) * x_p;
      int s = sign(rho);
    	V1 = ( (s*epsilon) / dist_g ) * y_p;
    	V2 = ( (s*epsilon) / dist_g ) * (-x_p);
    }
    /////////
    F1 = Fatt1 + Frep1 - V1;
    F2 = Fatt2 + Frep2 - V2;

    double theta_d = atan2(F2,F1);
  //  logger().debug("theta_d={}", theta_d);
    double err = theta_d - theta_p;
  //  logger().debug("err={}", err);
    if (err < -M_PI)
      err = err + 2*M_PI;
    else if (err > M_PI)
      err = err - 2*M_PI;
   // logger().debug("dopo err={}", err);
    int s = sign(err);

    control.angular.z = wmax * sqrt(fabs(err)) * s;
    control.linear.x = (umax / (1+epsilon)) * (sqrt(pow(F1,2)+pow(F2,2)));

    return control;
  }


// end paste




void OsmosisControl::osmosisControlFSM()
	{

	State current_state=state_;
	switch (current_state)
		{
		case wait_goal:
				//ROS_INFO("WAIT");
				stop();
				if (new_goal()) current_state=move_to_goal;
				break;
		case move_to_goal:
				ROS_INFO("MOVE");
				ROS_INFO("x: %f  y:%f", this->robot_pose.x , this->robot_pose.y );
				if (new_goal()) current_state=move_to_goal;
				else if (is_arrived()) current_state=arrived_goal;
							else updateMove();
				break;
		case arrived_goal:
				ROS_INFO("ARRIVED");
				publish_is_arrived();
				stop();
				current_state=wait_goal;
				break;
		default : break;

		}
	state_=current_state;
	}


	bool OsmosisControl::run()
	{
		ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo
		while (nh_.ok())
		    {
			//std::cout <<"HEY";
			this->osmosisControlFSM();
			cmd_vel_pub_.publish(cmd_);
		 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
			loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
		    }

		return true;
	}


int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "osmosis_control_node");
	OsmosisControl myOsmosisControl;
	//launch the control node
	myOsmosisControl.run();
}