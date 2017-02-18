#include "phase1.h"

/* State variables */
int cube_twist, cube_flip, cube_choice;
int sol_found;
int phase1_todo;
unsigned long attempted;

void init_phase1()
{
//    fprintf(stderr, "    Initializing twists...\n");
    init_twists();
//    fprintf(stderr, "    Done!\n");
//    fprintf(stderr, "    Initializing flips...\n");
    init_flips();
//    fprintf(stderr, "    Done!\n");
//    fprintf(stderr, "    Initializing choices...\n");
    init_choices();
//    fprintf(stderr, "    Done!\n");
#ifdef LARGE_MEM
//    fprintf(stderr, "    Initializing mixed...\n");
    init_mixed1();
//    fprintf(stderr, "    Done!\n");
#endif /* LARGE_MEM */
}

int init_phase1_cube()
{
    int i, j, k;
    int t0, t1, t2, t3, t4, t5, t6, t7;
    int f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, fa, fb;
    int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, pa, pb;
    int e[12], c[8];
    
    /* First check twists */
    t0 = cube[0][0][0][1];
    t1 = cube[0][0][2][1];
    t2 = cube[0][2][2][1];
    t3 = cube[0][2][0][1];
    t4 = cube[2][0][0][1];
    t5 = cube[2][0][2][1];
    t6 = cube[2][2][2][1];
    t7 = cube[2][2][0][1];
    i = (t0+t1+t2+t3+t4+t5+t6+t7) % 3;
    if(i != 0) {
        fprintf(stderr, "The cube is too twisty.\n");
        return -1;
    }
    cube_twist = twist_val(t0,t1,t2,t3,t4,t5,t6,t7);
    /* Next check flips */
    f0 = cube[0][0][1][1];
    f1 = cube[0][1][2][1];
    f2 = cube[0][2][1][1];
    f3 = cube[0][1][0][1];
    f4 = cube[2][0][1][1];
    f5 = cube[2][1][2][1];
    f6 = cube[2][2][1][1];
    f7 = cube[2][1][0][1];
    f8 = cube[1][0][0][1];
    f9 = cube[1][0][2][1];
    fa = cube[1][2][2][1];
    fb = cube[1][2][0][1];
    i = (f0+f1+f2+f3+f4+f5+f6+f7+f8+f9+fa+fb) & 1;
    if(i != 0) {
        fprintf(stderr, "The cube is too flippant.\n");
        return -1;
    }
    cube_flip = flip_val(f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,fa,fb);
    /* Check permutation */
    e [0] = cube[0][0][1][0];
    e [1] = cube[0][1][2][0];
    e [2] = cube[0][2][1][0];
    e [3] = cube[0][1][0][0];
    e [4] = cube[2][0][1][0];
    e [5] = cube[2][1][2][0];
    e [6] = cube[2][2][1][0];
    e [7] = cube[2][1][0][0];
    e [8] = cube[1][0][0][0];
    e [9] = cube[1][0][2][0];
    e[10] = cube[1][2][2][0];
    e[11] = cube[1][2][0][0];
    c [0] = cube[0][0][0][0];
    c [1] = cube[0][0][2][0];
    c [2] = cube[0][2][2][0];
    c [3] = cube[0][2][0][0];
    c [4] = cube[2][0][0][0];
    c [5] = cube[2][0][2][0];
    c [6] = cube[2][2][2][0];
    c [7] = cube[2][2][0][0];
    i = 0;
    for(j = 0; j < 12; j++) {
        while((k = e[j]) != j) {
            if(k < j) {
                fprintf(stderr, "Cube contains identical edges.\n");
                exit(1);
            }
            e[j] = e[k];
            e[k] = k;
            i++;
        }
    }
    for(j = 0; j < 8; j++) {
        while((k = c[j]) != j) {
            if(k < j) {
                fprintf(stderr, "Cube contains identical corners.\n");
                exit(1);
            }
            c[j] = c[k];
            c[k] = k;
            i++;
        }
    }
    if((i & 1) != 0) {
        fprintf(stderr, "The cube is too permuted.\n");
        exit(1);
    }
    /* Finally check choice */
    p0 = cube[0][0][1][0] >= 8;
    p1 = cube[0][1][2][0] >= 8;
    p2 = cube[0][2][1][0] >= 8;
    p3 = cube[0][1][0][0] >= 8;
    p4 = cube[2][0][1][0] >= 8;
    p5 = cube[2][1][2][0] >= 8;
    p6 = cube[2][2][1][0] >= 8;
    p7 = cube[2][1][0][0] >= 8;
    p8 = cube[1][0][0][0] >= 8;
    p9 = cube[1][0][2][0] >= 8;
    pa = cube[1][2][2][0] >= 8;
    pb = cube[1][2][0][0] >= 8;
    cube_choice = choice_val(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,pa,pb);
    /* Finally check whether phase 1 has something to do */
    if(cube_twist + cube_flip + cube_choice != 0) {
        i = mm_twists[cube_twist];
        j = mm_flips[cube_flip];
        if(j > i) {
            i = j;
        }
        j = mm_choices[cube_choice];
        if(j > i) {
            i = j;
        }
#ifdef LARGE_MEM
        j = mm_tf[cube_twist][cube_flip];
        if(j > i) {
            i = j;
        }
        j = mm_tc[cube_twist][cube_choice];
        if(j > i) {
            i = j;
        }
        j = mm_fc[cube_flip][cube_choice];
        if(j > i) {
            i = j;
        }
#endif /* LARGE_MEM */
//        fprintf(stderr, "The cube is twisty, flippant and/or choosy; ");
//        fprintf(stderr, "Phase 1 needs at least %d moves\n", i);
#ifdef VERBOSE
        fprintf(stderr, "Twistiness = %d\n", cube_twist);
        fprintf(stderr, "Flippancy  = %d\n", cube_flip);
        fprintf(stderr, "Choosiness = %d\n", cube_choice);
#endif /* VERBOSE */
        return i;
    } else {
//        fprintf(stderr, "The cube is not twisty, flippant or choosy; ");
//        fprintf(stderr, "Phase 1 is not needed\n");
        return 0;
    }
}

void do_phase1(twist, flip, choice, dont1, dont2)
int twist, flip, choice, dont1, dont2;
{
    int i, j, tw, fl, ch, move, do_phase2;
    
    if(twist == 0 && flip == 0 && choice == 0) {
        if(phase1_todo != cur_move) {
            return; /* Was too short */
        }
        attempted++;
        phase1_cur = cur_move;
        perm_cube();
        do_phase2 = init_phase2_cube();
        if(do_phase2) {
            i = cur_move + 1;
            if(i < do_phase2) {
                i = do_phase2;
            }
            while(i < max_sol) {
                phase2(i++ - cur_move, dont1, dont2);
                if(do_max20 && max_sol <= 20) {
                    break;
                }
            }
        } else {
            prnt_sol();
            sol_found = -1;
        }
        return;
    }
    if(mm_twists[twist] > sol_found) {
        return;
    }
    if(mm_flips[flip] > sol_found) {
        return;
    }
    if(mm_choices[choice] > sol_found) {
        return;
    }
#ifdef LARGE_MEM
    if(mm_tf[twist][flip] > sol_found) {
        return;
    }
    if(mm_tc[twist][choice] > sol_found) {
        return;
    }
    if(mm_fc[flip][choice] > sol_found) {
        return;
    }
#endif /* LARGE_MEM */
    for(i = 0; i < 6; i++) if(i != dont1 && i != dont2) {
        tw = twist;
        fl = flip;
        ch = choice;
        move = i << 2;
        for(j = 0; j < 3; j++) {
            tw = twists[tw][i];
            fl = flips[fl][i];
            ch = choices[ch][i];
            sol_found--;
            moves[cur_move++] = move;
            if(abs(dont1 - i) == 3) {
                do_phase1(tw, fl, ch, i, dont1);
                // add
                if(do_max20 && max_sol <= 20) {
                    return;
                }
                // add
            } else if(i >= 3) {
                do_phase1(tw, fl, ch, i, i - 3);
                // add
                if(do_max20 && max_sol <= 20) {
                    return;
                }
                // add
            } else {
                do_phase1(tw, fl, ch, i, -1);
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

int phase1(max_todo)
int max_todo;
{
    sol_found = max_todo;
    phase1_todo = max_todo;
    attempted = 0;
    do_phase1(cube_twist, cube_flip, cube_choice, -1, -1);
    fprintf(stderr, "max = %d; attempted: %ld\n", max_todo, attempted);
    return sol_found;
}

