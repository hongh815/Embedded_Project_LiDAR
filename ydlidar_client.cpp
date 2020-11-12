/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS Node Client 
 *
 *  Copyright 2015 - 2018 EAI TEAM
 *  http://www.ydlidar.com
 * 
 */
#include <wiringPi.h>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
#define RAD2DEG(x) ((x)*180./M_PI)
#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define BACK 4
#define ARDUINO 5
#define DEGSET(x) (((x)+360)/10) //180~540 / 10 --> 18<x<54

void directionSet(float degree) {
    int result = (int)DEGSET(degree);
	int out_result;
	if(result <= 23 || result >= 50) {
		out_result = BACK;
	} else if(result >= 41 && result < 50) {
		out_result = RIGHT;
	} else if(result <= 32 && result > 23) {
		out_result = LEFT;
	} else if (result > 32 && result < 41) {
		out_result = FORWARD;
	} else out_result = 0;

    switch(out_result) {
        case 2:
            cout << "dir : RIGHT - "<< RIGHT << endl;
            break;
        case 1:
            cout << "dir : FORWARD - " << FORWARD << endl;
            break;
        case 4:
            cout << "dir : BACK - " << BACK << endl;
            break;
        case 3:
            cout << "dir : LEFT - " << LEFT << endl;
            break;
        default:
            cout << "dir : DEFAULT(config FORWARD) - " << FORWARD << endl;
    }
}

float scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int i;
	int count = scan->scan_time / scan->time_increment;    	
	float send_degree; 
	float send_dist = -1; 

    for(i = 0; i < count; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
	float distance = scan->ranges[i];		
		
	if(send_dist < distance){ //block
	//printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
    	send_dist = distance;
	send_degree = degree;
	} //end block	
    }//enf for


	directionSet(send_degree);
	printf("degree :: %f\n", send_degree);
	printf("dist :: %f\n", send_dist);
	printf("count :: %d\n", count);   	
	printf("\n");

	return send_degree;
	
}// end scancallback

    
    //if here , no block
 
int main(int argc, char **argv)
{
	
	wiringPisetup();
	pinMode(FORWARD, OUTPUT);
	pinMode(BACK, OUTPUT);
	pinMode(RIGHT, OUTPUT);
	pinMode(LEFT, OUTPUT);
	pinMode(ARDUINO, INPUT);

    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    printf("start\n");
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}

/*
int flag=0; //init
int block=0;
int distance2=0;
int num=0;

//    int count = scan->scan_time / scan->time_increment;
    //printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    //printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));

*/
