#include "globals.h"

char U[3][3], D[3][3], R[3][3], L[3][3], F[3][3], B[3][3];
char cube[3][3][3][2]; /* resp coordinates and number/twist */
char tcube[3][3][3]; /* after phase 1 */
char moves[MAX_MOVES];
char final_moves[MAX_MOVES + 1];
int cur_move, phase1_cur, max_sol, do_max20;

