#include <osmosis_control/graphPlanner.hpp>


//! ROS node initialization
GraphPlanner::GraphPlanner()
{
	//set up the publisher for the goal topic
	target_pub_ = nh_.advertise<geometry_msgs::Point>("target", 1);
	goal_reached_pub_ = nh_.advertise<std_msgs::Bool>("goal_reached", 1);
	goal_sub_=nh_.subscribe("/goal", 1, &GraphPlanner::callbackGoal, this);
	odom_sub_=nh_.subscribe("/pose", 1, &GraphPlanner::callbackPose, this);
	target_reached_sub_=nh_.subscribe("/target_reached", 1, &GraphPlanner::callbackTargetReached, this);
	state_=wait_goal;
	_new_goal=false;
	target_reached_=false;
}

void GraphPlanner::callbackTargetReached(const std_msgs::Bool & target_reached)
{
	target_reached_=target_reached.data;
	ROS_INFO("Target reached : [%d]",target_reached_);
}

void GraphPlanner::callbackGoal(const geometry_msgs::Point & thegoal)
{
	this->goal=thegoal;
	_new_goal=true;
	ROS_INFO("NEW GOAL : x: [%f], y:[%f]",goal.x,goal.y);
}

/*void GraphPlanner::callbackGoalId(const std::string & thegoal_id)
{
	this->goal_id=thegoal_id;
	_new_goal=true;
	ROS_INFO("NEW GOAL : [%s]",thegoal_id);
}*/

void GraphPlanner::callbackPose(const geometry_msgs::Pose2D & msg)
{
	this->current.x = msg.x;
	this->current.y = msg.y;
	//ROS_INFO("NEW POS : x: [%f], y:[%f]",this->current.x,this->current.y);
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
		this->logger().info("current location {}", current);
		if (in_id.status == runtime::DataStatus::NEW_DATA)
			goal = graph.getNode(in_id.value)->point;
		else
			goal = in_goal.value;
		this->logger().info("received new goal {}", goal);
		_has_goal = true;
	}
}*/

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

/*bool GraphPlanner::no_goal()
{
	return ! (_has_goal);
}*/

void GraphPlanner::compute_plan() 
{
	auto s = graph.getClosestNode(this->current);
	//  this->logger().info("start node {} {}", s->name, s->point);
	ROS_INFO("start node %s %f %f", s->name.c_str(), s->point.x,s->point.y);
	auto g = graph.getClosestNode(this->goal);
	//  this->logger().info("goal node {} {}", g->name, g->point);
	ROS_INFO("goal node %s %f %f", g->name.c_str(), g->point.x,g->point.y);
	auto p = graph.compute_plan(s, g);
	plan.clear();
	plan.push_back(s->point);
	for (int i = 0; i < p.size(); i++)
		plan.push_back(p[i]->point);
	//  plan.push_back(this->goal);

	//  this->logger().info("plan computed, length: {}", plan.size());
	//  for (int i = 0; i < plan.size(); i++)
	//    this->logger().info("{}: {}", i, plan[i]);

	target_index = 0;
	ROS_INFO("Plan computed, size = %d",(int)plan.size());
	for (int i = 0; i < plan.size(); i++)
		ROS_INFO("%d: (%f , %f)",i, plan[i].x,plan[i].y);
}

bool GraphPlanner::plan_computed() 
{
	return plan.size() > 0;
}

void GraphPlanner::done() 
{
	std_msgs::Bool target_reached;
	target_reached.data=true;;
	goal_reached_pub_.publish(target_reached);

	//  shell().arrived.write(true);
	//  _has_goal = false;
}

bool GraphPlanner::plan_done() 
{
	return ( target_index >= (int)plan.size() );
}

void GraphPlanner::send_target()
{

	//ROS_INFO ("target_index < plan.size() : %d < %u",target_index,plan.size());
	//  if (target_index < plan.size())
	//  {
	//this->shell().target.write(plan[target_index]);
	ROS_INFO("SEND target x: %f y:%f", plan[target_index].x, plan[target_index].y);
	this->target_=plan[target_index];
	target_pub_.publish(target_);
	//  }
}

bool GraphPlanner::is_arrived()
{
	//return Graph::distance(this->current, plan[target_index]) < TH;
	return target_reached_;
}

void GraphPlanner::execute_plan()
{
	//this->current = this->shell().pose.read().location;
	//double d = Graph::distance(this->current, plan[target_index]);
	//this->logger().debug("distance to current target {}", d);
	ROS_INFO("POSE x: %f  y:%f", this->current.x , this->current.y );
	ROS_INFO("PLAN x: %f  y:%f", plan[target_index].x , plan[target_index].y );
	ROS_INFO("dist to target = %f", Graph::distance(this->current, plan[target_index]));
}

// this method should be placed somewhere else... where ???
void GraphPlanner::initGraph(const std::string& filename)
{
	Graph g;
	std::string s;
	s= ros::package::getPath("osmosis_control");
	s=s.append("/").append(filename);
	g=parse(s); // grapIO.hpp method
	this->graph=g;

	// to check
	//std::cout<<"HEY : "<<g.getNode("N49")->point.x<<std::endl;
}

void GraphPlanner::graphPlannerFSM()
{
	State next_state=state_;
	switch (state_)
	{
		case wait_goal:
			ROS_INFO("WAIT GOAL");
			if (new_goal())
			{
				compute_plan();
				next_state=wait_compute_plan;
			}
			break;

		case wait_compute_plan:
			ROS_INFO("WAIT_COMPUTE PLAN");
			if (plan_computed())
			{
				next_state=send;
			}
			break;

		case send:
			ROS_INFO("SEND");
			target_index ++; // needed to test plan_done()
			ROS_INFO ("target_index : %d   plan.size(): %u",target_index,(int)plan.size());
			if (plan_done()==true)
			{
				next_state=goal_done;
			}
			else
			{
				send_target();
				next_state=follow;
			}
			break;

		case follow:
			ROS_INFO("FOLLOW");
			if (is_arrived())
			{
				next_state=send;
				target_reached_=false; //re-init
			}
			else execute_plan();
			break;

		case goal_done:
			ROS_INFO("DONE");
			done();
			next_state=wait_goal;
			break;

		default : next_state=wait_goal;

	}
	state_=next_state;
}

void GraphPlanner::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		//std::cout <<"HEY";
		//this->goalKeyboard();
		this-> graphPlannerFSM();

		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
	//while(1){ROS_INFO("OUT...");}
}



int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "graph_planner_node");

	GraphPlanner myGraphPlanner;

	myGraphPlanner.initGraph("test.graph");
	myGraphPlanner.run();
	//while(1){ROS_INFO("OUT...");}
}
