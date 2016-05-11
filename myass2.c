#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAXCOLS 100
#define MAXROWS 100
#define NEWLINE 10

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

typedef struct {
     char type;
     int reachable;
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
void solve_maze(maze_t *M, int i, int j);

int
main(int argc, char *argv[]) {
     maze_t M;            /* the maze */

     read_maze(&M);
     print_stage_one(&M);
     assign_reachability(&M);
     print_stage_two(&M);
     print_stage_three(&M);
     /* if (M.hassoln) { */
     /*      label_final_path(&M); */
     /*         print_stage_four(&M); */
     /* } */
     return 0;
}

void
read_maze(maze_t *M) {
     int i,j;
     char ch;
     i=j=0;
     while(scanf("%c",&ch)==1) {
          M->maze_A[i][j].type=ch;
          M->maze_A[i][j].reachable=0;
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
  int j;

  for(j=0; j<M->cols; j++) {
    if(M->maze_A[0][j].type == 46) {
      M->maze_A[0][j].reachable = 1;
      M->maze_A[0][j].mincost = 0;
      if(M->maze_A[1][j].type == 46) {
        M->maze_A[1][j].reachable = 1;
        M->maze_A[1][j].mincost = 1;
        solve_maze(M, 1, j);
      }
    }
  }
}

void
solve_maze(maze_t *M, int i, int j) {
  if(j>0 && M->maze_A[i][j-1].type == 46 && !M->maze_A[i][j-1].reachable) {
    M->maze_A[i][j-1].reachable = 1;
    if(M->maze_A[i][j-1].mincost>M->maze_A[i][j].mincost) {
      M->maze_A[i][j-1].mincost = M->maze_A[i][j].mincost + 1;
    }
    solve_maze(M,i,j-1);
  } else if(i>0 && M->maze_A[i-1][j].type == 46 && !M->maze_A[i-1][j].reachable) {
    M->maze_A[i-1][j].reachable = 1;
    if(M->maze_A[i-1][j].mincost>M->maze_A[i][j].mincost) {
      M->maze_A[i-1][j].mincost = M->maze_A[i][j].mincost + 1;
    }
    solve_maze(M,i-1,j);
  } else if(i<M->rows && M->maze_A[i+1][j].type == 46 && !M->maze_A[i+1][j].reachable) {
    M->maze_A[i+1][j].reachable = 1;
    if(M->maze_A[i+1][j].mincost>M->maze_A[i][j].mincost) {
      M->maze_A[i+1][j].mincost = M->maze_A[i][j].mincost + 1;

    }
    solve_maze(M, i+1, j);
  } else if(j<M->cols && M->maze_A[i][j+1].type == 46 && !M->maze_A[i][j+1].reachable) {
    M->maze_A[i][j+1].reachable = 1;
    if(M->maze_A[i][j+1].mincost>M->maze_A[i][j].mincost) {
      M->maze_A[i][j+1].mincost = M->maze_A[i][j].mincost + 1;
    }
    solve_maze(M,i,j+1);
  }

  /* backtrack if dead end */

  if(j>0 && M->maze_A[i][j-1].type == 46 && M->maze_A[i][j-1].reachable == 1) {
    M->maze_A[i][j-1]reachable(M,i,j-1).reachable = 2;
    solve_maze(M,i,j-1);
  } else if(i>0 && M->maze_A[i-1][j].type == 46 && M->maze_A[i-1][j].reachable == 1) {
    M->maze_A[i-1][j].reachable = 2;
    solve_maze(M,i-1,j);
  } else if(i<M->rows && M->maze_A[i+1][j].type == 46 && M->maze_A[i+1][j].reachable==1) {
    solve_maze(M, i+1, j);
  } else if(j<M->cols && M->maze_A[i][j+1].type == 46 M->maze_A[i][j+1].reachable==1) {
    solve_maze(M,i,j+1);
  }
}
/* void */
/* assign_reachability(maze_t *M) { */
/*   int i,j,k,l; */
/*   for(k=0; k<100; k++){ */
/*      for(i=0; i<M->rows; i++) { */
/*        for(l=0; l<100; l++){ */
/*          for(j=0; j<M->cols; j++) { */
/*            if(M->maze_A[i][j].type==46 && i==0){ */
/*                     M->maze_A[i][j].reachable = 1; */
/*                     M->maze_A[i][j].mincost = 0; */
/*                } else if(M->maze_A[i][j].type==46 && */
/*                          i<(M->rows-1) && (M->maze_A[i+1][j].reachable || */
/*                                            M->maze_A[i-1][j].reachable || */
/*                                            M->maze_A[i][j-1].reachable || */
/*                                            M->maze_A[i][j+1].reachable)) { */
/*                     M->maze_A[i][j].reachable = 1; */
/*                     M->maze_A[i][j].mincost = MIN(MIN(MIN(M->maze_A[i+1][j].mincost, M->maze_A[i-1][j].mincost), */
/*                                                       M->maze_A[i][j+1].mincost), */
/*                                                   M->maze_A[i][j-1].mincost) + 1; */
/*                } else if(M->maze_A[i][j].type==46 && */
/*                          M->maze_A[i-1][j].reachable) { */
/*                     M->maze_A[i][j].reachable = 1; */
/*                     M->hassoln = 1; */
/*                     if((M->maze_A[i-1][j].mincost+1) < M->final_cost){ */
/*                          M->final_cost = M->maze_A[i-1][j].mincost + 1; */
/*                          M->maze_A[i][j].mincost = M->maze_A[i-1][j].mincost+1; */
/*                     } */
/*                } */
/*           } */
/*           if(i!=0 && i!=M->rows) { */
/*                for(; j>0; j--) { */
/*                     if(M->maze_A[i][j].type==46){ */
/*                          if(i<M->rows-1 && (M->maze_A[i+1][j].reachable || */
/*                                           M->maze_A[i-1][j].reachable || */
/*                                           M->maze_A[i][j-1].reachable || */
/*                                           M->maze_A[i][j+1].reachable)) { */
/*                               M->maze_A[i][j].reachable = 1; */
/*                               M->maze_A[i][j].mincost = MIN(MIN(MIN(M->maze_A[i+1][j].mincost, M->maze_A[i-1][j].mincost), */
/*                                                                 M->maze_A[i][j+1].mincost), */
/*                                                             M->maze_A[i][j-1].mincost) + 1; */
/*                          } */
/*                     } */
/*                } */
/*           } */
/*      } */
/*      for(i=M->rows; i>0; i--) { */
/*           for(j=0; j<M->cols; j++) { */
/*                if(M->maze_A[i][j].type==46 && i==0){ */
/*                     M->maze_A[i][j].reachable = 1; */
/*                     M->maze_A[i][j].mincost = 0; */
/*                } else if(M->maze_A[i][j].type==46 && */
/*                          i<(M->rows-1) && (M->maze_A[i+1][j].reachable || */
/*                                            M->maze_A[i-1][j].reachable || */
/*                                            M->maze_A[i][j-1].reachable || */
/*                                            M->maze_A[i][j+1].reachable)) { */
/*                     M->maze_A[i][j].reachable = 1; */
/*                     M->maze_A[i][j].mincost = MIN(MIN(MIN(M->maze_A[i+1][j].mincost, M->maze_A[i-1][j].mincost), */
/*                                                       M->maze_A[i][j+1].mincost), */
/*                                                   M->maze_A[i][j-1].mincost) + 1; */
/*                } else if(M->maze_A[i][j].type==46 && */
/*                          M->maze_A[i-1][j].reachable) { */
/*                     M->maze_A[i][j].reachable = 1; */
/*                     M->hassoln = 1; */
/*                     if((M->maze_A[i-1][j].mincost+1) < M->final_cost){ */
/*                          M->final_cost = M->maze_A[i-1][j].mincost + 1; */
/*                          M->maze_A[i][j].mincost = M->maze_A[i-1][j].mincost+1; */
/*                     } */
/*                } */
/*           } */
/*           if(i!=0 && i!=M->rows) { */
/*                for(; j>0; j--) { */
/*                     if(M->maze_A[i][j].type==46){ */
/*                          if(i<M->rows-1 && (M->maze_A[i+1][j].reachable || */
/*                                           M->maze_A[i-1][j].reachable || */
/*                                           M->maze_A[i][j-1].reachable || */
/*                                           M->maze_A[i][j+1].reachable)) { */
/*                               M->maze_A[i][j].reachable = 1; */
/*                               M->maze_A[i][j].mincost = MIN(MIN(MIN(M->maze_A[i+1][j].mincost, M->maze_A[i-1][j].mincost), */
/*                                                                 M->maze_A[i][j+1].mincost), */
/*                                                             M->maze_A[i][j-1].mincost) + 1; */
/*                          } */
/*                     } */
/*                } */
/*           } */
/*      } */
/*      } */
/*   } */
/* /\* for(j=0; j< M->cols; j++){ *\/ */
/* /\*      if (M->maze_A[0][j] == 46) { *\/ */
/* /\*           M->maze_A[0][j].reachable = 1; *\/ */
/*      /\*           if (M->maze_A[0+1][j] == 46) { *\/ */
/*      /\*                M->maze_A[0+1][j].reachable = 1; *\/ */
/*      /\*           } *\/ */
/*      /\*      } *\/ */
/*      /\* } *\/ */
/*      /\* for(i=1; i< M->rows; i++) { *\/ */
/*      /\*      for(j=0; j< M->cols; j++) { *\/ */
/*      /\*           if(M->maze_A[i][j].reachable) { *\/ */
/*      /\*                if *\/ */
/*      /\*           } *\/ */
/*      /\*      } *\/ */
/*      /\* } *\/ */

/*      /\* solve maze variant *\/ */
/*      /\* for(i=0; i< M->cols; i++) { *\/ */
/*      /\*   if(M->maze_A[0][j].type == 46) { *\/ */
/*      /\*     M->maze_A[0][j].reachable = 1; *\/ */
/*      /\*     if(M->maze_A)solve_maze(M, 1, j); *\/ */
/*      /\*   } *\/ */
/*      /\* } *\/ */
/* } */

/* void */
/* solve_maze(maze_t *M, int i, int j) { */
/*      if() */
/* } */

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
               if(M->maze_A[i][j].reachable) {
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
               if(M->maze_A[i][j].reachable) {
                    if(!(M->maze_A[i][j].mincost % 2)) {
                         printf("%d%d",M->maze_A[i][j].mincost / 10, M->maze_A[i][j].mincost % 10);
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

/* void */
/* label_final_path(maze_t *M) { */
/*      int i,j; */

/*      i=M->rows; */
/*      for(j=M->cols; j>=0; j--) { */
/*           if(M->maze[i][j].mincost == M->final_cost){ */
/*                M->maze[i][j].isfinal = 1; */
/*           } */
/*      } */

/*      for(i=M->rows-1; i>0; i--){ */
/*           for(j=M->cols; j>=0; j--){ */
/*                if */
/*           } */
/*      } */
/* } */
