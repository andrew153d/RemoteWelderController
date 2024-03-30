#pragma once
#include "config.h"


#ifdef DEBUG_PROGRAM
    #define DEBUG_PRINT(...)                  \
        {                                     \
            DEBUG_PRINTER.print(__VA_ARGS__); \
        }
    #define DEBUG_PRINTLN(...)                  \
        {                                       \
            DEBUG_PRINTER.println(__VA_ARGS__); \
        }
    #define DEBUG_PRINTF(...)                  \
        {                                      \
            DEBUG_PRINTER.printf(__VA_ARGS__); \
        }
    #define DEBUG_BEGIN(...)                  \
        {                                     \ 
            DEBUG_PRINTER.begin(__VA_ARGS__); \
        }
#else
    #define DEBUG_PRINT(...) \
        {                    \
        }
    #define DEBUG_PRINTLN(...) \
        {                      \
        }
    #define DEBUG_PRINTF(...) \
        {                     \
        }
    #define DEBUG_BEGIN(...) \
        {                    \
        }
#endif

#include "AsyncUDP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Arduino.h"

class udp_debug{

    private:    
    const uint16_t port = 4645;
    AsyncUDP udp;

    public:
    void begin(uint32_t unused);
    void println(const char *msg);
    void print(const char *msg);
    void printf(const char *format, ...);
};

extern udp_debug WifiDebug;