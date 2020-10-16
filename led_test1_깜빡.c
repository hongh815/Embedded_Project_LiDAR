#include <stdio.h>
#include <wiringPi.h>

#define LED 4
int main(void) {
	if(wiringPiSetup() == -1) {
		return -1;
	}

	pinMode(LED, OUTPUT);

	while(1) {
		digitalWrite(LED, 1);
		delay(1000);
		digitalWrite(LED, 0);
		delay(1000);
	}

	return 0;
}

