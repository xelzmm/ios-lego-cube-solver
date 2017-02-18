#include "permcube.h"

void perm_cube()
{
int i, j, k, tmp;

    /* Phase 2 does not concern itself with twists and flips */
    for(i = 0; i < 3; i++) {
	for(j = 0; j < 3; j++) {
	    for(k = 0; k < 3; k++) {
		tcube[i][j][k] = cube[i][j][k][0];
	    }
	}
    }
    for(i = 0; i < cur_move; i++) {
	j = moves[i];
	k = j & 3;
	j = j >> 2;
	while(k-- >= 0) {
	    switch(j) {
	    case 0:    /* F */
		tmp = tcube[0][2][0];
		tcube[0][2][0] = tcube[2][2][0];
		tcube[2][2][0] = tcube[2][2][2];
		tcube[2][2][2] = tcube[0][2][2];
		tcube[0][2][2] = tmp;
		tmp = tcube[0][2][1];
		tcube[0][2][1] = tcube[1][2][0];
		tcube[1][2][0] = tcube[2][2][1];
		tcube[2][2][1] = tcube[1][2][2];
		tcube[1][2][2] = tmp;
		break;
	    case 1:    /* R */
		tmp = tcube[0][2][2];
		tcube[0][2][2] = tcube[2][2][2];
		tcube[2][2][2] = tcube[2][0][2];
		tcube[2][0][2] = tcube[0][0][2];
		tcube[0][0][2] = tmp;
		tmp = tcube[0][1][2];
		tcube[0][1][2] = tcube[1][2][2];
		tcube[1][2][2] = tcube[2][1][2];    
		tcube[2][1][2] = tcube[1][0][2];
		tcube[1][0][2] = tmp;
		break;
	    case 2:    /* U */
		tmp = tcube[0][0][0];
		tcube[0][0][0] = tcube[0][2][0];
		tcube[0][2][0] = tcube[0][2][2];
		tcube[0][2][2] = tcube[0][0][2];
		tcube[0][0][2] = tmp;
		tmp = tcube[0][0][1];
		tcube[0][0][1] = tcube[0][1][0];
		tcube[0][1][0] = tcube[0][2][1];
		tcube[0][2][1] = tcube[0][1][2];
		tcube[0][1][2] = tmp;
		break;
	    case 3:    /* B */
		tmp = tcube[0][0][2];
		tcube[0][0][2] = tcube[2][0][2];
		tcube[2][0][2] = tcube[2][0][0];
		tcube[2][0][0] = tcube[0][0][0];
		tcube[0][0][0] = tmp;
		tmp = tcube[0][0][1];
		tcube[0][0][1] = tcube[1][0][2];
		tcube[1][0][2] = tcube[2][0][1];
		tcube[2][0][1] = tcube[1][0][0];
		tcube[1][0][0] = tmp;
		break;
	    case 4:    /* L */
		tmp = tcube[0][0][0];
		tcube[0][0][0] = tcube[2][0][0];
		tcube[2][0][0] = tcube[2][2][0];
		tcube[2][2][0] = tcube[0][2][0];
		tcube[0][2][0] = tmp;
		tmp = tcube[0][1][0];
		tcube[0][1][0] = tcube[1][0][0];
		tcube[1][0][0] = tcube[2][1][0];
		tcube[2][1][0] = tcube[1][2][0];
		tcube[1][2][0] = tmp;
		break;
	    case 5:    /* D */
		tmp = tcube[2][0][0];
		tcube[2][0][0] = tcube[2][0][2];
		tcube[2][0][2] = tcube[2][2][2];
		tcube[2][2][2] = tcube[2][2][0];
		tcube[2][2][0] = tmp;
		tmp = tcube[2][0][1];
		tcube[2][0][1] = tcube[2][1][2];
		tcube[2][1][2] = tcube[2][2][1];
		tcube[2][2][1] = tcube[2][1][0];
		tcube[2][1][0] = tmp;
		break;
	    }
	}
    }
}

