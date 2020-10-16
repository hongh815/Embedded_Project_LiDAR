#include <stdio.h>
#include <iostream>
#include <wiringPi.h>


#define LED 4
#define SENSOR 1
using namespace std;

int main(void) {

    if(wiringPiSetup() == -1) return -1;

    pinMode(SENSOR, INPUT);
    pinMode(LED, OUTPUT);

    while(1) {
        int result = digitalRead(SENSOR);
        cout << result << endl;

        if(result == HIGH) {
            digitalWrite(LED, 1);
            delay(100);
            digitalWrite(LED, 0);
            delay(100);
        } else digitalWrite(LED, 0);
        delay(500);
    }
    return 0;
}

