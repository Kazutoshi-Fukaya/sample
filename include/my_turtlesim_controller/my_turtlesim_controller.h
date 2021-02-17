#ifndef MY_TURTLESIM_CONTROLLER_H
#define MY_TURTLESIM_CONTROLLER_H

#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

class MyTurtlesimController
{
    public:
        MyTurtlesimController();
        void process();

    private:
        void pose_callback(const turtlesim::Pose::ConstPtr &);
        void go_straight();
        void turn();

        int hz;
        int N;

        ros::NodeHandle nh;
        ros::NodeHandle private_nh;
        ros::Subscriber sub_pose;
        ros::Publisher pub_cmd_vel;
        //geometry_msgs::Pose current_pose;
        turtlesim::Pose current_pose;

};
#endif
