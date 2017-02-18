/* Corner orderliness */
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

#define MAX_CPERMS	40320

static unsigned short cperms[MAX_CPERMS][6];
#ifndef NOMAX
static char mm_cperms[MAX_CPERMS];
#endif /* NOMAX */
#ifdef IPERM
static unsigned short cperms_inv[MAX_CPERMS];
#endif /* IPERM */

static void init_cperms()
{
int i, j, k, l, m;
int p0, p1, p2, p3, p4, p5, p6, p7;
int np0, np1, np2, np3, np4, np5, np6, np7;
#define params	np0,np1,np2,np3,np4,np5,np6,np7

    for(i = 0; i < MAX_CPERMS; i++) {
#ifdef IPERM
	cperms_inv[i] = inv_perm8_val(i);
#endif /* IPERM */
	val_perm8(i,&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7);
#ifdef SUBGROUP
	/* F^2 */
	np0 = p0;
	np1 = p1;
	np2 = p7;
	np3 = p6;
	np4 = p4;
	np5 = p5;
	np6 = p3;
	np7 = p2;
#else /* SUBGROUP */
	/* F */
	np0 = p0;
	np1 = p1;
	np2 = p3;
	np3 = p7;
	np4 = p4;
	np5 = p5;
	np6 = p2;
	np7 = p6;
#endif /* SUBGROUP */
	cperms[i][0] = perm8_val(params);
#ifdef SUBGROUP
	/* R^2 */
	np0 = p0;
	np1 = p6;
	np2 = p5;
	np3 = p3;
	np4 = p4;
	np5 = p2;
	np6 = p1;
	np7 = p7;
#else /* SUBGROUP */
	/* R */
	np0 = p0;
	np1 = p2;
	np2 = p6;
	np3 = p3;
	np4 = p4;
	np5 = p1;
	np6 = p5;
	np7 = p7;
#endif /* SUBGROUP */
	cperms[i][1] = perm8_val(params);
	/* U */
	np0 = p3;
	np1 = p0;
	np2 = p1;
	np3 = p2;
	np4 = p4;
	np5 = p5;
	np6 = p6;
	np7 = p7;
	cperms[i][2] = perm8_val(params);
#ifdef SUBGROUP
	/* B^2 */
	np0 = p5;
	np1 = p4;
	np2 = p2;
	np3 = p3;
	np4 = p1;
	np5 = p0;
	np6 = p6;
	np7 = p7;
#else /* SUBGROUP */
	/* B */
	np0 = p1;
	np1 = p5;
	np2 = p2;
	np3 = p3;
	np4 = p0;
	np5 = p4;
	np6 = p6;
	np7 = p7;
#endif /* SUBGROUP */
	cperms[i][3] = perm8_val(params);
#ifdef SUBGROUP
	/* L^2 */
	np0 = p7;
	np1 = p1;
	np2 = p2;
	np3 = p4;
	np4 = p3;
	np5 = p5;
	np6 = p6;
	np7 = p0;
#else /* SUBGROUP */
	/* L */
	np0 = p4;
	np1 = p1;
	np2 = p2;
	np3 = p0;
	np4 = p7;
	np5 = p5;
	np6 = p6;
	np7 = p3;
#endif /* SUBGROUP */
	cperms[i][4] = perm8_val(params);
	/* D */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	np4 = p5;
	np5 = p6;
	np6 = p7;
	np7 = p4;
	cperms[i][5] = perm8_val(params);
    }
#ifdef VERBOSE
    fprintf(stderr, "\tInitialized = %d\n", MAX_CPERMS);
#endif /* VERBOSE */
#ifndef NOMAX
    for(i = 0; i < MAX_CPERMS; i++) {
	mm_cperms[i] = 127;
    }
    i = MAX_CPERMS - 1;
    j = 0;
    mm_cperms[0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_CPERMS; k++) {
	    if(mm_cperms[k] == j) {
		p0 = k;
		for(l = 0; l < 6; l++) {
		    np0 = p0;
		    for(m = 0; m < 3; m++) {
			np0 = cperms[np0][l];
			if(mm_cperms[np0] == 127) {
			    mm_cperms[np0] = j + 1;
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
#undef params

