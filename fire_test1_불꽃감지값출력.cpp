#include <stdio.h>
#include <iostream>
#include <wiringPi.h>

using namespace std;

#define LED 4
#define FIRE 1

int main(void) {

    if(wiringPiSetup() == -1) return -1;

    pinMode(FIRE, INPUT);
    pinMode(LED, OUTPUT);

    while(1) {
        int result = digitalRead(FIRE);
        cout << result << endl;
        if(result == HIGH) {
            digitalWrite(LED, 1);
        } else digitalWrite(LED, 0);
        delay(1000);
    }

    return 0;
}
