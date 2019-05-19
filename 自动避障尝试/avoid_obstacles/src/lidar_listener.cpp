#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>

static std::string pub_topic;
class LidarListener
{
public:
    LidarListener();
private:
     ros::NodeHandle n;
     ros::Publisher scan_pub;
     ros::Subscriber scan_sub;
     void lidarListenerCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
};

LidarListener::LidarListener()
{
    scan_pub = n.advertise<std_msgs::Bool>(pub_topic,1);
    scan_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_raw",1,&LidarListener::lidarListenerCallback,this);
}

void LidarListener::lidarListenerCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    ROS_INFO("[lidar_listener]");
    bool jud = false;
    int nRanges = scan->ranges.size();
    for(int i=0 ; i<nRanges ; i++)
    {
        if (scan->ranges[i] < 0.1) {
            jud = true;
        }
    }
    scan_pub.publish(jud);
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"lidar_listener");
    ros::NodeHandle n_param("~");
    std::string strSerialPort;
    n_param.param<std::string>("pub_topic", pub_topic, "/scan_listener");
    LidarListener lidar_listener;
    ros::spin();
}
