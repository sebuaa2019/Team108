#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#define go_times 1000000
#define stop_time 1000000

int main(int argc, char** argv) { 


	ros::init(argc, argv, "go_forward"); 
	ros::NodeHandle n; 
	ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Rate loopRate(10);

    //int times = go_times;
	int times = 10;

	while(ros::ok()&&times>0) {

		geometry_msgs::Twist vel_cmd; 

		vel_cmd.linear.x = -0.2; 
		vel_cmd.linear.y = 0; 
		vel_cmd.linear.z = 0; 

		vel_cmd.angular.x = 0; 
		vel_cmd.angular.y = 0; 
		vel_cmd.angular.z = 0; 
		vel_pub.publish(vel_cmd); 

        times--;

		loopRate.sleep();
		//ros::spinOnce(); 
	} 

   
    //times = stop_time;
	times = 10;

	while(ros::ok()&&times>0) {

		geometry_msgs::Twist vel_cmd; 

		vel_cmd.linear.x = 0; 
		vel_cmd.linear.y = 0; 
		vel_cmd.linear.z = 0; 

		vel_cmd.angular.x = 0; 
		vel_cmd.angular.y = 0; 
		vel_cmd.angular.z = 0; 
		vel_pub.publish(vel_cmd); 

        times--;

		loopRate.sleep();
		//ros::spinOnce(); 
	} 


return 0; 

}