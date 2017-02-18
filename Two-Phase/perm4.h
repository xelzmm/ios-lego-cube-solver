static int perm4_val(int p0,int p1,int p2,int p3)
{
int p[4], i, res, k;

    for(i = 0; i < 4; i++) {
	p[i] = 0;
    }
    res = p0;
    p[p0] = 1;
    k = 0;
    for(i = 0; i < p1; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 3 + k;
    p[p1] = 1;
    k = 0;
    for(i = 0; i < p2; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 2 + k;
    p[p2] = 1;
    return res;
}

static void val_perm4(int perm,int *p0,int *p1,int *p2,int *p3)
{
int p[4], i, k, r;

    for(i = 0; i < 4; i++) {
	p[i] = 0;
    }
    k = perm / 6;
    perm -= k * 6;
    r = k;
    p[r] = 1;
    *p0 = r;
    k = perm / 2;
    perm -= k * 2;
    r = k;
    i = 0;
    while(k >= 0) {
	if(p[i]) {
	    r++;
	} else {
	    k--;
	}
	i++;
    }
    p[r] = 1;
    *p1 = r;
    k = perm;
    r = k;
    i = 0;
    while(k >= 0) {
	if(p[i]) {
	    r++;
	} else {
	    k--;
	}
	i++;
    }
    p[r] = 1;
    *p2 = r;
    k = 0;
    r = k;
    i = 0;
    while(k >= 0) {
	if(p[i]) {
	    r++;
	} else {
	    k--;
	}
	i++;
    }
    p[r] = 1;
    *p3 = r;
}

#ifdef IPERM
void inv_perm4(p)
int p[4];
{
int p1[4], i;

    for(i = 0; i < 4; i++) {
	p1[p[i]] = i;
    }
    for(i = 0; i < 4; i++) {
	p[i] = p1[i];
    }
}

int inv_perm4_val(i)
int i;
{
int p[4];

    val_perm4(i, p+0,p+1,p+2,p+3);
    inv_perm4(p);
    return perm4_val(p[0],p[1],p[2],p[3]);
}
#endif /* IPERM */

#ifdef PARITY
int perm4_parity(p1)
int p1[4];
{
int p[4], i, j, par;
    for(i = 0; i < 4; i++) {
	p[i] = p1[i];
    }
    par = 0;
    for(i = 0; i < 4; i++) {
	if(p[i] != i) {
	    par = 1 - par;
	    for(j = i + 1; j < 4; j++) {
		if(p[j] == i) {
		    p[j] = p[i];
		}
	    }
	}
    }
    return par;
}
#endif /* PARITY */

