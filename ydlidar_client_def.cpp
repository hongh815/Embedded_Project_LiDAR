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
int flag=0; //init
int block=0;
int distance2=0;
int num=0;
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
//    int count = scan->scan_time / scan->time_increment;
    //printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    //printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
    	
 
    for(int i = 0; i < 720; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
	float distance = scan->ranges[i];		
	
	if(distance >0.15 && distance <0.4){ //block
	//printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
	  
		if(degree>-40 && degree<-25 && flag != 1){ //right
			printf("right: %f %f\n",degree,distance); 
			flag=1;
			distance2=distance;
			return;	        
	    	}
	    	else if(degree>25 && degree<40 && flag != 2){ //left
			printf("left: %f %f\n",degree,distance);
			flag=2;
			distance2=distance;
			return;
		}
		
    	} //end block
    	if(i>=710){
    	printf("distance\n");
    	distance2=distance;
    	}
    }//enf for
    

	
}// end scancallback


    
    //if here , no block
 
    


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    printf("start\n");
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}
