#ifndef __INIT_H__
#define __INIT_H__

#include "Clock.h"
#include "msp.h"
#include <stdio.h>
#include <stdint.h>


// Motor INITIALIZE
void pwm_init34(uint16_t period, uint16_t duty3, uint16_t duty4);
void motor_init(void);
void timer_A3_capture_init(void);


// Switch INITIALIZE
void switch_init(void);
void ir_sensor_init(void);
    
// INITIALZE all of things.
void init_all(void);

#endif // __INIT_H__
