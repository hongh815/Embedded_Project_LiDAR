#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <errno.h>
#include <string.h>
using namespace std;

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 //1Mhz
#define CS_MCP3008 11 //GPIO 8

int read_mcp(unsigned char adcChannel) {
    unsigned char buffer[3];
    int adc_value = 0;

    buffer[0] = 0x06 | ((adcChannel & 0x07) >> 2);
    buffer[1] = ((adcChannel & 0x07) << 6);
    buffer[2] = 0x00;

    digitalWrite(CS_MCP3008, 0);
    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    buffer[1] = 0x0f & buffer[1];
    adc_value = (buffer[1] << 8) | buffer[2];

    digitalWrite(CS_MCP3008, 1);

    return adc_value;
}

int main(void) {
    unsigned char adcChannel_light = 0;
    int adc_value_light = 0;

    float vout_light;
    float vout_oftemp;
    float percentrh = 0;
    float supsiondo = 0;

    cout << "start." <<endl;

    if(wiringPiSetup() == -1) return -1;
    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) return -1;

    pinMode(CS_MCP3008, OUTPUT);

    while(1) {
        adc_value_light = read_mcp(adcChannel_light);

        cout << "light sensor = " << adc_value_light << endl;

        delay(100);
    } 

    return 0;

}
