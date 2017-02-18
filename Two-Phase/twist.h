/* Twistiness */
/* Numbering of corner cubelets top layer to bottom:
     0  .  1
     .  .  .
     3  .  2

     .  .  .
     .  .  .
     .  .  .

     4  .  5
     .  .  .
     7  .  6
*/

#define MAX_TWISTS	2187

static unsigned short twists[MAX_TWISTS][6];
#ifndef NOMAX
static char mm_twists[MAX_TWISTS];
#endif /* NOMAX */

static int twist_val(int t0,int t1,int t2,int t3,int t4,int t5,int t6,int t7)
{
    return (((((t6*3+
		t5)*3+
		t4)*3+
		t3)*3+
		t2)*3+
		t1)*3+
		t0;
}

static void init_twists()
{
int i, j, k, l, m;
int t0, t1, t2, t3, t4, t5, t6, t7;
int nt0, nt1, nt2, nt3, nt4, nt5, nt6, nt7;
#define inc(i, j) ((i+j) % 3)
#define params	nt0,nt1,nt2,nt3,nt4,nt5,nt6,nt7

    t0 = t1 = t2 = t3 = t4 = t5 = t6 = t7 = 0;
    for(i = 0; i < MAX_TWISTS; i++) {
	/* F */
	nt0 = t0;
	nt1 = t1;
	nt2 = inc(t3,1);
	nt3 = inc(t7,2);
	nt4 = t4;
	nt5 = t5;
	nt6 = inc(t2,2);
	nt7 = inc(t6,1);
	twists[i][0] = twist_val(params);
	/* R */
	nt0 = t0;
	nt1 = inc(t2,1);
	nt2 = inc(t6,2);
	nt3 = t3;
	nt4 = t4;
	nt5 = inc(t1,2);
	nt6 = inc(t5,1);
	nt7 = t7;
	twists[i][1] = twist_val(params);
	/* U */
	nt0 = t3;
	nt1 = t0;
	nt2 = t1;
	nt3 = t2;
	nt4 = t4;
	nt5 = t5;
	nt6 = t6;
	nt7 = t7;
	twists[i][2] = twist_val(params);
	/* B */
	nt0 = inc(t1,1);
	nt1 = inc(t5,2);
	nt2 = t2;
	nt3 = t3;
	nt4 = inc(t0,2);
	nt5 = inc(t4,1);
	nt6 = t6;
	nt7 = t7;
	twists[i][3] = twist_val(params);
	/* L */
	nt0 = inc(t4,2);
	nt1 = t1;
	nt2 = t2;
	nt3 = inc(t0,1);
	nt4 = inc(t7,1);
	nt5 = t5;
	nt6 = t6;
	nt7 = inc(t3,2);
	twists[i][4] = twist_val(params);
	/* D */
	nt0 = t0;
	nt1 = t1;
	nt2 = t2;
	nt3 = t3;
	nt4 = t5;
	nt5 = t6;
	nt6 = t7;
	nt7 = t4;
	twists[i][5] = twist_val(params);
	t0 = inc(t0,1);
	if(t0 == 0) {
	    t1 = inc(t1,1);
	    if(t1 == 0) {
		t2 = inc(t2,1);
		if(t2 == 0) {
		    t3 = inc(t3,1);
		    if(t3 == 0) {
			t4 = inc(t4,1);
			if(t4 == 0) {
			    t5 = inc(t5,1);
			    if(t5 == 0) {
				t6 = inc(t6,1);
			    }
			}
		    }
		}
	    }
	}
	j = (t0 + t1 + t2 + t3 + t4 + t5 + t6) % 3;
	t7 = 3 - j;
	if(t7 == 3) {
	    t7 = 0;
	}
    }
#ifdef VERBOSE
    fprintf(stderr, "\tInitialized = %d\n", MAX_TWISTS);
#endif /* VERBOSE */
#ifndef NOMAX
    for(i = 0; i < MAX_TWISTS; i++) {
	mm_twists[i] = 127;
    }
    i = MAX_TWISTS - 1;
    j = 0;
    mm_twists[0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_TWISTS; k++) {
	    if(mm_twists[k] == j) {
		t0 = k;
		for(l = 0; l < 6; l++) {
		    nt0 = t0;
		    for(m = 0; m < 3; m++) {
			nt0 = twists[nt0][l];
			if(mm_twists[nt0] == 127) {
			    mm_twists[nt0] = j + 1;
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
#undef inc
#undef params

