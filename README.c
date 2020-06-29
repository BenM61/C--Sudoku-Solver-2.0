/*
 * NOTES & HOW TO USE
 * This is a sudoku solver- will work with any size sudoku grid
 * Place both solver.h, solver.c and this moduls on the same folder.
 *
 * How to
 *
 * As shown below, the input is a pointer to a 2D Integer array.
 * The way to insert numbers is: if the number is given- insert it,
 * otherwise insert '0'. In order to use the solver, create a new solver
 * with "create_solver" with the row_len and a pointer to the grid
 * and use "solve" method on it.
 *
 * The output will be:
 * Valid sudoku (has solution): a solution to the board.
 * Invalid sudoku: prints "no sol" message.
 *
 * enjoy :)
 *
 * I have placed few examples In the main method below
*/
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>


/*small 4x4 board*/
int*** load_table1();

/*classic 9x9 board*/
int*** load_table2();

/*huge 16x16 board*/
int*** load_table3();

int main(int argc, char** argv){
	/*solver *s1 = create_solver(4, load_table1());
	solve(s1);
	destroy_solver(s1);*/

	solver *s2 = create_solver(9, load_table2());
	solve(s2);
	destroy_solver(s2);

	/*solver *s3 = create_solver(16, load_table3());
	solve(s3);
	destroy_solver(s3);*/

}

int*** load_table1(){
	const int len = 4;
	int ***grid_ptr = (int***) malloc(sizeof(int**));
	*grid_ptr = (int**) malloc(sizeof(int*) * len);
	for (int i = 0; i < len; i++){
		(*grid_ptr)[i] = (int*) malloc(sizeof(int) * len);
	}
	int mat[4][4] = {{1,0,0,4}
				 	 ,{0,0,1,0}
					 ,{4,0,2,3}
				 	 ,{0,3,4,0}};
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++){
			(*grid_ptr)[i][j] = mat[i][j];
		}
	}
	return grid_ptr;
}

int*** load_table2(){
	const int len = 9;
	int ***grid_ptr = (int***) malloc(sizeof(int**));
	*grid_ptr = (int**) malloc(sizeof(int*) * len);
		for (int i = 0; i < len ; i++){
			(*grid_ptr)[i] = (int*) malloc(sizeof(int) * len);
		}
	int mat[9][9] = {
				     {0,3,2,0,0,0,0,0,0}
					,{7,4,0,0,0,2,0,0,0}
					,{0,0,0,7,9,0,0,0,0}
					,{6,0,0,0,0,0,9,4,0}
					,{2,0,9,6,0,4,1,0,7}
					,{0,7,4,0,0,0,0,0,6}
					,{0,0,0,0,6,5,0,0,0}
					,{0,0,0,2,0,0,0,5,1}
					,{0,0,0,0,0,0,7,8,0}
					};
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++){
			(*grid_ptr)[i][j] = mat[i][j];
		}
	}
	return grid_ptr;
}

int*** load_table3(){
	const int len = 16;
	int ***grid_ptr = (int***) malloc(sizeof(int**));
	*grid_ptr = (int**) malloc(sizeof(int*) * len);
		for (int i = 0; i < len; i++){
			(*grid_ptr)[i] = (int*) malloc(sizeof(int) * len);
		}
	int mat[16][16] = {
			 {10,0,7,1,0,0,2,0,12,0,0,0,0,8,0,0}
			,{9,4,0,0,0,1,0,0,7,0,0,0,15,0,0,16}
			,{11,0,15,2,9,0,3,14,0,0,1,0,0,12,0,0}
			,{12,0,0,0,0,0,11,6,0,0,15,0,2,7,4,0}
			,{6,0,0,9,4,0,0,0,2,5,0,0,8,11,14,12}
			,{0,10,1,0,0,0,0,3,11,0,0,8,16,0,0,4}
			,{0,0,0,0,0,16,0,2,3,0,13,9,0,5,0,0}
			,{0,0,0,7,1,0,14,0,0,6,0,12,9,0,0,0}
			,{0,0,0,5,10,0,12,0,0,11,0,7,4,0,0,0}
			,{0,0,4,0,13,6,0,15,14,0,3,0,0,0,0,0}
			,{16,0,0,6,14,0,0,5,4,0,0,0,0,3,2,0}
			,{8,15,3,11,0,0,16,4,0,0,0,6,10,0,0,14}
			,{0,6,2,16,0,5,0,0,15,12,0,0,0,0,0,9}
			,{0,0,11,0,0,14,0,0,1,9,0,3,13,15,0,6}
			,{13,0,0,15,0,0,0,8,0,0,5,0,0,0,11,3}
			,{0,0,9,0,0,0,0,1,0,16,0,0,12,4,0,10}};
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++){
			(*grid_ptr)[i][j] = mat[i][j];
		}
	}
	return grid_ptr;
}
