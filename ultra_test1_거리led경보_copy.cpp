
#include <fstream> //c++ fileinout
#include <string>
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>
#define IN 1 
#define OUT 0 
#define LED 4
#define _CRT_SECURE_NO_WARNINGS

using namespace std;


class LedSensorData {
    float data;
    public:
        LedSensorData();
        LedSensorData(float);
        float data_input();
};
LedSensorData::LedSensorData() {cout<<"LedSensorData() init!!"<<endl;}
LedSensorData::LedSensorData(float data) {cout<<"LedSensorData(float) init!!!"<<endl;this->data=data;
    cout<<" ## data_input : "<<data<<endl;
}
float LedSensorData::data_input() {
    ofstream ofile("led_test_data.txt", ios::app);
    string str = to_string(data);
    if(ofile.is_open()) {
        ofile << str << endl;
        ofile.close();
    } 
    return 0;
}

int main(void) {

    float dist, s, e;   
    // s : 센서에서 입력되는 값이 없을때 값
    // e : 센서에서 들어오는 값이 있을 때의 값
    // dist : 위의 두 값의 차를 이용하여 거리 값 측정

    wiringPiSetup();

    pinMode(OUT, OUTPUT);
    pinMode(IN, INPUT);

    while(1) {
        digitalWrite(OUT,0);
        digitalWrite(OUT,1);
        delayMicroseconds(10);
        digitalWrite(OUT,0);
        while(digitalRead(IN) == 0)
            s = micros();
        while(digitalRead(IN) == 1)
            e = micros();
        dist = (e - s) / 58;
        cout << "distance(cm) : " << dist << endl;
        if(dist < 10) {digitalWrite(LED, 1);cout<<"Warning!!"<<endl;}else digitalWrite(LED, 0); 
        if(dist > 0) {
            LedSensorData led_in_data(dist);
            led_in_data.data_input();
        }
        delay(1000);     //!!!!!!!!!!!!!!!!!!!!!! 결과 출력 시간 설정 !!!!!!!!!!!!
    }

    return 0;
}
