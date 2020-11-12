/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS Node Client
 *
 *  Copyright 2015 - 2018 EAI TEAM
 *  http://www.ydlidar.com
 *
 */

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <unistd.h>
#define RAD2DEG(x) ((x)*180./M_PI)
int flag = 0; //init
int num = 0;
int backflag(int flag) {


    return 0;
}
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{

    for (int i = 0; i < 720; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);\
        float distance = scan->ranges[i];

        if (distance > 0.1&& distance < 0.4) { //block
       
            if (degree > -40 && degree < -25 && flag != 1) {  //right
                num++;
                if (num > 100) { //100은 right noblcok 반복 되는 횟수를 100분의 1로 줄여주는 것을 의미한다. 
                    printf("right: %f %f\n", degree, distance);
                    flag = 1;
                    num = 0;
                }
                return;
            }
            else if (degree > 25 && degree < 40 && flag != 2) {  //left
                num++;
                if (num > 100) {
                    printf("left: %f %f\n", degree, distance);
                    flag = 2;
                    num = 0;
                }
                return;
            }
        }//end block
    }//end for
    if (flag != 3) {
        printf("no block\n");
        flag = 3;
    }

}//end scanCallback

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    printf("no block\n");
    flag = 3; //초기에 직진신호 한번
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}
