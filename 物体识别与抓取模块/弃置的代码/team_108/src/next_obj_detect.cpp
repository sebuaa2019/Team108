#include <ros/ros.h> 
#include <move_base_msgs/MoveBaseAction.h> 
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){ 

	ros::init(argc, argv, "next_obj_detect");
	MoveBaseClient ac("move_base", true);

	while(!ac.waitForServer(ros::Duration(5.0))){ 
		ROS_INFO("Waiting for the move_base action server to come up");
	 }
	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "base_footprint"; 

	goal.target_pose.header.stamp = ros::Time::now();
	//向右平移0.2米
	goal.target_pose.pose.position.y = -0.2; 
	//面朝桌面
	goal.target_pose.pose.orientation.w = 1.0;
	ROS_INFO("Sending goal"); ac.sendGoal(goal);
	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) 
		ROS_INFO("the base moved 0.2 meter rightward"); 
	else 
		ROS_INFO("The base failed to move 0.2 meter for some reason");
	return 0; 
}