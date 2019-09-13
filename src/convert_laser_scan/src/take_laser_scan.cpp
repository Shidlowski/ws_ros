#include <ros/ros.h>

#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"
#include <laser_geometry/laser_geometry.h>

laser_geometry::LaserProjection projector_;

ros::Publisher pub;


void scanCallback(const sensor_msgs::LaserScan::ConstPtr scan_in){
    sensor_msgs::PointCloud2 cloud2;
    projector_.projectLaser(*scan_in,cloud2);

    pub.publish(cloud2);
}

int main(int argc, char **argv){

    ros::init(argc, argv, "take_laser_scan");

    ros::NodeHandle privateNodeHandle("~");

    std::string input_topic;
    if(!privateNodeHandle.getParam("input_topic", input_topic)){
        ROS_ERROR_STREAM("Error getParam input_topic");
        return 1;
    }
    else
    {
        ROS_INFO_STREAM("Name of input topic LaserScan data:[ "<<input_topic<<" ]");
    }
    
    std::string output_topic;
    if (!privateNodeHandle.getParam("output_topic", output_topic)) {
        ROS_ERROR_STREAM("Error getParam output_topic");
        return 1;
    }
    else
    {
        ROS_INFO_STREAM("Name of output topic PointCloud2 data: [ "<<output_topic<<" ]");
    }
    
    ros::NodeHandle nh;

    //public to topic "point_cloud2_data" data after conversion LaserScan to PointCloud2
    pub=nh.advertise<sensor_msgs::PointCloud2>(output_topic,100);

    ROS_INFO_STREAM("Start take_laser_scan node");

    //subscribed to the topic with the data LaserScan
    ros::Subscriber sub=nh.subscribe(input_topic,100,scanCallback);
    
    ros::spin();

    return 0;
}