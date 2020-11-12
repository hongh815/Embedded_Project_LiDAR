
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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <unistd.h>

#define RAD2DEG(x) ((x)*180./M_PI)
#define FORWARD 1
#define RIGHT 2
#define BACKRIGHT 3
#define BACK 4
#define BACKLEFT 5
#define LEFT 6
#define STOP 7
#include <iostream>
using namespace std;
char device[] = "/dev/ttyACM0";
int fd;
unsigned long baud = 9600;
int tmp=55;
int flag=70;

void DirectionControll(float x, float y) {
    
    //cout << "direction controll init!!!" << endl;
    
           

    if(y < 0.5){ //jangemul on
        
       if(315< x && x <= 360){ printf("LEFT\n"); serialPutchar(fd, 76);  } //Leftt
       else if(0< x && x<= 45){ printf("RIGHT\n"); serialPutchar(fd, 82); } //right
      // else if(45< x && x<=135){ printf("BACKR\n"); serialPutchar(fd, 65); } // back right
      // else if(225< x && x<=315){ printf("BACKL\n"); serialPutchar(fd, 66); }  // back left
    } 
    else{ 
        printf("forward\n"); 
        serialPutchar(fd, 70);
        
    }
    flag=0;
    
}

//void scan_right(float degree, float distance) {
//            printf("RIGHT\n"); serialPutchar(fd, 82);
//            sleep(1);
//}

//void  scan_left(float degree, float distance) {
//            printf("LEFT\n"); serialPutchar(fd, 76);
//            sleep(1);
//}


void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
    int count = scan->scan_time / scan->time_increment;
   // printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
   // printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));

    for(int i = 0; i < count; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        float x = RAD2DEG(scan->angle_min + scan->angle_increment * i);
            if(degree > -180 && degree< 180 && scan->ranges[i]>0.13){ //dgree data print
            //printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree,scan->ranges[i], i);
            tmp=serialGetchar(fd);//get 50
            flag=tmp;
            printf("%d\n", tmp);
            printf("%d\n",flag);
            if(flag != 'q'){
                DirectionControll(degree+180, scan->ranges[i]);

            }

        }
    }
}

int main(int argc, char **argv)
{
    if((fd = serialOpen (device, baud)) < 0) {
        fprintf(stderr, "Uable to open serial device : %s\n", strerror(errno));
        exit(1);
    }

    if(wiringPiSetup() == -1) {
        fprintf(stderr, "Unable to start wiringPi : %s\n", strerror(errno));
        exit(1);
    }

    serialPutchar(fd, 70);
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}
