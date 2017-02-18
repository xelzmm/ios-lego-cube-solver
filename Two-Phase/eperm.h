/* Edge orderliness */
/* Numbering of edge cubelets top layer to bottom:
     .  0  .
     3  .  1
     .  2  .

     .  .  .
     .  .  .
     .  .  .

     .  4  .
     7  .  5
     .  6  .
*/

#define MAX_EPERMS	40320

static unsigned short eperms[MAX_EPERMS][6];
#ifndef NOMAX
static char mm_eperms[MAX_EPERMS];
#endif /* NOMAX */
#ifdef IPERM
static unsigned short eperms_inv[MAX_EPERMS];
#endif /* IPERM */

static void init_eperms()
{
int i, j, k, l, m;
int p0, p1, p2, p3, p4, p5, p6, p7;
int np0, np1, np2, np3, np4, np5, np6, np7;
#define params	np0,np1,np2,np3,np4,np5,np6,np7

    for(i = 0; i < MAX_EPERMS; i++) {
#ifdef IPERM
	eperms_inv[i] = inv_perm8_val(i);
#endif /* IPERM */
	val_perm8(i,&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7);
	/* F^2 */
	np0 = p0;
	np1 = p1;
	np2 = p6;
	np3 = p3;
	np4 = p4;
	np5 = p5;
	np6 = p2;
	np7 = p7;
	eperms[i][0] = perm8_val(params);
	/* R^2 */
	np0 = p0;
	np1 = p5;
	np2 = p2;
	np3 = p3;
	np4 = p4;
	np5 = p1;
	np6 = p6;
	np7 = p7;
	eperms[i][1] = perm8_val(params);
	/* U */
	np0 = p3;
	np1 = p0;
	np2 = p1;
	np3 = p2;
	np4 = p4;
	np5 = p5;
	np6 = p6;
	np7 = p7;
	eperms[i][2] = perm8_val(params);
	/* B^2 */
	np0 = p4;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	np4 = p0;
	np5 = p5;
	np6 = p6;
	np7 = p7;
	eperms[i][3] = perm8_val(params);
	/* L^2 */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p7;
	np4 = p4;
	np5 = p5;
	np6 = p6;
	np7 = p3;
	eperms[i][4] = perm8_val(params);
	/* D */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	np4 = p5;
	np5 = p6;
	np6 = p7;
	np7 = p4;
	eperms[i][5] = perm8_val(params);
    }
#ifdef VERBOSE
    fprintf(stderr, "\tInitialized = %d\n", MAX_EPERMS);
#endif /* VERBOSE */
#ifndef NOMAX
    for(i = 0; i < MAX_EPERMS; i++) {
	mm_eperms[i] = 127;
    }
    i = MAX_EPERMS - 1;
    j = 0;
    mm_eperms[0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_EPERMS; k++) {
	    if(mm_eperms[k] == j) {
		p0 = k;
		for(l = 0; l < 6; l++) {
		    np0 = p0;
		    for(m = 0; m < 3; m++) {
			np0 = eperms[np0][l];
			if(mm_eperms[np0] == 127) {
			    mm_eperms[np0] = j + 1;
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

