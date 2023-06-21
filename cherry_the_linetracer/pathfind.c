#include "pathfind.h"

void mapping(int map[][ROW])
{
   for (int i = 0; i<COL; i++)
   {
      for (int j = 0; j<ROW; j++)
      {
         my_map[i][j] = 0;
         if(map[i][j] == 2){
            my_map[i][j] = 1;
         }
         if (map[i][j] == 1)
         {
            my_map[i][j] = 1;
            if ((i - 1) >= 0 && map[i - 1][j] == 1)//상
            {
               int me = ROW * i + j;
               int neighber = ROW * (i - 1) + j;
               graph[me][neighber] = 1;
            }
            if ((i + 1) <= ROW-1 && map[i + 1][j] == 1)//하
            {
               int me = ROW * i + j;
               int neighber = ROW * (i + 1) + j;
               graph[me][neighber] = 1;
            }
            if ((j - 1) >= 0 && map[i][j - 1] == 1)//좌
            {
               int me = ROW * i + j;
               int neighber = ROW * i + (j - 1);
               graph[me][neighber] = 1;
            }
            if ((j + 1) <= ROW-1 && map[i][j + 1] == 1)//우
            {
               int me = ROW * i + j;
               int neighber = ROW * i + (j + 1);
               graph[me][neighber] = 1;
            }
         }
      }
   }
}


void init_dtable()
{
   int start_idx = start[0] * ROW + start[1];
   for (int i = 0; i < COL; i++)
   {
      for (int j = 0; j < ROW; j++)
      {
         int idx = i*ROW + j;
         if (idx == start_idx)
         {
            dtable[idx].found = 1;
            dtable[idx].prev_vertex = -1;
            continue;
         }
         dtable[idx].found = 0;
         int diff = i - start[0] + j - start[1];
         if ( (diff == 1 || diff == -1) && (i == start[0] || j == start[1]))
         {
            dtable[idx].distance = 1;
            dtable[idx].prev_vertex = start_idx;
         }
         else
         {
            dtable[idx].distance = -999;
            dtable[idx].prev_vertex = -1;
         }
      }
   }   
}
int CalcHeuristic(int i)
{
   int x = i % ROW;
   int y = i/ ROW;

   int dx = (x - finish[1]);
   int dy = (y - finish[0]);

   return ((dx*dx) + (dy*dy));
}
int findshortest()
{
   int shortest = 99999;//INT_MAX
   int shortest_v = -1;

   for (int i = 0; i < ROW*COL; i++)
   {
      if (dtable[i].found == 0 && dtable[i].distance>0)
      {
         int dist = dtable[i].distance + CalcHeuristic(i);
         if (shortest > dist)
         {
            shortest = dist;
            shortest_v = i;
         }
      }
   }
   return shortest_v;
}
void updatedtable(int v)
{
   for (int i = 0; i < ROW*COL; i++)
   {
      int ii = i / ROW;
      int ji = i%ROW;
      if (dtable[i].found == 0 && graph[v][i] == 1)
      {
         if (dtable[i].distance > dtable[v].distance +1 || dtable[i].distance < 0)
         {
            dtable[i].prev_vertex = v;
            dtable[i].distance = dtable[v].distance + 1;
         }
      }
   }
}

void find_dijkstra_vertex(int* end)
{
   my_map[end[0]][end[1]] = 2;
   int idx = end[0] * ROW + end[1];
   while (1)
   {
      int prev = dtable[idx].prev_vertex;
      if (prev==-1)
         break;
      else
      {
         my_map[prev / ROW][prev % ROW] = 2;
         idx = prev; 
      }
   }
}

void get_pos(int direction, int* pos){
   switch(direction){
      case N:
         if(pos[0] == 0) return;
         pos[0] = pos[0] - 1;
         return;
      case E:
         if(pos[1] == COL) return;
         pos[1] = pos[1] + 1;
         return;
      case S:
         if(pos[0] == ROW) return;
         pos[0] = pos[0] + 1;
         return;
      case W:
         if(pos[1] == 0) return;
         pos[1] = pos[1] - 1;
         return;
   }
}
int get_pos_val(int direction, int* pos){
   switch(direction){
      case N:
         if(pos[0] == 0) return 0;
         return my_map[pos[0] - 1][pos[1]];
      case E:
         if(pos[1] == COL) return 0;
         return my_map[pos[0]][pos[1] + 1];
      case S:
         if(pos[0] == ROW) return 0;
         return my_map[pos[0] + 1][pos[1]];
      case W:
         if(pos[1] == 0) return 0;
         return my_map[pos[0]][pos[1] - 1];
   }
}
int find_path(int direction, int* pos)
{
   if(pos[0] == finish[0] && pos[1] == finish[1]) return END;
   int straight = direction;
   int prev = (direction + PREV) % 4;
   int right = (direction + RIGHT) % 4;
   int left = (direction + LEFT) % 4;

   if(get_pos_val(straight, pos) == 2 && get_pos_val(left, pos) == 0 && get_pos_val(right, pos) == 0) return -1;
   if(get_pos_val(straight, pos) == 2) return STRAIGHT;
   if(get_pos_val(left, pos) == 2) return LEFT;
   if(get_pos_val(right, pos) == 2) return RIGHT;
}

void find_paths(int direction, int* pos, int* root){
   int cur_dir = direction;
   int cur[2];
   cur[0] = pos[0];
   cur[1] = pos[1];
   int dir;
   int i = 0;
   while(1){
      dir = find_path(cur_dir, cur);
      if (dir == END) {
         root[i] = -1;
         break;
      }
      root[i] = 0;
      if(dir == STRAIGHT) root[i] = 0;
      else if(dir == RIGHT) root[i] = 1;
      else if(dir == LEFT) root[i] = 2;
      else i--;
      if(dir != -1) {
         cur_dir = (cur_dir + dir) % 4;
      }   
      get_pos(cur_dir, cur);
      i++;
   }
}

// map이랑 return 받을 root 배열 넣으시면 됩니다. 사용법은 main함수 참고
void do_astar(int map[][ROW], int* root)
{
   mapping(map);
   init_dtable();
   int next_vertex = -1;
   while ((next_vertex = findshortest()) != -1)
   {
      if (next_vertex == finish[0] * ROW + finish[1])
         break;
      dtable[next_vertex].found = 1;
      updatedtable(next_vertex);
      num++;
   }
   find_dijkstra_vertex(finish);
   
   int cur_pos[2] = {start[0],start[1]};
   int cur_dir = 2;
   find_paths(cur_dir, cur_pos, root);
}
