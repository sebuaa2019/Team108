#include "ros/ros.h"
#include "std_msgs/Bool.h"

void chatterCallback(const std_msgs::Bool::ConstPtr& msg)
{
    ros::NodeHandle node;
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    while(ros::ok())   {
        geometry_msgs::Twist vel_cmd;
        vel_cmd.linear.x = 0;
        vel_cmd.linear.y = 0;
        vel_cmd.linear.z = 0;
        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 0;
        vel_pub.publish(vel_cmd);
        ros::spinOnce();
    }
    //ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "stoplistener");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/scan_listener", 1 ,chatterCallback);

    ros::spin();

    return 0;
 }
