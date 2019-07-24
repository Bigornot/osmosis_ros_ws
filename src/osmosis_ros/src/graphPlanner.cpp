#include <osmosis_control/graphPlanner.hpp>

////////////////////// PRIVATE //////////////////////

void GraphPlanner::graphPlannerFSM()
{
	switch (state_)
	{
		case WAIT_GOAL:
			ROS_INFO("WAIT GOAL\n");
			if (new_goal())
			{
				compute_plan();
				state_=WAIT_COMPUTE_PLAN;
			}
			if(emergency_stop_)
				state_=EMERGENCY_STOP;
			break;

		case WAIT_COMPUTE_PLAN:
			ROS_INFO("WAIT_COMPUTE PLAN\n");
			if (plan_computed())
			{
				state_=SEND;
			}
			if(emergency_stop_)
				state_=EMERGENCY_STOP;
			break;

		case SEND:
			ROS_INFO("SEND\n");
			target_index ++; // needed to test plan_done()
			ROS_INFO ("target_index : %d   plan.size(): %u",target_index,(int)plan.size());
			if (plan_done()==true)
			{
				state_=GOAL_DONE;
			}
			else
			{
				publishSendTarget();
				state_=FOLLOW;
			}
			if(emergency_stop_)
				state_=EMERGENCY_STOP;
			break;

		case FOLLOW:
			ROS_INFO("FOLLOW\n");
			if (is_arrived())
			{
				state_=SEND;
				target_reached_=false; //re-init
			}
			else execute_plan();
			if(emergency_stop_)
				state_=EMERGENCY_STOP;
			break;

		case GOAL_DONE:
			ROS_INFO("DONE\n");
			publishDone();
			state_=WAIT_GOAL;
			if(emergency_stop_)
				state_=EMERGENCY_STOP;
			break;
		
		case EMERGENCY_STOP:
			ROS_INFO("EMERGENCY_STOP\n");
			if(!emergency_stop_)
				state_=WAIT_GOAL;
			break;

		default: break;
	}
}

bool GraphPlanner::new_goal()
{
	bool newg=false;
	if (_new_goal)
	{
		newg=true;
		_new_goal=false; // reset for next time
	}
	return newg;
}

void GraphPlanner::compute_plan()
{
	auto s = graph.getClosestNode(current);
	//  logger().info("start node {} {}", s->name, s->point);
	ROS_INFO("start node %s %f %f", s->name.c_str(), s->point.x,s->point.y);
	auto g = graph.getClosestNode(mission_goal_.point);
	//  logger().info("goal node {} {}", g->name, g->point);
	ROS_INFO("goal node %s %f %f", g->name.c_str(), g->point.x,g->point.y);
	auto p = graph.compute_plan(s, g);
	plan.clear();
	plan.push_back(s->point);
	for (int i = 0; i < p.size(); i++)
		plan.push_back(p[i]->point);
	//  plan.push_back(goal);

	//  logger().info("plan computed, length: {}", plan.size());
	//  for (int i = 0; i < plan.size(); i++)
	//    logger().info("{}: {}", i, plan[i]);

	target_index = 0;
	ROS_INFO("Plan computed, size = %d",(int)plan.size());
	for (int i = 0; i < plan.size(); i++)
		ROS_INFO("%d: (%f , %f)",i, plan[i].x,plan[i].y);
}

bool GraphPlanner::plan_computed()
{
	return plan.size() > 0;
}

bool GraphPlanner::plan_done()
{
	return ( target_index >= (int)plan.size() );
}

bool GraphPlanner::is_arrived()
{
	return target_reached_;
}

void GraphPlanner::execute_plan()
{
	//current = shell().pose.read().location;
	//double d = Graph::distance(current, plan[target_index]);
	//logger().debug("distance to current target {}", d);
	ROS_INFO("POSE x: %f  y:%f", current.x , current.y );
	ROS_INFO("PLAN x: %f  y:%f", plan[target_index].x , plan[target_index].y );
	ROS_INFO("dist to target = %f", Graph::distance(current, plan[target_index]));
}

void GraphPlanner::publishDone()
{
	std_msgs::Bool target_reached;
	target_reached.data=true;;
	goal_reached_pub_.publish(target_reached);

	//  shell().arrived.write(true);
	//  _has_goal = false;
}

void GraphPlanner::publishSendTarget()
{

	//ROS_INFO ("target_index < plan.size() : %d < %u",target_index,plan.size());
	//  if (target_index < plan.size())
	//  {
	//shell().target.write(plan[target_index]);
	ROS_INFO("SEND target x: %f y:%f", plan[target_index].x, plan[target_index].y);
	goal_.point=plan[target_index];

	goal_.taxi=mission_goal_.taxi;

	target_pub_.publish(goal_);
	//  }
}

//from MAUVE
/*void GraphPlanner::read_ports()
{
	auto in_goal = shell().goal.read();
	auto in_id = shell().goal_id.read();
	if (in_goal.status == runtime::DataStatus::NEW_DATA || in_id.status == runtime::DataStatus::NEW_DATA)
	{
		_new_goal = true;
		graph = shell().map.read();
		auto p = shell().pose.read();
		current = p.location;
		logger().info("current location {}", current);
		if (in_id.status == runtime::DataStatus::NEW_DATA)
			goal = graph.getNode(in_id.value)->point;
		else
			goal = in_goal.value;
		logger().info("received new goal {}", goal);
		_has_goal = true;
	}
}*/

/*bool GraphPlanner::no_goal()
{
	return ! (_has_goal);
}*/


////////////////////// PUBLIC //////////////////////

GraphPlanner::GraphPlanner()
{
	freq_=10;
	//set up the publisher for the goal topic
	target_pub_ = nh_.advertise<osmosis_control::GoalMsg>("target", 1);
	goal_reached_pub_ = nh_.advertise<std_msgs::Bool>("goal_reached", 1);
	goal_sub_=nh_.subscribe("/mission_goal", 1, &GraphPlanner::callbackGoal, this);
	odom_sub_=nh_.subscribe("/pose", 1, &GraphPlanner::callbackPose, this);
	target_reached_sub_=nh_.subscribe("/target_reached", 1, &GraphPlanner::callbackTargetReached, this);
	emergency_stop_sub_=nh_.subscribe("/do_emergency_stop", 1, &GraphPlanner::callbackEmergencyStop, this);
	state_=WAIT_GOAL;
	_new_goal=false;
	target_reached_=false;
	emergency_stop_=false;
}

// this method should be placed somewhere else... where ???
void GraphPlanner::initGraph(const string& filename)
{
	Graph g;
	string s;
	s= ros::package::getPath("osmosis_control");
	s=s.append("/").append(filename);
	g=parse(s); // grapIO.hpp method
	graph=g;

	// to check
	//cout<<"HEY : "<<g.getNode("N49")->point.x<<endl;
}

void GraphPlanner::run()
{
	ros::Rate loop_rate(freq_); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		//cout <<"HEY";
		//goalKeyboard();
		graphPlannerFSM();

		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
	//while(1){ROS_INFO("OUT...");}
}

void GraphPlanner::callbackTargetReached(const std_msgs::Bool & target_reached)
{
	target_reached_=target_reached.data;
	ROS_INFO("Target reached : [%d]",target_reached_);
}

void GraphPlanner::callbackGoal(const osmosis_control::GoalMsg & thegoal)
{
	mission_goal_=thegoal;
	_new_goal=true;
	ROS_INFO("NEW GOAL : x: [%f], y:[%f]",mission_goal_.point.x,mission_goal_.point.y);
}

void GraphPlanner::callbackPose(const geometry_msgs::Pose2D & msg)
{
	current.x = msg.x;
	current.y = msg.y;
	//ROS_INFO("NEW POS : x: [%f], y:[%f]",current.x,current.y);
}

void GraphPlanner::callbackEmergencyStop(const std_msgs::Bool &emergency_stop)
{
	emergency_stop_=emergency_stop.data;
}

/*void GraphPlanner::callbackGoalId(const string & thegoal_id)
{
	goal_id=thegoal_id;
	_new_goal=true;
	ROS_INFO("NEW GOAL : [%s]",thegoal_id);
}*/


////////////////////// MAIN //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "graph_planner_node");

	GraphPlanner myGraphPlanner;

	myGraphPlanner.initGraph("/../../ressources/blagnac.graph");
	myGraphPlanner.run();
}
