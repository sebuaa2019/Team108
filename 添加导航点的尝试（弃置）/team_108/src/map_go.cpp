#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#define go_times 10000000

int main(int argc, char** argv) { 

	ros::init(argc, argv, "map_go"); 
	ros::NodeHandle n; 
	ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	long times = go_times;

	while(ros::ok() && times>=0) {

		geometry_msgs::Twist vel_cmd; 

		vel_cmd.linear.x = 0.1; 
		vel_cmd.linear.y = 0; 
		vel_cmd.linear.z = 0; 

		vel_cmd.angular.x = 0; 
		vel_cmd.angular.y = 0; 
		vel_cmd.angular.z = 0; 
		vel_pub.publish(vel_cmd); 
        //printf("gogo");
		ros::spinOnce(); 
		times--;
	} 

	times = go_times - 1000000;

	while(ros::ok() && times>=0) {

		geometry_msgs::Twist vel_cmd; 

		vel_cmd.linear.x = -0.1; 
		vel_cmd.linear.y = 0; 
		vel_cmd.linear.z = 0; 

		vel_cmd.angular.x = 0; 
		vel_cmd.angular.y = 0; 
		vel_cmd.angular.z = 0; 
		vel_pub.publish(vel_cmd); 

		ros::spinOnce(); 
		times--;
	} 
times = 100000;
while(ros::ok() && times>=0) {

		geometry_msgs::Twist vel_cmd; 

		vel_cmd.linear.x = 0; 
		vel_cmd.linear.y = 0; 
		vel_cmd.linear.z = 0; 

		vel_cmd.angular.x = 0; 
		vel_cmd.angular.y = 0; 
		vel_cmd.angular.z = 0; 
		vel_pub.publish(vel_cmd); 

		ros::spinOnce(); 
		times--;
	} 

return 0; 

}
