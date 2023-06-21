#include <stdio.h>
#include <stdint.h>
#include "map.h"
#include "msp.h"
#include "Clock.h"
#include "section.h"
#include "init.h"
#include "pathfind.h"

#define MOVEFORWARD     0
#define MOVELEFT        2
#define MOVERIGHT       1

void main(void){
    init_all();
    int lst[256] = {-1, };
    // Start point
    map[0][11] = START;
    // Detect map
     while (!(map[current_row][current_col] == START)) {
         arrow = move_until_cross(SPEED, SPEED, SPEED);
         switch(arrow) {
             case FORWARD:
                 // Nothing have to do.
                 break;
             case BACKWARD:
                 // Turn 180 degree.
                 rotate_right_degree(RIGHT_SPEED, RIGHT_DEGREE*2);
                 break;
             case RIGHT:
                 rotate_right_degree(RIGHT_SPEED, RIGHT_DEGREE);
                 break;
             case LEFT:
                 rotate_left_degree(LEFT_SPEED, LEFT_DEGREE);
                 break;
         }
     }

    // find path
    do_astar(map1, root);

    // Hard coding.
    int i = 0;
    for (i; i < sizeof(root)/sizeof(int); i++) {
        switch (root[i]) {
            case MOVEFORWARD:
                straight_no_turn(SPEED, SPEED, SPEED);         
                break;
            case MOVELEFT:
                straight_turn_left(SPEED, SPEED, SPEED);      
                break;
            case MOVERIGHT:
                straight_turn_right(SPEED, SPEED, SPEED);
                break;
        }
    }

    move(0,0);    
}
