#ifndef GPIO_H
#define GPIO_H

#include "stdio.h"
#include "Arduino.h"

namespace gpio{
    
    constexpr uint16_t STATUS_LED = 13;

    inline void init_common_gpio(){
        pinMode(STATUS_LED, OUTPUT);
    }
}


#endif