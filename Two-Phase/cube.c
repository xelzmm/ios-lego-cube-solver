#include "cube.h"

//static void def_cube();
//static void read_cube();
//static void read_position();

//static int do_repeat = 0;

char* solvecube(char const* state) {
    
    static char m[] = "FRUBLD";
    
#define t(i) state[i]

    /*
        U
      L F R B
        D
     */
    
   /*
	                   D 22  21  20

	                     00  01  02
	                   B 10  11  12
	                     20  21  22

	 22    00  01  02    00  01  02    00  01  02    20
   D 12  L 10  11  12  U 10  11  12  R 10  11  12  D 10
	 02    20  21  22    20  21  22    20  21  22    00

	                     00  01  02
	                   F 10  11  12
	                     20  21  22

	                   D 02  01  00
    */
    
    U[0][0] = t( 0); U[0][1] = t( 1); U[0][2] = t( 2);
    U[1][0] = t( 3); U[1][1] = t( 4); U[1][2] = t( 5);
    U[2][0] = t( 6); U[2][1] = t( 7); U[2][2] = t( 8);
    
    R[0][0] = t(9 + 2); R[0][1] = t(9 + 5); R[0][2] = t(9 + 8);
    R[1][0] = t(9 + 1); R[1][1] = t(9 + 4); R[1][2] = t(9 + 7);
    R[2][0] = t(9 + 0); R[2][1] = t(9 + 3); R[2][2] = t(9 + 6);
    
    F[0][0] = t(18 + 0); F[0][1] = t(18 + 1); F[0][2] = t(18 + 2);
    F[1][0] = t(18 + 3); F[1][1] = t(18 + 4); F[1][2] = t(18 + 5);
    F[2][0] = t(18 + 6); F[2][1] = t(18 + 7); F[2][2] = t(18 + 8);
    
    D[0][0] = t(27 + 2); D[0][1] = t(27 + 1); D[0][2] = t(27 + 0);
    D[1][0] = t(27 + 5); D[1][1] = t(27 + 4); D[1][2] = t(27 + 3);
    D[2][0] = t(27 + 8); D[2][1] = t(27 + 7); D[2][2] = t(27 + 6);
    
    L[0][0] = t(36 + 6); L[0][1] = t(36 + 3); L[0][2] = t(36 + 0);
    L[1][0] = t(36 + 7); L[1][1] = t(36 + 4); L[1][2] = t(36 + 1);
    L[2][0] = t(36 + 8); L[2][1] = t(36 + 5); L[2][2] = t(36 + 2);
    
    B[0][0] = t(45 + 8); B[0][1] = t(45 + 7); B[0][2] = t(45 + 6);
    B[1][0] = t(45 + 5); B[1][1] = t(45 + 4); B[1][2] = t(45 + 3);
    B[2][0] = t(45 + 2); B[2][1] = t(45 + 1); B[2][2] = t(45 + 0);
    
#undef t
    
    set_cube();
    final_moves[0] = -1;
    int do_phase1, do_phase2, i, j, k;
    do_phase1 = init_phase1_cube();
    if(do_phase1) {
        i = 1;
        if(i < do_phase1) {
            i = do_phase1;
        }
        while(i < max_sol) {
            phase1(i++);
            if(do_max20 && max_sol <= 20) {
                break;
            }
        }
    } else {
        perm_cube();
        do_phase2 = init_phase2_cube();
        i = 1;
        if(i < do_phase2) {
            i = do_phase2;
        }
        if(do_phase2) {
            phase1_cur = 0;
            while(i < max_sol) {
                phase2(i++, -1, -1);
                if(do_max20 && max_sol <= 20) {
                    break;
                }
            }
        }
    }
    fflush(stdout);
    
    char* result = (char *) malloc(sizeof(char) * MAX_MOVES * 3);
    
    for(i = 0; (j = final_moves[i]) != -1; i++) {
        k = j & 3;
        j = j >> 2;
//        printf("%c%d ", m[j], k + 1);
        result[i * 3] = m[j];
        result[i * 3 + 1] = '1' + k;
        result[i * 3 + 2] = ' ';
    }
    result[i * 3 - 1] = 0;
    printf("Final Solution: %s\n", result);
    return result;
}
void init() {
    
    cur_move = 0;
    max_sol = MAX_MOVES + 1;
    do_max20 = 1;
    //    fprintf(stderr, "Initializing for phase 1...\n");
    init_phase1();
    //    fprintf(stderr, "Initializing for phase 2...\n");
    init_phase2();
    //    fprintf(stderr, "Initialization done!\n");
}

int main2(int argc, char *argv[])
{
    init();
    printf("%s\n", solvecube("FUUUUDRBULBLLRDURBBRBLFFUFFBRRLDUFBDDLDDLBDDRFFLFBRLUR"));
    return 0;
}

//int main1(int argc, char *argv[])
//{
//    int do_phase1, do_phase2, i, error = 0, readturns, readpos;
//    
//    readturns = -1;
//    readpos = -1;
//    do_max20 = 0;
//    if(argc > 3) {
//        fprintf(stderr, "Too many parameters\n");
//        return -1;//exit(1);
//    }
//    while(argc > 1) {
//        if(!strcmp(argv[1], "-t")) {
//            if(readpos >= 0 || readturns >= 0) {
//                error = 1;
//            }
//            readturns = 1;
//        } else if(!strcmp(argv[1], "-p")) {
//            if(readpos >= 0 || readturns >= 0) {
//                error = 1;
//            }
//            readpos = 1;
//        }
//        if(!strcmp(argv[1], "-m")) {
//            do_max20 = 1;
//        }
//        argc--;
//        argv++;
//    }
//    readpos = 1;
//    do_max20 = 1;
//    if(error) {
//        fprintf(stderr, "usage: cube [-t | -p]\n");
//        return -1;//exit(1);
//    }
//    if(readturns < 0) {
//        readturns = 0;
//    }
//    if(readpos < 0) {
//        readpos = 0;
//    }
//    fprintf(stderr, "Initializing for phase 1...\n");
//    init_phase1();
//    fprintf(stderr, "Initializing for phase 2...\n");
//    init_phase2();
//    fprintf(stderr, "Initialization done!\n");
//again:
//    cur_move = 0;
//    max_sol = MAX_MOVES + 1;
//    if(!readturns) {
//        if(!readpos) {
//            def_cube();
//        } else {
//            read_position();
//        }
//        set_cube();
//    } else {
//        read_cube();
//    }
//    do_phase1 = init_phase1_cube();
//    if(do_phase1) {
//        i = 1;
//        if(i < do_phase1) {
//            i = do_phase1;
//        }
//        while(i < max_sol) {
//            phase1(i++);
//            if(do_max20 && max_sol <= 20) {
//                break;
//            }
//        }
//    } else {
//        perm_cube();
//        do_phase2 = init_phase2_cube();
//        i = 1;
//        if(i < do_phase2) {
//            i = do_phase2;
//        }
//        if(do_phase2) {
//            phase1_cur = 0;
//            while(i < max_sol) {
//                phase2(i++, -1, -1);
//                if(do_max20 && max_sol <= 20) {
//                    break;
//                }
//            }
//        }
//    }
//    fflush(stdout);
//    if(do_repeat) goto again;
//    return 0;
//}

//static void def_cube()
//{
//    /* Row 0 of U connected with row 2 of B */
//    /* Column 2 of U connected with column 0 of R */
//    /* Row 2 of U connected with row 0 of F */
//    /* Column 0 of U connected with column 2 of L */
//    /* Row 2 of D connected with row 0 of B */
//    /* Column 0 of D connected with column 2 of R */
//    /* Row 0 of D connected with row 2 of F */
//    /* Column 2 of D connected with column 0 of L */
//    /*
//                       D 22  21  20
//     
//                         00  01  02
//                       B 10  11  12
//                         20  21  22
//     
//     22    00  01  02    00  01  02    00  01  02    20
//   D 12  L 10  11  12  U 10  11  12  R 10  11  12  D 10
//     02    20  21  22    20  21  22    20  21  22    00
//     
//                         00  01  02
//                       F 10  11  12
//                         20  21  22
//     
//                       D 02  01  00
//     */
//    U[0][0] = 'U'; U[0][1] = 'B'; U[0][2] = 'U';
//    U[1][0] = 'B'; U[1][1] = 'U'; U[1][2] = 'B';
//    U[2][0] = 'U'; U[2][1] = 'B'; U[2][2] = 'U';
//    
//    D[0][0] = 'D'; D[0][1] = 'F'; D[0][2] = 'D';
//    D[1][0] = 'F'; D[1][1] = 'D'; D[1][2] = 'F';
//    D[2][0] = 'D'; D[2][1] = 'F'; D[2][2] = 'D';
//    
//    R[0][0] = 'R'; R[0][1] = 'D'; R[0][2] = 'R';
//    R[1][0] = 'D'; R[1][1] = 'R'; R[1][2] = 'D';
//    R[2][0] = 'R'; R[2][1] = 'D'; R[2][2] = 'R';
//    
//    L[0][0] = 'L'; L[0][1] = 'U'; L[0][2] = 'L';
//    L[1][0] = 'U'; L[1][1] = 'L'; L[1][2] = 'U';
//    L[2][0] = 'L'; L[2][1] = 'U'; L[2][2] = 'L';
//    
//    F[0][0] = 'F'; F[0][1] = 'L'; F[0][2] = 'F';
//    F[1][0] = 'L'; F[1][1] = 'F'; F[1][2] = 'L';
//    F[2][0] = 'F'; F[2][1] = 'L'; F[2][2] = 'F';
//    
//    B[0][0] = 'B'; B[0][1] = 'R'; B[0][2] = 'B';
//    B[1][0] = 'R'; B[1][1] = 'B'; B[1][2] = 'R';
//    B[2][0] = 'B'; B[2][1] = 'R'; B[2][2] = 'B';
//}

//static void read_position()
//{
//    int c, i, input[54], used[256];
//    /* Reads the current position from standard input.  The input should
//     give the successive faces as follows:
//	    B
//     L U R D
//	    F
//     although different letters can be used.  So first the first 9 faces
//     of B, followed by 3 faces of L, U, R and D all three times, followed
//     by the faces of F.  The program will give the translation between
//     the symbols actually used and the symbols used in the solution.
//     So you might give the faces in the order
//	    T
//     L F R B
//	    D
//     but the program will use the translation T -> B -> D -> F -> U!
//     Error messages about wrong position are *after* translation!
//     */
//    do_repeat = 0;
//    for(i = 0; i < 256; i++) {
//        used[i] = 0;
//    }
//    i = 0;
//    while((c = getchar()) != EOF) {
//        if(c == ' ' || c == '\n' || c == '\t') {
//            continue;
//        }
//        if(c == '*') {
//            do_repeat = 1;
//            break;
//        }
//        if(i == 54) {
//            fprintf(stderr, "Too much input\n");
//            exit(1);
//        }
//        input[i++] = c;
//        used[c]++;
//    }
//    if(i != 54) {
//        fprintf(stderr, "Not enough input\n");
//        exit(1);
//    }
//    for(i = 0; i < 256; i++) {
//        if(used[i] != 0 && used[i] != 9) {
//            fprintf(stderr, "Input inbalance\n");
//            exit(1);
//        }
//    }
//    printf("Translations:\n");
//    c = input[ 4];
//    used[c] = 'B';
//    printf("    %c -> B\n", c);
//    c = input[22];
//    used[c] = 'L';
//    printf("    %c -> L\n", c);
//    c = input[25];
//    used[c] = 'U';
//    printf("    %c -> U\n", c);
//    c = input[28];
//    used[c] = 'R';
//    printf("    %c -> R\n", c);
//    c = input[31];
//    used[c] = 'D';
//    printf("    %c -> D\n", c);
//    c = input[49];
//    used[c] = 'F';
//    printf("    %c -> F\n", c);
//    printf("-----------\n");
//    
//#define t(i)	used[input[i]]
//    
//    B[0][0] = t( 0); B[0][1] = t( 1); B[0][2] = t( 2);
//    B[1][0] = t( 3); B[1][1] = t( 4); B[1][2] = t( 5);
//    B[2][0] = t( 6); B[2][1] = t( 7); B[2][2] = t( 8);
//    L[0][0] = t( 9); L[0][1] = t(10); L[0][2] = t(11);
//    U[0][0] = t(12); U[0][1] = t(13); U[0][2] = t(14);
//    R[0][0] = t(15); R[0][1] = t(16); R[0][2] = t(17);
//    D[2][0] = t(18); D[2][1] = t(19); D[2][2] = t(20);
//    L[1][0] = t(21); L[1][1] = t(22); L[1][2] = t(23);
//    U[1][0] = t(24); U[1][1] = t(25); U[1][2] = t(26);
//    R[1][0] = t(27); R[1][1] = t(28); R[1][2] = t(29);
//    D[1][0] = t(30); D[1][1] = t(31); D[1][2] = t(32);
//    L[2][0] = t(33); L[2][1] = t(34); L[2][2] = t(35);
//    U[2][0] = t(36); U[2][1] = t(37); U[2][2] = t(38);
//    R[2][0] = t(39); R[2][1] = t(40); R[2][2] = t(41);
//    D[0][0] = t(42); D[0][1] = t(43); D[0][2] = t(44);
//    F[0][0] = t(45); F[0][1] = t(46); F[0][2] = t(47);
//    F[1][0] = t(48); F[1][1] = t(49); F[1][2] = t(50);
//    F[2][0] = t(51); F[2][1] = t(52); F[2][2] = t(53);
//    
//#undef t
//}

//static void read_cube()
//{
//    int c, n, tmp;
//    
//    cube[0][0][0][0] =  0; cube[0][0][0][1] = 0;
//    cube[0][0][1][0] =  0; cube[0][0][1][1] = 0;
//    cube[0][0][2][0] =  1; cube[0][0][2][1] = 0;
//    cube[0][1][2][0] =  1; cube[0][1][2][1] = 0;
//    cube[0][2][2][0] =  2; cube[0][2][2][1] = 0;
//    cube[0][2][1][0] =  2; cube[0][2][1][1] = 0;
//    cube[0][2][0][0] =  3; cube[0][2][0][1] = 0;
//    cube[0][1][0][0] =  3; cube[0][1][0][1] = 0;
//    cube[2][0][0][0] =  4; cube[2][0][0][1] = 0;
//    cube[2][0][1][0] =  4; cube[2][0][1][1] = 0;
//    cube[2][0][2][0] =  5; cube[2][0][2][1] = 0;
//    cube[2][1][2][0] =  5; cube[2][1][2][1] = 0;
//    cube[2][2][2][0] =  6; cube[2][2][2][1] = 0;
//    cube[2][2][1][0] =  6; cube[2][2][1][1] = 0;
//    cube[2][2][0][0] =  7; cube[2][2][0][1] = 0;
//    cube[2][1][0][0] =  7; cube[2][1][0][1] = 0;
//    cube[1][0][0][0] =  8; cube[1][0][0][1] = 0;
//    cube[1][0][2][0] =  9; cube[1][0][2][1] = 0;
//    cube[1][2][2][0] = 10; cube[1][2][2][1] = 0;
//    cube[1][2][0][0] = 11; cube[1][2][0][1] = 0;
//    do_repeat = 1;
//    while((c = getchar()) != '\n') {
//        if(c == EOF) {
//            exit(0);
//        }
//        if(c == ' ') {
//            continue;
//        }
//        if(c >= 'a' && c <= 'z') {
//            c = c - 'a' + 'A';
//        }
//        if(c != 'F' && c != 'R' && c != 'U' && c != 'B' && c != 'L' &&
//           c != 'D') {
//            fprintf(stderr, "Illegal input character: %c\n", c);
//            exit(1);
//        }
//        n = getchar();
//        if(n != '1' && n != '2' && n != '3' && n != '\'') {
//            ungetc(n, stdin);
//            n = 1;
//        } else if(n == '\'') {
//            n = 3;
//        } else {
//            n = n - '0';
//        }
//        while(n-- > 0) {
//#define ic(i, n)	((i + n) % 3)
//#define ie(i)		((i + 1) & 1)
//            switch(c) {
//                case 'F':
//                    tmp = cube[0][2][0][0];
//                    cube[0][2][0][0] = cube[2][2][0][0];
//                    cube[2][2][0][0] = cube[2][2][2][0];
//                    cube[2][2][2][0] = cube[0][2][2][0];
//                    cube[0][2][2][0] = tmp;
//                    tmp = cube[0][2][1][0];
//                    cube[0][2][1][0] = cube[1][2][0][0];
//                    cube[1][2][0][0] = cube[2][2][1][0];
//                    cube[2][2][1][0] = cube[1][2][2][0];
//                    cube[1][2][2][0] = tmp;
//                    tmp = cube[0][2][0][1];
//                    cube[0][2][0][1] = ic(cube[2][2][0][1], 2);
//                    cube[2][2][0][1] = ic(cube[2][2][2][1], 1);
//                    cube[2][2][2][1] = ic(cube[0][2][2][1], 2);
//                    cube[0][2][2][1] = ic(tmp, 1);
//                    tmp = cube[0][2][1][1];
//                    cube[0][2][1][1] = ie(cube[1][2][0][1]);
//                    cube[1][2][0][1] = ie(cube[2][2][1][1]);
//                    cube[2][2][1][1] = ie(cube[1][2][2][1]);
//                    cube[1][2][2][1] = ie(tmp);
//                    break;
//                case 'R':
//                    tmp = cube[0][2][2][0];
//                    cube[0][2][2][0] = cube[2][2][2][0];
//                    cube[2][2][2][0] = cube[2][0][2][0];
//                    cube[2][0][2][0] = cube[0][0][2][0];
//                    cube[0][0][2][0] = tmp;
//                    tmp = cube[0][1][2][0];
//                    cube[0][1][2][0] = cube[1][2][2][0];
//                    cube[1][2][2][0] = cube[2][1][2][0];
//                    cube[2][1][2][0] = cube[1][0][2][0];
//                    cube[1][0][2][0] = tmp;
//                    tmp = cube[0][2][2][1];
//                    cube[0][2][2][1] = ic(cube[2][2][2][1], 2);
//                    cube[2][2][2][1] = ic(cube[2][0][2][1], 1);
//                    cube[2][0][2][1] = ic(cube[0][0][2][1], 2);
//                    cube[0][0][2][1] = ic(tmp, 1);
//                    tmp = cube[0][1][2][1];
//                    cube[0][1][2][1] = cube[1][2][2][1];
//                    cube[1][2][2][1] = cube[2][1][2][1];
//                    cube[2][1][2][1] = cube[1][0][2][1];
//                    cube[1][0][2][1] = tmp;
//                    break;
//                case 'U':
//                    tmp = cube[0][0][0][0];
//                    cube[0][0][0][0] = cube[0][2][0][0];
//                    cube[0][2][0][0] = cube[0][2][2][0];
//                    cube[0][2][2][0] = cube[0][0][2][0];
//                    cube[0][0][2][0] = tmp;
//                    tmp = cube[0][0][1][0];
//                    cube[0][0][1][0] = cube[0][1][0][0];
//                    cube[0][1][0][0] = cube[0][2][1][0];
//                    cube[0][2][1][0] = cube[0][1][2][0];
//                    cube[0][1][2][0] = tmp;
//                    tmp = cube[0][0][0][1];
//                    cube[0][0][0][1] = cube[0][2][0][1];
//                    cube[0][2][0][1] = cube[0][2][2][1];
//                    cube[0][2][2][1] = cube[0][0][2][1];
//                    cube[0][0][2][1] = tmp;
//                    tmp = cube[0][0][1][1];
//                    cube[0][0][1][1] = cube[0][1][0][1];
//                    cube[0][1][0][1] = cube[0][2][1][1];
//                    cube[0][2][1][1] = cube[0][1][2][1];
//                    cube[0][1][2][1] = tmp;
//                    break;
//                case 'B':
//                    tmp = cube[0][0][2][0];
//                    cube[0][0][2][0] = cube[2][0][2][0];
//                    cube[2][0][2][0] = cube[2][0][0][0];
//                    cube[2][0][0][0] = cube[0][0][0][0];
//                    cube[0][0][0][0] = tmp;
//                    tmp = cube[0][0][1][0];
//                    cube[0][0][1][0] = cube[1][0][2][0];
//                    cube[1][0][2][0] = cube[2][0][1][0];
//                    cube[2][0][1][0] = cube[1][0][0][0];
//                    cube[1][0][0][0] = tmp;
//                    tmp = cube[0][0][2][1];
//                    cube[0][0][2][1] = ic(cube[2][0][2][1], 2);
//                    cube[2][0][2][1] = ic(cube[2][0][0][1], 1);
//                    cube[2][0][0][1] = ic(cube[0][0][0][1], 2);
//                    cube[0][0][0][1] = ic(tmp, 1);
//                    tmp = cube[0][0][1][1];
//                    cube[0][0][1][1] = ie(cube[1][0][2][1]);
//                    cube[1][0][2][1] = ie(cube[2][0][1][1]);
//                    cube[2][0][1][1] = ie(cube[1][0][0][1]);
//                    cube[1][0][0][1] = ie(tmp);
//                    break;
//                case 'L':
//                    tmp = cube[0][0][0][0];
//                    cube[0][0][0][0] = cube[2][0][0][0];
//                    cube[2][0][0][0] = cube[2][2][0][0];
//                    cube[2][2][0][0] = cube[0][2][0][0];
//                    cube[0][2][0][0] = tmp;
//                    tmp = cube[0][1][0][0];
//                    cube[0][1][0][0] = cube[1][0][0][0];
//                    cube[1][0][0][0] = cube[2][1][0][0];
//                    cube[2][1][0][0] = cube[1][2][0][0];
//                    cube[1][2][0][0] = tmp;
//                    tmp = cube[0][0][0][1];
//                    cube[0][0][0][1] = ic(cube[2][0][0][1], 2);
//                    cube[2][0][0][1] = ic(cube[2][2][0][1], 1);
//                    cube[2][2][0][1] = ic(cube[0][2][0][1], 2);
//                    cube[0][2][0][1] = ic(tmp, 1);
//                    tmp = cube[0][1][0][1];
//                    cube[0][1][0][1] = cube[1][0][0][1];
//                    cube[1][0][0][1] = cube[2][1][0][1];
//                    cube[2][1][0][1] = cube[1][2][0][1];
//                    cube[1][2][0][1] = tmp;
//                    break;
//                case 'D':
//                    tmp = cube[2][0][0][0];
//                    cube[2][0][0][0] = cube[2][0][2][0];
//                    cube[2][0][2][0] = cube[2][2][2][0];
//                    cube[2][2][2][0] = cube[2][2][0][0];
//                    cube[2][2][0][0] = tmp;
//                    tmp = cube[2][0][1][0];
//                    cube[2][0][1][0] = cube[2][1][2][0];
//                    cube[2][1][2][0] = cube[2][2][1][0];
//                    cube[2][2][1][0] = cube[2][1][0][0];
//                    cube[2][1][0][0] = tmp;
//                    tmp = cube[2][0][0][1];
//                    cube[2][0][0][1] = cube[2][0][2][1];
//                    cube[2][0][2][1] = cube[2][2][2][1];
//                    cube[2][2][2][1] = cube[2][2][0][1];
//                    cube[2][2][0][1] = tmp;
//                    tmp = cube[2][0][1][1];
//                    cube[2][0][1][1] = cube[2][1][2][1];
//                    cube[2][1][2][1] = cube[2][2][1][1];
//                    cube[2][2][1][1] = cube[2][1][0][1];
//                    cube[2][1][0][1] = tmp;
//                    break;
//            }
//        }
//    }
//}

