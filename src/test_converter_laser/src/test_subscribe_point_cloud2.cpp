#include <ros/ros.h>

#include "sensor_msgs/PointCloud2.h"

void pointCloud2Callback(const sensor_msgs::PointCloud2::ConstPtr point){

    ROS_INFO_STREAM("data came in the format pointCloud2!!!!!!! Process the data please!!!!!!!");

}

int main(int argc, char **argv){
    ros::init(argc, argv, "test_subscribe_point_cloud2");

    ros::NodeHandle nh;

    std::string output_point_cloud2_topic;
    ros::param::get("/take_laser_scan/output_point_cloud2_topic",output_point_cloud2_topic);

    ROS_INFO_STREAM("Start test_subscribe_point_cloud2 node");

    //subscribed to the topic with the data LaserScan
    ros::Subscriber sub=nh.subscribe(output_point_cloud2_topic,100,pointCloud2Callback);
    
    ros::spin();

    return 0;
}