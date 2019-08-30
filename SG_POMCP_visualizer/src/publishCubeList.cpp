/**
 * \file publishTexturedObjects.cpp
 * \author Zhen Zeng (zengzhen@umich.edu)
 * \brief publish textured objects with ground truth poses
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <sstream>
#include <std_msgs/String.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "publishTexturedObjects");
    ros::NodeHandle node_handle;

    float scale = 0.2;
    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time::now();
    marker.ns = "GOP";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE_LIST;
    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = scale;
    marker.scale.y = scale;
    marker.scale.z = scale;

    float step = 0.2;
    marker.points.clear();
    marker.colors.clear();
    for(int x = -20; x < 20; x++)
    {
        for(int y = -20; y < 20; y++)
        {
            geometry_msgs::Point point;
            point.x = x*step;
            point.y = y*step;
            point.z = 0.8;
            marker.points.push_back(point);

            std_msgs::ColorRGBA cube_color;
            cube_color.r = (x+20)/50.0;
            cube_color.g = (y+20)/50.0;
            cube_color.b = 0.5;
            cube_color.a = 1.0;
            marker.colors.push_back(cube_color);
        }
    }

    ros::Publisher objects_publisher = node_handle.advertise<visualization_msgs::Marker>("/object_cube_belief", 0);

    ros::Rate publish_rate(1);
    while(ros::ok())
    {
        objects_publisher.publish(marker);
        publish_rate.sleep();
    }


    return 0;
}
