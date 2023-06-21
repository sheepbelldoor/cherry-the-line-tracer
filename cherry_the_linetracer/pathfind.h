#ifndef __PATHFIND_H__
#define __PATHFIND_H__

#include <stdio.h>
#include <stdlib.h>
int num = 0;

// direction : 0 북 1 동 2 남 3 서
#define N 0
#define E 1
#define S 2
#define W 3

#define STRAIGHT 0
#define LEFT 3
#define RIGHT 1
#define PREV 2
#define END 4

#define ROW 21
#define COL 21
int my_map[21][21];
int graph[ROW*COL][ROW*COL] = { 0, };
int start[2] = {0,10};
int finish[2] = {20,10};
int navi[100] = {-1,};

typedef struct astar
{
   int found;
   int distance;
   int prev_vertex;
}astar;
astar dtable[ROW*COL];

void mapping(int map[][ROW]);
void init_dtable(void);
int CalcHeuristic(int);
int findshortest(void);
void updatedtable(int v);
void find_dijkstra_vertex(int* end);
void get_pos(int, int*);
int get_pos_val(int, int*);
int find_path(int, int*);
void find_paths(int, int*, int*);
void do_astar(int map[][ROW], int *);

#endif /* __PATHFIND_H__ */
