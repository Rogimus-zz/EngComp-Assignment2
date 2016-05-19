#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAXCOLS 100
#define MAXROWS 100
#define NEWLINE 10

typedef struct {
     char type;
     int mincost;
     int isfinal;
} cell_t;

typedef struct {
     cell_t maze_A[MAXCOLS][MAXROWS];
     int hassoln;
     int rows;
     int cols;
     int final_cost;
} maze_t;




void read_maze(maze_t *M);
void print_stage_one(maze_t *M);
void assign_reachability(maze_t *M);
void print_stage_two(maze_t *M);
void print_stage_three(maze_t *M);
void label_final_path(maze_t *M);
void print_stage_four(maze_t *M);

int
main(int argc, char *argv[]) {
     maze_t M;            /* the maze */

     read_maze(&M);
     print_stage_one(&M);
     assign_reachability(&M);
     print_stage_two(&M);
     print_stage_three(&M);
     if (M.hassoln) {
          label_final_path(&M);
          print_stage_four(&M);
     }
     return 0;
}

void
read_maze(maze_t *M) {
     int i,j;
     char ch;
     i=j=0;
     while(scanf("%c",&ch)==1) {
          M->maze_A[i][j].type=ch;
          M->maze_A[i][j].mincost=INT_MAX;
          M->final_cost = INT_MAX;
          M->maze_A[i][j].isfinal=0;
          if(ch == NEWLINE) { 
               i++;
               M->cols=j;
               j=0;
          } else {
               j++;
          }
     }
     M->rows=i;
     M->hassoln=0;
}


void
print_stage_one(maze_t *M) {
     int i,j;
     maze_t maze;
     maze=*M;
     printf("Stage 1\n");
     printf("=======\n");
     printf("maze has %d rows and %d columns\n",
            maze.rows,
            maze.cols);
     for(i=0; i<maze.rows; i++) {
          for(j=0; j<maze.cols; j++) {
               printf("%c%c", maze.maze_A[i][j].type, maze.maze_A[i][j].type);
          }
          printf("\n");
     }
     printf("\n");
}

void
assign_reachability(maze_t *M) {
  int j,i,
    changes;

  for(j=0; j<M->cols; j++) {
    if(M->maze_A[0][j].type == 46) {
      M->maze_A[0][j].mincost = 0;
      if(M->maze_A[1][j].type == 46) {
        M->maze_A[1][j].mincost = 1;
      }
    }
  }

  changes = 1;
  while(changes){
       changes=0;
       for(i=1; i<M->rows; i++){
            for(j=0; j<M->cols; j++){
                 if(M->maze_A[i][j].type == 46 && M->maze_A[i][j].mincost<INT_MAX){
                      if(j>0){
                           if(M->maze_A[i][j-1].type == 46 && M->maze_A[i][j-1].mincost > M->maze_A[i][j].mincost+1) {
                                M->maze_A[i][j-1].mincost = M->maze_A[i][j].mincost+1;
                                changes++;
                           }
                      }

                      if(i<M->rows){
                           if (M->maze_A[i+1][j].type == 46 && M->maze_A[i+1][j].mincost> M->maze_A[i][j].mincost+1) {
                                M->maze_A[i+1][j].mincost = M->maze_A[i][j].mincost+1;
                                changes++;
                           }
                      }
                      if(j<M->cols){
                           if (M->maze_A[i][j+1].type == 46 && M->maze_A[i][j+1].mincost> M->maze_A[i][j].mincost+1) {
                                M->maze_A[i][j+1].mincost = M->maze_A[i][j].mincost+1;
                                changes++;
                           }
                      }
                      if(i>0){
                           if (M->maze_A[i-1][j].type == 46 && M->maze_A[i-1][j].mincost> M->maze_A[i][j].mincost+1) {
                                M->maze_A[i-1][j].mincost = M->maze_A[i][j].mincost+1;
                                changes++;
                           }
                      }
                 }
            }
       }
  }
  /* determine hassoln */
  i = M->rows-1;
  for(j=0; j<=M->cols; j++) {
    if(M->maze_A[i][j].mincost != INT_MAX) {
      M->hassoln = 1;
      if(M->maze_A[i][j].mincost < M->final_cost) {
        M->final_cost = M->maze_A[i][j].mincost;
      }
    }
  }
}

void
print_stage_two(maze_t *M) {
     int i,j;
     printf("Stage 2\n");
     printf("=======\n");
     if(M->hassoln) {
          printf("maze has a solution\n");
     } else {
          printf("maze has no solution\n");
     }
     for(i=0; i<M->rows; i++) {
          for(j=0; j<M->cols; j++) {
               if(M->maze_A[i][j].mincost != INT_MAX) {
                    printf("++");
               } else if(M->maze_A[i][j].type==46) {
                    printf("--");
               } else {
                    printf("%c%c", M->maze_A[i][j].type, M->maze_A[i][j].type);
               }
          }
          printf("\n");
     }
     printf("\n");
}

void
print_stage_three(maze_t *M) {
     int i,j;
     printf("Stage 3\n");
     printf("=======\n");
     if(M->hassoln) {
          printf("maze has a solution with cost %d\n", M->final_cost);
     } else {
          printf("maze has no solution\n");
     }
     for(i=0; i<M->rows; i++) {
          for(j=0; j<M->cols; j++) {
               if(M->maze_A[i][j].mincost != INT_MAX) {
                    if(!(M->maze_A[i][j].mincost % 2)) {
                      printf("%d%d",((M->maze_A[i][j].mincost %100) - (M->maze_A[i][j].mincost %10))/10, M->maze_A[i][j].mincost % 10);
                    } else {
                         printf("++");
                    }
               } else if(M->maze_A[i][j].type==46) {
                 printf("--");
               } else {
                 printf("%c%c", M->maze_A[i][j].type, M->maze_A[i][j].type);
               }
          }
          printf("\n");
     }
     printf("\n");
}

void
label_final_path(maze_t *M) {
     int i,j,
          changes;

     i=M->rows-1;
     for(j=0; j<M->cols; j++) {
          if(M->maze_A[i][j].mincost == M->final_cost){
               M->maze_A[i][j].isfinal = 1;
               M->maze_A[i+1][j].isfinal = 1;
               break;
          }
     }

     changes=1;
     while(changes){
          changes=0;
          for(i=M->rows-1; i>=0; i--){
               for(j=0; j<M->cols-1; j++){
                    if(M->maze_A[i][j].isfinal){
                         if(j>0 && M->maze_A[i][j-1].mincost == M->maze_A[i][j].mincost-1){
                              if(!M->maze_A[i][j-1].isfinal){
                                   M->maze_A[i][j-1].isfinal=1;
                                   changes++;
                              }
                         } else if(i>0 && M->maze_A[i-1][j].mincost == M->maze_A[i][j].mincost-1 ) {
                              if(!M->maze_A[i-1][j].isfinal){
                                   M->maze_A[i-1][j].isfinal=1;
                                   changes++;
                              }
                         } else if(i<M->rows-1 && M->maze_A[i+1][j].mincost == M->maze_A[i][j].mincost-1 ) {
                              if(!M->maze_A[i+1][j].isfinal){
                                   M->maze_A[i+1][j].isfinal=1;
                                   changes++;
                              }
                         } else if(j<M->cols-1 && M->maze_A[i][j+1].mincost == M->maze_A[i][j].mincost-1 ) {
                              if(!M->maze_A[i][j+1].isfinal){
                                   M->maze_A[i][j+1].isfinal=1;
                                   changes++;
                              }
                         }
                    }
               }
          }
     }
}

void
print_stage_four(maze_t *M) {
     int i,j;
     printf("Stage 4\n");
     printf("=======\n");
     printf("maze solution\n");
     for(i=0; i<M->rows; i++) {
          for(j=0; j<M->cols; j++) {
               if(M->maze_A[i][j].mincost != INT_MAX) {
                    if(M->maze_A[i][j].isfinal){
                         if(!(M->maze_A[i][j].mincost % 2)) {
                              printf("%d%d",((M->maze_A[i][j].mincost %100) - (M->maze_A[i][j].mincost %10))/10, M->maze_A[i][j].mincost % 10);
                         } else {
                              printf("..");
                         }
                    }
                    else {
                         printf("  ");
                    }
               } else if(M->maze_A[i][j].type==46) {
                    printf("--");
               } else {
                    printf("%c%c", M->maze_A[i][j].type, M->maze_A[i][j].type);
               }
          }
          printf("\n");
     }
     printf("\n");
}
