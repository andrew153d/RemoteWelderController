#include "WifiDebug.h"


void udp_debug::begin(uint32_t unused){
    //udp.connect(IPAddress(255,255,255,255), 1234);
  
    udp.broadcastTo("WifiDebug", port);
}

void udp_debug::print(const char *msg){
     udp.broadcastTo(msg, port);
}

void udp_debug::printf(const char *format, ...){

    char loc_buf[64];
    char * temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
    va_end(copy);
    if(len < 0) {
        va_end(arg);
        return;
    }
    if(len >= (int)sizeof(loc_buf)){  // comparation of same sign type for the compiler
        temp = (char*) malloc(len+1);
        if(temp == NULL) {
            va_end(arg);
            return;
        }
        len = vsnprintf(temp, len+1, format, arg);
    }
    va_end(arg);
    udp.broadcastTo((char*)temp, port);

    //len = write((uint8_t*)temp, len);
    if(temp != loc_buf){
        free(temp);
    }
    //return len;
    
}

void udp_debug::println(const char *msg){
    udp.broadcastTo(msg, port);
}

udp_debug WifiDebug;