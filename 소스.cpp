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

//under need socket
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
//end;

#define RAD2DEG(x) ((x)*180./M_PI)

char sendm[1024] = { 0x00 };

void DecToHex(int fr) {

    int i = 0, j = 0, a = 0;
    int bu;
    int fu;
    int arr[1024] = { 0x0F };
    char message[0] = '/0';

    while (1) {
        bu = fr % 10;
        fr /= 10;
        arr[j] = bu;
        j++;
        if (!fr) break;
    }


    while (j - a - 1 > -1) { // Convert DEC -> HEX

        switch (arr[j - a - 1]) {
        case 0: message[i] = 0x30; break;
        case 1: message[i] = 0x31; break;
        case 2: message[i] = 0x32; break;
        case 3: message[i] = 0x33; break;
        case 4: message[i] = 0x34; break;
        case 5: message[i] = 0x35; break;
        case 6: message[i] = 0x36; break;
        case 7: message[i] = 0x37; break;
        case 8: message[i] = 0x38; break;
        case 9: message[i] = 0x39; break;
        default: printf("wong value!!!!\n\n\n\n"); break;
        }
        a++;
        i++;
    }
    strcat(sendm, message);
}

//지역변수로 만듬. -> 배열 합침.

int Socket(float num1, float num2, float num3 ) {
	
	int n1 = (int)num1;
    int n2 = (int)num2;
    int n3 = (int)num3;

    DecToHex(n1);
    strcat(sendm, "/");
    DecToHex(n2);
    strcat(sendm, "/");
    DecToHex(n3);
	
	int clnt_sock;
	struct sockaddr_in serv_addr;

	//

	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);

	if (clnt_sock == -1);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.0.58");
	serv_addr.sin_port = htons(6112);

	if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1);
	if (write(clnt_sock, sendm, sizeof(sendm) - 1) == -1);

    sendm[0] = '\0' ;

	close(clnt_sock);
	return 0;

}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
    printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));

    for (int i = 0; i < 720; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        //if(degree > -180 && degree< 180)
        if (scan->ranges[i] > 0.01) {
            printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
			Socket(degree+180,1000* (scan->ranges[i]), i);
        }
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}