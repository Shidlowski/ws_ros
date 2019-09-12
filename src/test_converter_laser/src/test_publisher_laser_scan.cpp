
#include <ros/ros.h>

#include "sensor_msgs/LaserScan.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "test_publisher_laser_scan");

    ROS_INFO_STREAM("Start test_bublisher_laser_scan node!");

    ros::NodeHandle nh;

    std::string input_laser_scan_topic;
    ros::param::get("/take_laser_scan/input_laser_scan_topic",input_laser_scan_topic);

    ros::Rate rate(1);

    ros::Publisher pub=nh.advertise<sensor_msgs::LaserScan>(input_laser_scan_topic,100);

    sensor_msgs::LaserScan msg;

    while(ros::ok()){
        //msg.
        pub.publish(msg);
        rate.sleep();
    }
    
    return 0;
}
