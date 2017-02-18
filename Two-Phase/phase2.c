#include "phase2.h"

/* State variables */
static int cube_cperm, cube_eperm, cube_sperm;
static int sol_found;

void init_phase2()
{
//    fprintf(stderr, "    Initializing corner orders...\n");
    init_cperms();
//    fprintf(stderr, "    Done!\n");
//    fprintf(stderr, "    Initializing edge orders...\n");
    init_eperms();
//    fprintf(stderr, "    Done!\n");
//    fprintf(stderr, "    Initializing slice orders...\n");
    init_sperms();
//    fprintf(stderr, "    Done!\n");
#ifdef LARGE_MEM
//    fprintf(stderr, "    Initializing mixed...\n");
    init_mixed2();
//    fprintf(stderr, "    Done!\n");
#endif /* LARGE_MEM */
}

int init_phase2_cube()
{
int i, j;
int c0, c1, c2, c3, c4, c5, c6, c7;
int e0, e1, e2, e3, e4, e5, e6, e7;
int s0, s1, s2, s3;

    /* First check corner orders */
    c0 = tcube[0][0][0];
    c1 = tcube[0][0][2];
    c2 = tcube[0][2][2];
    c3 = tcube[0][2][0];
    c4 = tcube[2][0][0];
    c5 = tcube[2][0][2];
    c6 = tcube[2][2][2];
    c7 = tcube[2][2][0];
    cube_cperm = perm8_val(c0,c1,c2,c3,c4,c5,c6,c7);
    /* Next check edge orders */
    e0 = tcube[0][0][1];
    e1 = tcube[0][1][2];
    e2 = tcube[0][2][1];
    e3 = tcube[0][1][0];
    e4 = tcube[2][0][1];
    e5 = tcube[2][1][2];
    e6 = tcube[2][2][1];
    e7 = tcube[2][1][0];
    cube_eperm = perm8_val(e0,e1,e2,e3,e4,e5,e6,e7);
    /* Finally check slice orders */
    s0 = tcube[1][0][0] - 8;
    s1 = tcube[1][0][2] - 8;
    s2 = tcube[1][2][2] - 8;
    s3 = tcube[1][2][0] - 8;
    cube_sperm = perm4_val(s0,s1,s2,s3);
    /* Finally check whether phase 2 has something to do */
    if(cube_cperm + cube_eperm + cube_sperm != 0) {
	i = mm_cperms[cube_cperm];
	j = mm_eperms[cube_eperm];
	if(j > i) {
	    i = j;
	}
	j = mm_sperms[cube_sperm];
	if(j > i) {
	    i = j;
	}
#ifdef LARGE_MEM
	j = mm_cs[cube_cperm][cube_sperm];
	if(j > i) {
	    i = j;
	}
	j = mm_es[cube_eperm][cube_sperm];
	if(j > i) {
	    i = j;
	}
#endif /* LARGE_MEM */
/*
	fprintf(stderr, "The cube is not orderly; ");
	fprintf(stderr, "Phase 2 needs at least %d moves\n", i);
*/
	return i;
    } else {
	fprintf(stderr, "The cube is orderly; ");
	fprintf(stderr, "Phase 2 is not needed\n");
	return 0;
    }
}

void do_phase2(cperm, eperm, sperm, dont1, dont2)
int cperm, eperm, sperm, dont1, dont2;
{
int i, j, cp, ep, sp, move;

    if(cperm == 0 && eperm == 0 && sperm == 0) {
	prnt_sol();
	sol_found = -1;
	return;
    }
    if(mm_cperms[cperm] > sol_found) {
	return;
    }
    if(mm_eperms[eperm] > sol_found) {
	return;
    }
    if(mm_sperms[sperm] > sol_found) {
	return;
    }
#ifdef LARGE_MEM
    if(mm_cs[cperm][sperm] > sol_found) {
	return;
    }
    if(mm_es[eperm][sperm] > sol_found) {
	return;
    }
#endif /* LARGE_MEM */
    for(i = 0; i < 6; i++) if(i != dont1 && i != dont2) {
	cp = cperm;
	ep = eperm;
	sp = sperm;
	move = i << 2;
	if((i % 3) != 2) {
	    cp = cperms[cp][i];
	    ep = eperms[ep][i];
	    sp = sperms[sp][i];
	    move++;
	    sol_found--;
	    moves[cur_move++] = move;
	    if(abs(i - dont1) == 3) {
            do_phase2(cp, ep, sp, i, dont1);
            // add
            if(do_max20 && max_sol <= 20) {
                return;
            }
            // add
	    } else if(i >= 3) {
            do_phase2(cp, ep, sp, i, i - 3);
            // add
            if(do_max20 && max_sol <= 20) {
                return;
            }
            // add
	    } else {
            do_phase2(cp, ep, sp, i, -1);
            // add
            if(do_max20 && max_sol <= 20) {
                return;
            }
            // add
	    }
	    sol_found++;
	    cur_move--;
	    if(sol_found == 0) {
		return;
	    }
	} else for(j = 0; j < 3; j++) {
#ifdef SQUARESONLY
	    if(j != 1) {
		continue;
	    }
#endif
	    cp = cperms[cp][i];
	    ep = eperms[ep][i];
	    sp = sperms[sp][i];
	    sol_found--;
	    moves[cur_move++] = move;
	    if(abs(i - dont1) == 3) {
            do_phase2(cp, ep, sp, i, dont1);
            // add
            if(do_max20 && max_sol <= 20) {
                return;
            }
            // add
	    } else if(i >= 3) {
            do_phase2(cp, ep, sp, i, i - 3);
            // add
            if(do_max20 && max_sol <= 20) {
                return;
            }
            // add
	    } else {
            do_phase2(cp, ep, sp, i, -1);
            // add
            if(do_max20 && max_sol <= 20) {
                return;
            }
            // add
	    }
	    sol_found++;
	    cur_move--;
	    move++;
	    if(sol_found == 0) {
		return;
	    }
	}
    }
}

int phase2(max_todo, dont1, dont2)
int max_todo, dont1, dont2;
{
    sol_found = max_todo;
    do_phase2(cube_cperm, cube_eperm, cube_sperm, dont1, dont2);
    return sol_found;
}

