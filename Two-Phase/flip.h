/* Flippancy */
/* Numbering of edge cubelets top layer to bottom:
     .  0  .
     3  .  1
     .  2  .

     8  .  9
     .  .  .
    11  . 10

     .  4  .
     7  .  5
     .  6  .
*/

#define MAX_FLIPS	2048

static unsigned short flips[MAX_FLIPS][6];
#ifndef NOMAX
static char mm_flips[MAX_FLIPS];
#endif /* NOMAX */

static int flip_val(int f0,int f1,int f2,int f3,int f4,int f5,int f6,int f7,int f8,int f9,int fa,int fb)
{
   return (((((((((fa*2+
		   f9)*2+
		   f8)*2+
		   f7)*2+
		   f6)*2+
		   f5)*2+
		   f4)*2+
		   f3)*2+
		   f2)*2+
		   f1)*2+
		   f0;
}

static void init_flips()
{
int i, j, k, l, m;
int f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, fa, fb;
int nf0, nf1, nf2, nf3, nf4, nf5, nf6, nf7, nf8, nf9, nfa, nfb;
#define inv(i)	((i)^1)
#define params	nf0,nf1,nf2,nf3,nf4,nf5,nf6,nf7,nf8,nf9,nfa,nfb

    f0 = f1 = f2 = f3 = f4 = f5 = f6 = f7 = f8 = f9 = fa = fb = 0;
    for(i = 0; i < MAX_FLIPS; i++) {
	/* F */
	nf0 = f0;
	nf1 = f1;
	nf2 = inv(fb);
	nf3 = f3;
	nf4 = f4;
	nf5 = f5;
	nf6 = inv(fa);
	nf7 = f7;
	nf8 = f8;
	nf9 = f9;
	nfa = inv(f2);
	nfb = inv(f6);
	flips[i][0] = flip_val(params);
	/* R */
	nf0 = f0;
	nf1 = fa;
	nf2 = f2;
	nf3 = f3;
	nf4 = f4;
	nf5 = f9;
	nf6 = f6;
	nf7 = f7;
	nf8 = f8;
	nf9 = f1;
	nfa = f5;
	nfb = fb;
	flips[i][1] = flip_val(params);
	/* U */
	nf0 = f3;
	nf1 = f0;
	nf2 = f1;
	nf3 = f2;
	nf4 = f4;
	nf5 = f5;
	nf6 = f6;
	nf7 = f7;
	nf8 = f8;
	nf9 = f9;
	nfa = fa;
	nfb = fb;
	flips[i][2] = flip_val(params);
	/* B */
	nf0 = inv(f9);
	nf1 = f1;
	nf2 = f2;
	nf3 = f3;
	nf4 = inv(f8);
	nf5 = f5;
	nf6 = f6;
	nf7 = f7;
	nf8 = inv(f0);
	nf9 = inv(f4);
	nfa = fa;
	nfb = fb;
	flips[i][3] = flip_val(params);
	/* L */
	nf0 = f0;
	nf1 = f1;
	nf2 = f2;
	nf3 = f8;
	nf4 = f4;
	nf5 = f5;
	nf6 = f6;
	nf7 = fb;
	nf8 = f7;
	nf9 = f9;
	nfa = fa;
	nfb = f3;
	flips[i][4] = flip_val(params);
	/* D */
	nf0 = f0;
	nf1 = f1;
	nf2 = f2;
	nf3 = f3;
	nf4 = f5;
	nf5 = f6;
	nf6 = f7;
	nf7 = f4;
	nf8 = f8;
	nf9 = f9;
	nfa = fa;
	nfb = fb;
	flips[i][5] = flip_val(params);
	f0 = inv(f0);
	if(f0 == 0) {
	    f1 = inv(f1);
	    if(f1 == 0) {
		f2 = inv(f2);
		if(f2 == 0) {
		    f3 = inv(f3);
		    if(f3 == 0) {
			f4 = inv(f4);
			if(f4 == 0) {
			    f5 = inv(f5);
			    if(f5 == 0) {
				f6 = inv(f6);
				if(f6 == 0) {
				    f7 = inv(f7);
				    if(f7 == 0) {
					f8 = inv(f8);
					if(f8 == 0) {
					    f9 = inv(f9);
					    if(f9 == 0) {
						fa = inv(fa);
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
	j = (f0 + f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8 + f9 + fa) & 1;
	fb = j;
    }
#ifdef VERBOSE
    fprintf(stderr, "\tInitialized = %d\n", MAX_FLIPS);
#endif /* VERBOSE */
#ifndef NOMAX
    for(i = 0; i < MAX_FLIPS; i++) {
	mm_flips[i] = 127;
    }
    i = MAX_FLIPS - 1;
    j = 0;
    mm_flips[0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_FLIPS; k++) {
	    if(mm_flips[k] == j) {
		f0 = k;
		for(l = 0; l < 6; l++) {
		    nf0 = f0;
		    for(m = 0; m < 3; m++) {
			nf0 = flips[nf0][l];
			if(mm_flips[nf0] == 127) {
			    mm_flips[nf0] = j + 1;
			    i--;
			}
		    }
		}
	    }
	}
	j++;
    }
#ifdef VERBOSE
    fprintf(stderr, "\tMaxpath = %d\n", j);
#endif /* VERBOSE */
#endif /* NOMAX */
}
#undef inv
#undef params

