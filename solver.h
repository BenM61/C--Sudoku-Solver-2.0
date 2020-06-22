#ifndef SOLVER_H_
#define SOLVER_H_

typedef struct sudoku_solver solver;

/*creates a new solver using the length of one row of the board
 *and a pointer to the starting board.
 *Also prints the input board*/
solver* create_solver(int row_len, int ***input_board_ptr);


/*assuming solver is not NULL, freeing the space allocated
 *before. Neither the solver nor the solution will be
 *accessible after this*/
void destroy_solver(solver *solver);

/*assuming solver is not null, if the board is valid-
 *solves the initial board and prints "Solution:" and the resault.
 *If the board is invalid- prints "no sol"*/
void solve(solver *solver);

/*given a pointer to a board, prints the inputed board*/
void print_board(int row_len, int ***board_ptr);

#endif /* SOLVER_H_ */
