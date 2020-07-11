#include "solver.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct sudoku_solver{
    /*length of one row of the board*/
    int N;
    /*a pointer to the solution board*/
    int ***sol_ptr;
}solver;

solver* create_solver(int row_len, int ***input_board_ptr){
    solver *s = (solver*) malloc(sizeof(solver));

    /*row_len is a variable, so we have to declare everything dynamically */
    /*allocating sol as a pointer to a matrix, and the matrix rows
     *is an array of pointers (1 out of 2D)*/
    int ***sol = (int***) malloc(sizeof(int**));
    *sol = (int**) malloc(row_len * sizeof(int*));
    for (int i = 0; i < row_len; i++){
        /*allocating every row (the second D)
         *while making sol equal to input_board*/
       (*sol)[i] = (int*) malloc(row_len * sizeof(int));
        for (int j = 0; j < row_len; j++){
        	(*sol)[i][j] =  (*input_board_ptr)[i][j];
        }
    }
    s->N = row_len;
    s->sol_ptr = sol;

    /*printing the input board*/
    printf("Input board:\n");
    print_board(s->N, s->sol_ptr);
    return s;
}

void destroy_solver(solver *s){
    for (int i = 0; i < s->N; i++){
        free((*(s->sol_ptr))[i]);
    }
    free(*(s->sol_ptr));
    free(s->sol_ptr);
    free(s);
}

int* calc_next(int x, int y, int *next, solver *s);

bool isSafe(int x, int y, int val, solver *s);

bool solve_rec(int x, int y, solver *s);

void solve(solver *s){
	int n = s->N;
    int next[2];
    int ***sp = s->sol_ptr;

	//edge case
	if (n == 1){
		(*sp)[0][0] = 1;
    	printf("Solution:\n");
    	print_board(n, sp);
        return;
	}

    //find first empty space
    if ((*sp)[0][0] == 0){
        next[0] = 0;
        next[1] = 0;
    }
    else{
       calc_next(0, 0, next, s);
    }
    int nextX = next[0];
    int nextY = next[1];
    for (int i = 1; i <= n; i++){
        if (isSafe(nextX, nextY, i, s)){
            (*sp)[nextX][nextY] = i;
            if(solve_rec(nextX, nextY, s)){
            	printf("Solution:\n");
            	print_board(n, sp);
                return;
            }
            //backtrack
            (*sp)[nextX][nextY] = 0;
        }
    }
    printf("no sol\n");
    return;
}

bool solve_rec(int x, int y, solver *s){
    int n = s->N;
    int next[2];
    int ***sp = s->sol_ptr;

    /*find next empty space*/
    calc_next(x, y, next, s);

    int nextX = next[0];
    int nextY = next[1];

    /*reached end of board*/
    if (nextX == -1 && nextY == -1){
        return true;
    }

    for (int i = 1; i <= n; i++){
        if (isSafe(nextX, nextY, i, s)){
            (*sp)[nextX][nextY] = i;

            if(solve_rec(nextX, nextY, s)){
                return true;
            }
            //backtrack
            (*sp)[nextX][nextY] = 0;
        }
    }
    return false;
}
/*checks if val is a valit value for the x,y entry*/
bool isSafe(int x, int y, int val, solver *s){
    int n = s->N;
    int ***sp = s->sol_ptr;
    /*check row*/
    for (int j = 0; j < n; j++){
        if ((*sp)[x][j] == val){
            return false;
        }
    }

    /*check col*/
    for (int i = 0; i < n; i++){
        if ((*sp)[i][y] == val){
            return false;
        }
    }

    /*check block
     *the index of a block in a grid is just like the index
     *the of entry in block. In sudoku, there are bs*bs blocks,
     *the and each has bs rows and bs columns*/
    int bs = sqrt(n); // block size
    int block_x_index = x / bs;
    int block_y_index = y / bs;
    for(int i = block_x_index * bs; i < bs * (block_x_index + 1); i++){
        for(int j = block_y_index * bs; j < bs * (block_y_index + 1); j++){
            if ((*sp)[i][j] == val){
                return false;
            }
        }
    }
    return true;
}

/*given valid x,y (a valid entry in the solution grid) and a
 * non-zero val to look for:
 *if there is an empty place in the grid after x,y,
 *the function finds the first one.
 *otherwise, returns [-1,-1] */
int* calc_next(int x, int y, int *next, solver *s){
    int n = s->N;
    int ***sp = s->sol_ptr;
    do{
        if (y == n - 1){
            x++;
            y = 0;
        }
        else{
            y++;
        }
     /*checkes for empty space in the grid or out-of-grid space.
      *it's sufficient to only check x since 0 <= y < n always
      */
        if (!(y < n && x < n)){
        	break;
        }
    } while ((*sp)[x][y] != 0);

    /*if reached end of grid*/
    if (x == n){
    	x = -1;
    	y = -1;
    }
    next[0] = x;
    next[1] = y;
    return next;
}

void print_board(int row_len, int ***board_ptr){
    int n = row_len;
    int bs = sqrt(n); // block size
    char *curr = "g";
    int rows_passed, col_passed;
    for (int i = 0; i < n + bs - 1; i++){
        for (int j = 0; j < n + bs - 1; j++){
            //if it's a grid row
            if (i == bs || ((i - bs) % (bs + 1)) == 0){
                //if it's also a grid col
                if (j == bs || ((j - bs) % (bs + 1) == 0)){
                    curr = "+";
                }
                else{
                    curr = "--";
                }
            }
            //if it's only a grid col
            else if (j == bs || ((j - bs) % (bs + 1) == 0)){
                curr = "|";
            }
            else{
                rows_passed = i / (bs + 1);
                col_passed = j / (bs + 1);
                int num = (*board_ptr)[i-rows_passed][j-col_passed];
		    
                /*printing num as a string because we cant print
                 * numbers > 10 as digits (also assuming num < 999)*/
		char num_str[4];
                sprintf(num_str, "%d,", num);
                curr = num_str;
            }
            printf("%s",curr);
        }
        printf("\n");
    }
    printf("\n");
}
