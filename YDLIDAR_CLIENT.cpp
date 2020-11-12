
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
#include <vector>
#include <algorithm>
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
using namespace std;

char device[] = "/dev/ttyACM0";
int fd;
unsigned long baud = 9600;
int tmp=55;
int flag=70;
int num = 0;
float send_dist = -1; 
float send_degree = 1; 
#define FORWARD 70
#define RIGHT 82
#define LEFT 76
#define BACK 66
#define DEGSET(x) (((x)+360)/10) //180~540 / 10 --> 18<x<54

#define ARDUINO 4 


int fa = 1; // this add
void return_function_one(float degree, float distance) {
      if(degree>-40 && degree<-25 && flag != 1){ //right
         printf("right: %f %f\n",degree,distance);
         serialPutchar(fd, 82);
         flag=1;
//         break;           
          }

          else if(degree>25 && degree<40 && flag != 2){ //left
         printf("left: %f %f\n",degree,distance);
         serialPutchar(fd, 76);
         flag=2;
  //       break;
      }
/*      else if(degree > -20 && degree < 20 && flag != 5) {
          printf("back!!");
          flag = 5;
         break;
      }*/
      
      else{
         num++;
         if(num > 10000){
         printf("foward : %f %f\n", degree, distance);
         serialPutchar(fd, 70);
         num = 0;
         fa = 0;
         }
    }
}
void directionSet(float degree) {
    cout << "degree ::: >>> " << degree << endl;
    int result = (int)DEGSET(degree);
    cout << "degree < > :  : >>>> " << result << endl;
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
        case 82:
            cout << "dir : RIGHT - "<< RIGHT << endl;
            serialPutchar(fd, RIGHT);
            break;
        case 70:
            cout << "dir : FORWARD - " << FORWARD << endl;
            serialPutchar(fd, FORWARD);
            break;
        case 66:
            cout << "dir : BACK - " << BACK << endl;
            serialPutchar(fd, BACK);
            break;
        case 76:
            cout << "dir : LEFT - " << LEFT << endl;
            serialPutchar(fd, LEFT);
            break;
        default:
            cout << "dir : DEFAULT(config FORWARD) - " << FORWARD << endl;
            serialPutchar(fd, FORWARD);
    }
}


float return_function_two(float degree, float distance) {
	if(send_dist < distance){ //block
    	send_dist = distance;
	    send_degree = degree;
    
    cout << "send dist ::>>" << send_dist << endl;
    
	} //end block	
    else return 1;

    return send_degree;
/*	printf("degree :: %f\n", send_degree);
	printf("dist :: %f\n", send_dist);
	printf("count :: %d\n", count);   	
	printf("\n"); */
}



void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
//    int count = scan->scan_time / scan->time_increment;
	int count = scan->scan_time / scan->time_increment;    	
    send_degree = 1;
    
    //printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    //printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
  
    if(digitalRead(ARDUINO)){
        printf("doit\n");
    }//for debug

    for(int i = 0; i < 720; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        float distance = scan->ranges[i];      

   if(digitalRead(ARDUINO) || fa == 1){ // this add if no fa (flag) this code no operation; frist signal must operating; 
    if(distance >0.15){ //block dis < 0.4
   
        //printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
   //     return_function_one(degree, distance);  gilhee function
          
        send_degree = return_function_two(degree, distance); //hongbeom function
       }
    /*   else if(distance >0.15 && flag != 0 && degree>-40 && degree < 40){ //forward
      printf("forward: %f %f\n",degree,distance); 
      flag = 0;
      break;
   }*/
    
    }
    
}
        directionSet(send_degree);
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

    pinMode(ARDUINO, INPUT); // this add
    
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();
    
    return 0;
}
