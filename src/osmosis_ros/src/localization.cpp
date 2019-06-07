#include <osmosis_control/localization.hpp>

// Using const nav_msgs::Odometry::ConstPtr instead nav_msgs::Odometry, leads to avoid
// a copy of the object Odometry (which might be ressource consuming)
void Localization::localizationCallbackOdom(const nav_msgs::Odometry::ConstPtr& msg)
{
	tf::Pose pose;
	tf::poseMsgToTF(msg->pose.pose, pose);

	/* ROS_INFO("Seq: [%d]", msg->header.seq);
	ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
	ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
	*/

	robot_pose.x = msg->pose.pose.position.x;
	robot_pose.y = msg->pose.pose.position.y;
	robot_pose.theta =  tf::getYaw(pose.getRotation());
}

//! ROS node initialization
Localization::Localization()
{
	pose_pub_ = nh_.advertise<geometry_msgs::Pose2D>("/pose", 1);
	odom_sub_=nh_.subscribe("/summit_xl_a/ground_truth/state", 1, &Localization::localizationCallbackOdom, this);
}

bool Localization::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		pose_pub_.publish(robot_pose);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
	
	return true;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "localization_node");

	Localization mylocalization;
	mylocalization.run();
}
