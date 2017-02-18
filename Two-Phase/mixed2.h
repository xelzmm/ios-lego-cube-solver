static char mm_cs[MAX_CPERMS][MAX_SPERMS];
static char mm_es[MAX_EPERMS][MAX_SPERMS];

static void init_mixed2()
{
int i, j, k, l, m, n;
int c0, nc0, e0, ne0, s0, ns0;

    for(i = 0; i < MAX_CPERMS; i++) {
	for(j = 0; j < MAX_SPERMS; j++) {
	    mm_cs[i][j] = 127;
	}
    }
    i = MAX_CPERMS * MAX_SPERMS - 1;
    j = 0;
    mm_cs[0][0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_CPERMS; k++) {
	    for(l = 0; l < MAX_SPERMS; l++) {
		if(mm_cs[k][l] == j) {
		    c0 = k;
		    s0 = l;
		    for(m = 0; m < 6; m++) {
			nc0 = c0;
			ns0 = s0;
			for(n = 0; n < 3; n++) {
			    nc0 = cperms[nc0][m];
			    ns0 = sperms[ns0][m];
			    if(mm_cs[nc0][ns0] == 127) {
				mm_cs[nc0][ns0] = j + 1;
				i--;
			    }
			}
		    }
		}
	    }
	}
	j++;
    }
#ifdef VERBOSE
    fprintf(stderr, "\tMaxpath(c+s) = %d\n", j);
#endif /* VERBOSE */
    for(i = 0; i < MAX_EPERMS; i++) {
	for(j = 0; j < MAX_SPERMS; j++) {
	    mm_es[i][j] = 127;
	}
    }
    i = MAX_EPERMS * MAX_SPERMS - 1;
    j = 0;
    mm_es[0][0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_EPERMS; k++) {
	    for(l = 0; l < MAX_SPERMS; l++) {
		if(mm_es[k][l] == j) {
		    e0 = k;
		    s0 = l;
		    for(m = 0; m < 6; m++) {
			ne0 = e0;
			ns0 = s0;
			for(n = 0; n < 3; n++) {
			    ne0 = eperms[ne0][m];
			    ns0 = sperms[ns0][m];
			    if(mm_es[ne0][ns0] == 127) {
				mm_es[ne0][ns0] = j + 1;
				i--;
			    }
			}
		    }
		}
	    }
	}
	j++;
    }
#ifdef VERBOSE
    fprintf(stderr, "\tMaxpath(e+s) = %d\n", j);
#endif /* VERBOSE */
}

