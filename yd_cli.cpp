#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#define RAD2DEG(x) ((x)*180./M_PI)


#define FORWARD 70
#define RIGHT 82
#define BACKRIGHT 3
#define BACK 4
#define BACKLEFT 5
#define LEFT 76
#define STOP 7

using namespace std;

char device[] = "/dev/ttyACM0";
int fd;
unsigned long baud = 9600;
int tmp=10;
int flag=70;

char DirectionControll(float x, float y) {
    //cout << "direction controll init!!!" << endl;
    if(y < 0.5){ //jangemul on
       if(315< x && x <= 360){printf("LEFT\n"); serialPutchar(fd, LEFT);} //Left                                                       
       else if(0< x && x<= 45){printf("RIGHT\n"); serialPutchar(fd, RIGHT);} //Right                                                                                                         
      // else if(45< x && x<=135){ printf("BACKR\n");serialPutchar(fd,65); } // back right                                                                                                            
    }
    else{
        //printf("forward\n");
        serialPutchar(fd, FORWARD);
    }
    flag=0;
    
    return fd;
}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{

    int i;
   // int count = scan->scan_time / scan->time_increment;    
    for(i = 0; i < 360; i++) { // count 값 ==> -5 ~ 5 도 값 , 0도에서 180도는 왼쪽방향임
        

        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
          
        if(degree > -180 && degree< 180 && scan->ranges[i]>0.13){ //dgree data print                                                                                                // printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree,scan->ranges[i], i);                                                                                                             
            
            vector< vector<float> > angle_2vec;
            vector<float> range_vec;
            vector<float> degree_vec;

            degree_vec.push_back(degree);
            range_vec.push_back(scan->ranges[i]);

            angle_2vec.push_back(degree_vec);
            angle_2vec.push_back(range_vec);
            
            sort(angle_2vec.begin[1](), angle_2vec.end[1]());
            reverse(begin(angle_2vec[1]), end(angle_2vec[1])); 
            cout << angle_2vec[0].size()\n;  // largest scan->range degree data out
            cout << angle_2vec[1].size() << endl;  // largest scan->range data out
            

            tmp=serialGetchar(fd); //get 50
            flag=tmp;
            printf("%c\n",flag);
            if(flag != 0){
            		sleep(1);
            		char data;
                //DirectionControll(degree+180, scan->ranges[i]);       
            		char datarr[1] = {};
                    datarr[0] = strcpy(data, DirectionControll(degree+180, scan->ranges[i]));         
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
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, sca                                                                                                             nCallback);
    ros::spin();

    return 0;
}
