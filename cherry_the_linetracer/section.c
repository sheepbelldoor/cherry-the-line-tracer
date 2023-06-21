#include "section.h"

// return 1, if there is line
// return 0, if there isn't line
int check_front(){
    P5->OUT |= 0x08;
    P9->OUT |= 0x04;

    P7->DIR = 0xFF;
    P7->OUT = 0xFF;

    Clock_Delay1us(10);

    P7->DIR = 0x00;
    int timerTest;
    int ts4;
    int ts5;
    ts4 = 0;
    ts5 = 0;
    for(timerTest=0 ; timerTest<10000 ; timerTest++) {
        int s4;
        int s5;
        s4 = P7->IN & 0x08; // 4
        s5 = P7->IN & 0x10; // 5
        if(!ts4 && !s4) {
            ts4 = timerTest;
        }
        if(!ts5 && !s5) {
            ts5 = timerTest;
        }
    }
    if (ts4 > 400 && ts4 < 1300 && ts5 > 400 && ts5 < 1300)
        return 1;
    return 0;
}

int move_until_cross (uint16_t left_speed, uint16_t right_speed, uint16_t speed) {
    int leftflag = 0;
    int rightflag = 0;
    int straightflag = 0;

    while(1) {
        P5->OUT |= 0x08;
        P9->OUT |= 0x04;

        P7->DIR = 0xFF;
        P7->OUT = 0xFF;

        Clock_Delay1us(10);

        P7->DIR = 0x00;
        int timerTest;
        int ts1;
        int ts2;
        int ts3;
        int ts4;
        int ts5;
        int ts6;
        int ts7;
        int ts8;
        ts1 = 0;
        ts2 = 0;
        ts3 = 0;
        ts4 = 0;
        ts5 = 0;
        ts6 = 0;
        ts7 = 0;
        ts8 = 0;
        for(timerTest=0 ; timerTest<10000 ; timerTest++) {
            int s1;
            int s2;
            int s3;
            int s4;
            int s5;
            int s6;
            int s7;
            int s8;
            s1 = P7->IN & 0x01; // 1
            s2 = P7->IN & 0x02; // 2
            s3 = P7->IN & 0x04; // 3
            s4 = P7->IN & 0x08; // 4
            s5 = P7->IN & 0x10; // 5
            s6 = P7->IN & 0x20; // 6
            s7 = P7->IN & 0x40; // 7
            s8 = P7->IN & 0x80; // 8

            if(!ts1 && !s1) {
                ts1 = timerTest;
            }
            if(!ts2 && !s2) {
                ts2 = timerTest;
            }
            if(!ts3 && !s3) {
                ts3 = timerTest;
            }
            if(!ts4 && !s4) {
                ts4 = timerTest;
            }
            if(!ts5 && !s5) {
                ts5 = timerTest;
            }
            if(!ts6 && !s6) {
                ts6 = timerTest;
            }
            if(!ts7 && !s7) {
                ts7 = timerTest;
            }
            if(!ts8 && !s8) {
                ts8 = timerTest;
            }
        }

        right_forward();
        left_forward();
        
        // 왼쪽, 오른쪽, 앞에 길이 있는지 확인 후 right hand 방법으로 이동함
        // Check right and left
        if(ts2 > 400 && ts2 < 1300 && ts7 > 400 && ts7 < 1300) {
            move_forward(1, speed);
            straightflag = check_front();
            rightflag = 1;
            leftflag = 1;

            return CROSS;
            // break;
        }
        // Check right
        else if(ts2 > 400 && ts2 < 1300 && ts3 > 400 && ts3 < 1300) {
            move_forward(1, speed);
            straightflag = check_front();
            rightflag = 1;

            return RIGHT;
            // break;
        }
        // Check left
        else if(ts7 > 400 && ts7 < 1300 && ts6 > 400 && ts6 < 1300) {
            move_forward(1, speed);
            straightflag = check_front();
            leftflag = 1;

            if (straightflag == 1)
                return FORWARD;
            else
                return LEFT;
            // break;
        }
        // Check left
        else if(ts5 < 400 && ts4 < 400) {
            return BACKWARD;
            // break;
        }
        else if(ts2 > 400 && ts2 < 1300) {
            left_forward();
            right_backward();
            move(1080, 1000);
        }
        else if (ts7 > 400 && ts7 < 1300) {
            left_backward();
            right_forward();
            move(1080, 1000);
        } 
        else if (ts3 > 400 && ts3 < 1300) {
            move(left_speed-200, right_speed);
        }
        
        else if (ts6 > 400 && ts6 < 1300) {
            move(left_speed, right_speed-200);
        } 
        
        else {
            move(left_speed, right_speed);
        }
        
        // Check map array.
        // 1칸 마다 체크해서 map에 1로 표시
        if(check_left_dist_g > check_cnt_g*16.3702 && check_right_dist_g>check_cnt_g*16.3702) {
            map[current_row][current_col] = 1;
            check_cnt_g++;
            switch (arrow) {
                case DOWN:
                    current_col++;
                    break;
                case UP:
                    current_col--;
                    break;
                case RIGHT:
                    current_row++;
                    break;
                case LEFT:
                    current_row--;
                    break;
            }
        }
        
        
        P5->OUT &= ~0x08;
        P9->OUT &= ~0x04;
        Clock_Delay1ms(10);
    }
}



void straight_turn_right (uint16_t left_speed, uint16_t right_speed, uint16_t speed) {
    while(1) {
        P5->OUT |= 0x08;
        P9->OUT |= 0x04;

        P7->DIR = 0xFF;
        P7->OUT = 0xFF;

        Clock_Delay1us(10);

        P7->DIR = 0x00;
        int timerTest;
        int ts1;
        int ts2;
        int ts3;
        int ts4;
        int ts5;
        int ts6;
        int ts7;
        int ts8;
        ts1 = 0;
        ts2 = 0;
        ts3 = 0;
        ts4 = 0;
        ts5 = 0;
        ts6 = 0;
        ts7 = 0;
        ts8 = 0;
        for(timerTest=0 ; timerTest<10000 ; timerTest++) {
            int s1;
            int s2;
            int s3;
            int s4;
            int s5;
            int s6;
            int s7;
            int s8;
            s1 = P7->IN & 0x01; // 1
            s2 = P7->IN & 0x02; // 2
            s3 = P7->IN & 0x04; // 3
            s4 = P7->IN & 0x08; // 4
            s5 = P7->IN & 0x10; // 5
            s6 = P7->IN & 0x20; // 6
            s7 = P7->IN & 0x40; // 7
            s8 = P7->IN & 0x80; // 8

            if(!ts1 && !s1) {
                ts1 = timerTest;
            }
            if(!ts2 && !s2) {
                ts2 = timerTest;
            }
            if(!ts3 && !s3) {
                ts3 = timerTest;
            }
            if(!ts4 && !s4) {
                ts4 = timerTest;
            }
            if(!ts5 && !s5) {
                ts5 = timerTest;
            }
            if(!ts6 && !s6) {
                ts6 = timerTest;
            }
            if(!ts7 && !s7) {
                ts7 = timerTest;
            }
            if(!ts8 && !s8) {
                ts8 = timerTest;
            }
        }

        right_forward();
        left_forward();

        // 2번 센서가 검정색으로 인식되면 2cm 앞으로 직진 후 90도 우회전
        if((ts2 > 400 && ts2 < 1300)) {
            move_forward(2, speed);
            rotate_right_degree(ROTATE_SPEED, RIGHT_DEGREE);
            move_forward(1, speed);

            P5->OUT &= ~0x08;
            P9->OUT &= ~0x04;
            break;
        }
        // 경로 이탈 시 보완
        else if(ts2 > 400 && ts2 < 1300) {
            left_forward();
            right_backward();
            move(1080, 1000);
        }
        else if (ts7 > 400 && ts7 < 1300) {
            left_backward();
            right_forward();
            move(1080, 1000);
        } 
        else if (ts3 > 400 && ts3 < 1300) {
            move(left_speed-200, right_speed);
        }
        
        else if (ts6 > 400 && ts6 < 1300) {
            move(left_speed, right_speed-200);
        } 
        else {
            move(left_speed, right_speed);
        }
        
        P5->OUT &= ~0x08;
        P9->OUT &= ~0x04;

        Clock_Delay1ms(10);
    }
}

// 갈림길이 있어도 직진
void straight_no_turn(uint16_t left_speed, uint16_t right_speed, uint16_t speed) {

    while(1) {
        P5->OUT |= 0x08;
        P9->OUT |= 0x04;

        P7->DIR = 0xFF;
        P7->OUT = 0xFF;

        Clock_Delay1us(10);

        P7->DIR = 0x00;
        int timerTest;
        int ts1;
        int ts2;
        int ts3;
        int ts4;
        int ts5;
        int ts6;
        int ts7;
        int ts8;
        ts1 = 0;
        ts2 = 0;
        ts3 = 0;
        ts4 = 0;
        ts5 = 0;
        ts6 = 0;
        ts7 = 0;
        ts8 = 0;
        for(timerTest=0 ; timerTest<10000 ; timerTest++) {
            int s1;
            int s2;
            int s3;
            int s4;
            int s5;
            int s6;
            int s7;
            int s8;
            s1 = P7->IN & 0x01; // 1
            s2 = P7->IN & 0x02; // 2
            s3 = P7->IN & 0x04; // 3
            s4 = P7->IN & 0x08; // 4
            s5 = P7->IN & 0x10; // 5
            s6 = P7->IN & 0x20; // 6
            s7 = P7->IN & 0x40; // 7
            s8 = P7->IN & 0x80; // 8



            if(!ts1 && !s1) {
                ts1 = timerTest;
            }
            if(!ts2 && !s2) {
                ts2 = timerTest;
            }
            if(!ts3 && !s3) {
                ts3 = timerTest;
            }
            if(!ts4 && !s4) {
                ts4 = timerTest;
            }
            if(!ts5 && !s5) {
                ts5 = timerTest;
            }
            if(!ts6 && !s6) {
                ts6 = timerTest;
            }
            if(!ts7 && !s7) {
                ts7 = timerTest;
            }
            if(!ts8 && !s8) {
                ts8 = timerTest;
            }
        }

        right_forward();
        left_forward();

        if(ts4 < 300) {
            left_backward();
            right_forward();
            move(left_speed, right_speed);
        }
        else if (ts5 < 300) {
            left_forward();
            right_backward();
            move(left_speed, right_speed);
        }
        else if(ts2 > 400 || ts7>400) {

            move_forward(2, speed);
            P5->OUT &= ~0x08;
            P9->OUT &= ~0x04;
            break;
        }
        else if (ts7 > 400 && ts7 < 1300) {
            left_backward();
            right_forward();
            move(left_speed, right_speed);
        } 
        else if(ts2 > 400 && ts2 < 1300) {
            left_forward();
            right_backward();
            move(left_speed, right_speed);
        }
        else if (ts3 > 400 && ts3 < 1300) {
            move(left_speed-200, right_speed);
        }
        else if (ts6 > 400 && ts6 < 1300) {
            move(left_speed, right_speed-200);
        } 
        
        else {
            move(left_speed, left_speed);
        }

        P5->OUT &= ~0x08;
        P9->OUT &= ~0x04;

        Clock_Delay1ms(10);
    }
}

void straight_turn_left(uint16_t left_speed, uint16_t right_speed, uint16_t speed) {
    while(1) {
        P5->OUT |= 0x08;
        P9->OUT |= 0x04;

        P7->DIR = 0xFF;
        P7->OUT = 0xFF;

        Clock_Delay1us(10);

        P7->DIR = 0x00;
        int timerTest;
        int ts1;
        int ts2;
        int ts3;
        int ts4;
        int ts5;
        int ts6;
        int ts7;
        int ts8;
        ts1 = 0;
        ts2 = 0;
        ts3 = 0;
        ts4 = 0;
        ts5 = 0;
        ts6 = 0;
        ts7 = 0;
        ts8 = 0;
        for(timerTest=0 ; timerTest<10000 ; timerTest++) {
            int s1;
            int s2;
            int s3;
            int s4;
            int s5;
            int s6;
            int s7;
            int s8;
            s1 = P7->IN & 0x01; // 1
            s2 = P7->IN & 0x02; // 2
            s3 = P7->IN & 0x04; // 3
            s4 = P7->IN & 0x08; // 4
            s5 = P7->IN & 0x10; // 5
            s6 = P7->IN & 0x20; // 6
            s7 = P7->IN & 0x40; // 7
            s8 = P7->IN & 0x80; // 8



            if(!ts1 && !s1) {
                ts1 = timerTest;
            }
            if(!ts2 && !s2) {
                ts2 = timerTest;
            }
            if(!ts3 && !s3) {
                ts3 = timerTest;
            }
            if(!ts4 && !s4) {
                ts4 = timerTest;
            }
            if(!ts5 && !s5) {
                ts5 = timerTest;
            }
            if(!ts6 && !s6) {
                ts6 = timerTest;
            }
            if(!ts7 && !s7) {
                ts7 = timerTest;
            }
            if(!ts8 && !s8) {
                ts8 = timerTest;
            }
        }

        right_forward();
        left_forward();


        if((ts7 > 400 && ts7 < 1300)  && (ts6 > 400 && ts6 < 1300)) {
            move_forward(1,SPEED);
            rotate_left_degree(ROTATE_SPEED, LEFT_DEGREE);
            move_forward(1,SPEED);
            P5->OUT &= ~0x08;
            P9->OUT &= ~0x04;
            break;
        }
        else if (ts6 > 400 && ts6 < 1300) {
            left_backward();
            right_forward();
            move(left_speed, right_speed);
        } 
         else if(ts2 > 400 && ts2 < 1300) {
            left_forward();
            right_backward();
            move(left_speed, right_speed);
        }
        else if (ts3 > 400 && ts3 < 1300) {
            move(left_speed-200, right_speed);
        }
        else if (ts5 > 400 && ts5 < 1300) {
            move(left_speed, right_speed-200);
        } 
        else {
            move(left_speed, right_speed);
        }

        P5->OUT &= ~0x08;
        P9->OUT &= ~0x04;

        Clock_Delay1ms(10);
    }
}
