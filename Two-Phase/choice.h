/* Choosiness */
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
#define CHOICE4


#define MAX_CHOICES	495
#define DO_CHOICE	4

#define MAX_PERMS	4096

static unsigned short choices[MAX_CHOICES][6];
#ifndef NOMAX
static char mm_choices[MAX_CHOICES];
#endif /* NOMAX */
static unsigned short choice_to_perm[MAX_CHOICES];
static unsigned short perm_to_choice[MAX_PERMS];

static void val_perm(int v,int *p0,int *p1,int *p2,int *p3,int *p4,int *p5,int *p6,int *p7,int *p8,int *p9,int *pa,int *pb)
{
    *pb = v & 1;
    v >>= 1;
    *pa = v & 1;
    v >>= 1;
    *p9 = v & 1;
    v >>= 1;
    *p8 = v & 1;
    v >>= 1;
    *p7 = v & 1;
    v >>= 1;
    *p6 = v & 1;
    v >>= 1;
    *p5 = v & 1;
    v >>= 1;
    *p4 = v & 1;
    v >>= 1;
    *p3 = v & 1;
    v >>= 1;
    *p2 = v & 1;
    v >>= 1;
    *p1 = v & 1;
    v >>= 1;
    *p0 = v & 1;
}

static int choice_val(int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9,int pa,int pb)
{
   return perm_to_choice[((((((((((p0*2+
				   p1)*2+
				   p2)*2+
				   p3)*2+
				   p4)*2+
				   p5)*2+
				   p6)*2+
				   p7)*2+
				   p8)*2+
				   p9)*2+
				   pa)*2+
				   pb];
}

static void val_choice(int v,int *p0,int *p1,int *p2,int *p3,int *p4,int *p5,int *p6,int *p7,int *p8,int *p9,int *pa,int *pb)
{
    v = choice_to_perm[v];
    val_perm(v,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,pa,pb);
}

static void init_choices()
{
int i, j, k, l, m;
int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, pa, pb;
int np0, np1, np2, np3, np4, np5, np6, np7, np8, np9, npa, npb;
#define params	np0,np1,np2,np3,np4,np5,np6,np7,np8,np9,npa,npb

    j = 0;
    for(i = 0; i < MAX_PERMS; i++) {
	val_perm(i,&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,&p9,&pa,&pb);
	if((p0+p1+p2+p3+p4+p5+p6+p7+p8+p9+pa+pb) == DO_CHOICE) {
	    perm_to_choice[i] = j;
	    choice_to_perm[j] = i;
	    j++;
	}
    }
    for(i = 0; i < MAX_CHOICES; i++) {
	val_choice(i,&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,&p9,&pa,&pb);
	/* F */
	np0 = p0;
	np1 = p1;
	np2 = pb;
	np3 = p3;
	np4 = p4;
	np5 = p5;
	np6 = pa;
	np7 = p7;
	np8 = p8;
	np9 = p9;
	npa = p2;
	npb = p6;
	choices[i][0] = choice_val(params);
	/* R */
	np0 = p0;
	np1 = pa;
	np2 = p2;
	np3 = p3;
	np4 = p4;
	np5 = p9;
	np6 = p6;
	np7 = p7;
	np8 = p8;
	np9 = p1;
	npa = p5;
	npb = pb;
	choices[i][1] = choice_val(params);
	/* U */
	np0 = p3;
	np1 = p0;
	np2 = p1;
	np3 = p2;
	np4 = p4;
	np5 = p5;
	np6 = p6;
	np7 = p7;
	np8 = p8;
	np9 = p9;
	npa = pa;
	npb = pb;
	choices[i][2] = choice_val(params);
	/* B */
	np0 = p9;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	np4 = p8;
	np5 = p5;
	np6 = p6;
	np7 = p7;
	np8 = p0;
	np9 = p4;
	npa = pa;
	npb = pb;
	choices[i][3] = choice_val(params);
	/* L */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p8;
	np4 = p4;
	np5 = p5;
	np6 = p6;
	np7 = pb;
	np8 = p7;
	np9 = p9;
	npa = pa;
	npb = p3;
	choices[i][4] = choice_val(params);
	/* D */
	np0 = p0;
	np1 = p1;
	np2 = p2;
	np3 = p3;
	np4 = p5;
	np5 = p6;
	np6 = p7;
	np7 = p4;
	np8 = p8;
	np9 = p9;
	npa = pa;
	npb = pb;
	choices[i][5] = choice_val(params);
    }
#ifdef VERBOSE
    fprintf(stderr, "\tInitialized = %d\n", MAX_CHOICES);
#endif /* VERBOSE */
#ifndef NOMAX
    for(i = 0; i < MAX_CHOICES; i++) {
	mm_choices[i] = 127;
    }
    i = MAX_CHOICES - 1;
    j = 0;
    mm_choices[0] = 0;
    while(i > 0) {
	for(k = 0; k < MAX_CHOICES; k++) {
	    if(mm_choices[k] == j) {
		p0 = k;
		for(l = 0; l < 6; l++) {
		    np0 = p0;
		    for(m = 0; m < 3; m++) {
			np0 = choices[np0][l];
			if(mm_choices[np0] == 127) {
			    mm_choices[np0] = j + 1;
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

