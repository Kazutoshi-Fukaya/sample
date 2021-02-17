#include "my_turtlesim_controller/my_turtlesim_controller.h"

MyTurtlesimController::MyTurtlesimController():private_nh("~")
{
    private_nh.param("hz",hz,{50});
    private_nh.param("N",N,{6});

    sub_pose = nh.subscribe("/turtle1/pose",10,&MyTurtlesimController::pose_callback,this);

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);
}

void MyTurtlesimController::pose_callback(const turtlesim::Pose::ConstPtr &msg)
{
    current_pose = *msg;
}

void MyTurtlesimController::go_straight()
{
    std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 1.0;
    pub_cmd_vel.publish(cmd_vel);
}

void MyTurtlesimController::turn()
{
    std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.angular.z = M_PI/45.0;
    pub_cmd_vel.publish(cmd_vel);
}

void MyTurtlesimController::process()
{
    ros::Rate loop_rate(hz);
    turtlesim::Pose last_pose = current_pose;
    int corner = 0;
    float naikaku = 2*M_PI/N;
    float turn_theta;

    while(ros::ok())
    {
        if (current_pose.theta-last_pose.theta < 0.0) turn_theta = current_pose.theta-last_pose.theta+2*M_PI;
        else turn_theta=current_pose.theta-last_pose.theta;

        if ((last_pose.x-current_pose.x)*(last_pose.x-current_pose.x)+(last_pose.y-current_pose.y)*(last_pose.y-current_pose.y) >= 4.0) corner = 1;
        if (turn_theta >= naikaku)
        {
            corner = 0;
            last_pose = current_pose;
        }

        if (corner == 0) go_straight();
        else turn();
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv,"my_turtlesim_controller");
    MyTurtlesimController my_turtlesim_controller;
    my_turtlesim_controller.process();
    return 0;
}
