Сonversion package v 1.0
Convert sensor_msgs::LaserScan to sensor_msgs::PointCloud2

Сonnection to launch file

    <!--Include launch file covert_laser_scan_to_point_cloud2-->
    <include file="$(find convert_laser_scan)/launch/convert_laser_scan_to_point_cloud2.launch" />
    
    <param name = "/take_laser_scan/input_laser_scan_topic" value = "tuturu1" />
    <param name = "/take_laser_scan/output_point_cloud2_topic" value = "tuturu2" />
