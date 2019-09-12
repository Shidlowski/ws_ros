#include <ros/ros.h>

#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"
#include <laser_geometry/laser_geometry.h>

laser_geometry::LaserProjection projector_;


void scanCallback(const sensor_msgs::LaserScan::ConstPtr scan_in){
    
    sensor_msgs::PointCloud2 cloud2;
    projector_.projectLaser(*scan_in,cloud2);

    ros::NodeHandle nh;
    ros::Rate rate(1);

    std::string output_point_cloud2_topic;
    ros::param::get("/take_laser_scan/output_point_cloud2_topic",output_point_cloud2_topic);
    ROS_INFO_STREAM("Name of output topic PointCloud2 data: [ "<<output_point_cloud2_topic<<" ]");

    //public to topic "point_cloud2_data" data after conversion LaserScan to PointCloud2
    ros::Publisher pub=nh.advertise<sensor_msgs::PointCloud2>(output_point_cloud2_topic,100);

    while(ros::ok()){
        //data will already be filled
        pub.publish(cloud2);
        rate.sleep();
    }
  
}


int main(int argc, char **argv){
    ros::init(argc, argv, "take_laser_scan");

    ros::NodeHandle nh;
    std::string input_laser_scan_topic;
    ros::param::get("/take_laser_scan/input_laser_scan_topic",input_laser_scan_topic);
    ROS_INFO_STREAM("Name of input topic LaserScan data:[ "<<input_laser_scan_topic<<" ]");
    
    ROS_INFO_STREAM("Start take_laser_scan node");

    //subscribed to the topic with the data LaserScan
    ros::Subscriber sub=nh.subscribe(input_laser_scan_topic,100,scanCallback);
    
    
    ros::spin();

    return 0;
}