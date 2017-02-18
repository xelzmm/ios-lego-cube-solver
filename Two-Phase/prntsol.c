#include "globals.h"

static char m[] = "FRUBLD";

void prnt_sol()
{
    int i, j, k;
    max_sol = cur_move;
    printf("Solution (%2d+%2d=%2d):", phase1_cur, cur_move-phase1_cur, cur_move);
    for(i = 0; i < cur_move; i++) {
	j = moves[i];
	k = j & 3;
	j = j >> 2;
	printf(" %c%d", m[j], k + 1);
        final_moves[i] = moves[i];
    }
    final_moves[i] = -1;
    printf("\n");
    fflush(stdout);
}

