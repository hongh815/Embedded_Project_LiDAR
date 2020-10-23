#ifndef SOCKET_DATA_T
#define SOCKET_DATA_T

typedef struct _SOCKET_DATA {
    int fr1, fr2, fr3;
    float num1, num2, num3;
    char message[1024] = {0x00};
    char sendm[1024] = {0x00};
}SOCKET_DATA;

#endif

void DecToHex(SOCKET_DATA *data);
int Socket(SOCKET_DATA *num);
