#ifndef __SECTION_H__
#define __SECTION_H__

#include <stdio.h>
#include <stdint.h>
#include "map.h"
#include "motor.h"
#include "Clock.h"
#include "msp.h"


#define SPEED 1000
#define LEFT_SPEED 1580
#define RIGHT_SPEED 1500
#define LOW_SPEED 2700
#define MAX_SPEED 4000
#define ROTATE_SPEED 1200
#define RIGHT_DEGREE 85 
#define LEFT_DEGREE 80

int check_front();
int move_until_cross (uint16_t left_speed, uint16_t right_speed, uint16_t speed);
void straight_turn_right (uint16_t left_speed, uint16_t right_speed, uint16_t speed);
void straight_no_turn(uint16_t left_speed, uint16_t right_speed, uint16_t speed);
void straight_turn_left(uint16_t left_speed, uint16_t right_speed, uint16_t speed);

#endif /* __SECTION_H__ */
