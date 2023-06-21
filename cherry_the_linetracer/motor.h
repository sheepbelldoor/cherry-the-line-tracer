#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdio.h>
#include <stdint.h>
#include <map.h>
#include "msp.h"
#include "section.h"
#include "Clock.h"

// ROTATE FUNCTION

void TA3_N_IRQHandler(void);
void TA3_0_IRQHandler(void);
void rotate_left_degree(int speed, int degree);
void rotate_right_degree(int speed, int degree);

// MOVE FUNCTION
void move(uint16_t leftDuty, uint16_t rightDuty);
void left_forward();
void left_backward();
void right_forward();
void right_backward();
void move_forward(int distance, uint16_t speed); /* The unit of distance is centimeter */

#endif
