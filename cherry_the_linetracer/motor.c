#include "motor.h"

// Function used to determine the turning radius.
void TA3_N_IRQHandler(void) {
    TIMER_A3->CCTL[1] &= ~0x0001;
    left_count_g++;
    // check_left_dist_g++;
}
void TA3_0_IRQHandler(void) {
    TIMER_A3->CCTL[0] &= ~0x0001;
    right_count_g++;
    // check_right_dist_g++;
}

void rotate_left_degree(int speed, int degree) {
    left_count_g = 0;
    right_count_g = 0;
    int count = degree * 2;
    // rotate by degree 
    while(1) {
        left_backward();
        right_forward();
        move(speed,speed);
        if(left_count_g>count && right_count_g>count) {
            move(0,0);
            break;
        }
    }
}
void rotate_right_degree(int speed, int degree) {
    left_count_g = 0;
    right_count_g = 0;
    int count = degree * 2;
    // rotate by degree 
    while(1) {
        left_forward();
        right_backward();
        move(speed,speed);
        if(left_count_g>count && right_count_g>count) {
            move(0,0);
            break;
        }
    }
}


// Move function parameter is move speed.
void move(uint16_t leftDuty, uint16_t rightDuty) {
    P3->OUT |= 0xC0;
    TIMER_A0->CCR[3] = leftDuty;
    TIMER_A0->CCR[4] = rightDuty;
}

// Set wheel's direction of rotation.
void left_forward() {
    P5->OUT &= ~0x10;
}
void left_backward() {
    P5->OUT |= 0x10;
}
void right_forward() {
    P5->OUT &= ~0x20;
}
void right_backward() {
    P5->OUT |= 0x20;
}
/* 16.3702 is 1cm */
void move_forward(int distance, uint16_t speed) {

    P3->OUT |= 0xC0;
    TIMER_A0->CCR[3] = speed;
    TIMER_A0->CCR[4] = speed;

    left_forward();
    right_forward();
    left_count_g = 0;
    right_count_g = 0;

    int dist = distance * 16.3702;

    while(1) {
        move(speed+80, speed);
        if(left_count_g>dist && right_count_g>dist) {
            move(0,0);
            break;
        }
    }
}
