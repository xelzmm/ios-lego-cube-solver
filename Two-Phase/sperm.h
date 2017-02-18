/* Slice orderliness */
/* Numbering of slice cubelets top layer to bottom:
     .  .  .
     .  .  .
     .  .  .

     0  .  1
     .  .  .
     3  .  2

     .  .  .
     .  .  .
     .  .  .
*/

#define MAX_SPERMS	24

static unsigned short sperms[MAX_SPERMS][6];
#ifndef NOMAX
static char mm_sperms[MAX_SPERMS];
#endif /* NOMAX */
#ifdef IPERM
static unsigned short sperms_inv[MAX_SPERMS];
#endif /* IPERM */

static void init_sperms()
{
int i, j, k, l, m;
int p0, p1, p2, p3;
int np0, np1, np2, np3;
#define params	np0,np1,np2,np3

    for(i = 0; i < MAX_SPERMS; i++) {
#ifdef IPERM
	sperms_inv[i] = inv_perm4_val(i);
#endif /* IPERM */
	val_perm4(i,&p0,&p1,&p2,&p3);
	/* F^2 */
	np0 = p0;
	np1 = p1;
	np2 = p3;
	np3 = p2;
	sperms[i][0] = perm4_val(params);
	/* R^2 */
	np0 = p0;
	np1 = p2;
	np2 = p1;
	np3 = p3;
	sperms[i][1] = perm4_val(params);
	/* U */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	sperms[i][2] = perm4_val(params);
	/* B^2 */
	np0 = p1;
	np1 = p0;
	np2 = p2;
	np3 = p3;
	sperms[i][3] = perm4_val(params);
	/* L^2 */
	np0 = p3;
	np1 = p1;
	np2 = p2;
	np3 = p0;
	sperms[i][4] = perm4_val(params);
	/* D */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	sperms[i][5] = perm4_val(params);
    }
#ifdef VERBOSE
    fprintf(stderr, "\tInitialized = %d\n", MAX_SPERMS);
#endif /* VERBOSE */
#ifndef NOMAX
    for(i = 0; i < MAX_SPERMS; i++) {
	mm_sperms[i] = 127;
    }
    i = MAX_SPERMS - 1;
    j = 0;
    mm_sperms[0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_SPERMS; k++) {
	    if(mm_sperms[k] == j) {
		p0 = k;
		for(l = 0; l < 6; l++) {
		    np0 = p0;
		    for(m = 0; m < 3; m++) {
			np0 = sperms[np0][l];
			if(mm_sperms[np0] == 127) {
			    mm_sperms[np0] = j + 1;
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

