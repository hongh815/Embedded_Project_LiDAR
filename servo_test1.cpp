
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define SERVO 24
#define LED 23
#define ULTRA_IN 1
#define ULTRA_OUT 0


class Servo {
    public :
        char sel;
        


};
int main(void) {
    char sel;

    if(wiringPiSetup() == -1) {return 1; printf("setinit\n");}

    softPwmCreate(SERVO, 0, 200);

    while(1) {
        fputs("select c, r, l, q : ", stdout);
        scanf("%c", &sel);
        getchar();
        if(sel == 'c') softPwmWrite(SERVO, 15); //0도
        else if(sel == 'r') softPwmWrite(SERVO, 24); //90도
        else if(sel == 'l') softPwmWrite(SERVO, 5); //-90도
        else if(sel == 'q') return 0;
    }

    return 0;
}
