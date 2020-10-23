#include "socket_transport.h"
#include <cstring>
#include <stdio.h>

void DecToHex(SOCKET_DATA *data) {
        sprintf(data->message, "%d", data->fr1);
        strcat(data->sendm, data->message);
        
        sprintf(data->message, "%d", data->fr2);
        strcat(data->sendm, data->message);
        
        sprintf(data->message, "%d", data->fr3);
        strcat(data->sendm, data->message);
}

