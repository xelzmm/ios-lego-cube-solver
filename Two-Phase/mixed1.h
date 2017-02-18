static char mm_tf[MAX_TWISTS][MAX_FLIPS];
static char mm_tc[MAX_TWISTS][MAX_CHOICES];
static char mm_fc[MAX_FLIPS][MAX_CHOICES];

static void init_mixed1()
{
int i, j, k, l, m, n;
int t0, nt0, f0, nf0, c0, nc0;

    for(i = 0; i < MAX_TWISTS; i++)  {
	for(j = 0; j < MAX_FLIPS; j++) {
	    mm_tf[i][j] = 127;
	}
    }
    i = MAX_TWISTS * MAX_FLIPS - 1;
    j = 0;
    mm_tf[0][0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_TWISTS; k++) {
	    for(l = 0; l < MAX_FLIPS; l++) {
		if(mm_tf[k][l] == j) {
		    t0 = k;
		    f0 = l;
		    for(m = 0; m < 6; m++) {
			nt0 = t0;
			nf0 = f0;
			for(n = 0; n < 3; n++) {
			    nt0 = twists[nt0][m];
			    nf0 = flips[nf0][m];
			    if(mm_tf[nt0][nf0] == 127) {
				mm_tf[nt0][nf0] = j + 1;
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
    fprintf(stderr, "\tMaxpath(t+f) = %d\n", j);
#endif /* VERBOSE */
    for(i = 0; i < MAX_TWISTS; i++) {
	for(j = 0; j < MAX_CHOICES; j++) {
	    mm_tc[i][j] = 127;
	}
    }
    i = MAX_TWISTS * MAX_CHOICES - 1;
    j = 0;
    mm_tc[0][0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_TWISTS; k++) {
	    for(l = 0; l < MAX_CHOICES; l++) {
		if(mm_tc[k][l] == j) {
		    t0 = k;
		    c0 = l;
		    for(m = 0; m < 6; m++) {
			nt0 = t0;
			nc0 = c0;
			for(n = 0; n < 3; n++) {
			    nt0 = twists[nt0][m];
			    nc0 = choices[nc0][m];
			    if(mm_tc[nt0][nc0] == 127) {
				mm_tc[nt0][nc0] = j + 1;
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
    fprintf(stderr, "\tMaxpath(t+c) = %d\n", j);
#endif /* VERBOSE */
    for(i = 0; i < MAX_FLIPS; i++) {
	for(j = 0; j < MAX_CHOICES; j++) {
	    mm_fc[i][j] = 127;
	}
    }
    i = MAX_FLIPS * MAX_CHOICES - 1;
    j = 0;
    mm_fc[0][0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_FLIPS; k++) {
	    for(l = 0; l < MAX_CHOICES; l++) {
		if(mm_fc[k][l] == j) {
		    f0 = k;
		    c0 = l;
		    for(m = 0; m < 6; m++) {
			nf0 = f0;
			nc0 = c0;
			for(n = 0; n < 3; n++) {
			    nf0 = flips[nf0][m];
			    nc0 = choices[nc0][m];
			    if(mm_fc[nf0][nc0] == 127) {
				mm_fc[nf0][nc0] = j + 1;
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
    fprintf(stderr, "\tMaxpath(f+c) = %d\n", j);
#endif /* VERBOSE */
}

