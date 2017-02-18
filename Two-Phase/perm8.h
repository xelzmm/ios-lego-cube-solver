static int perm8_val(int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7)
{
int p[8], i, res, k;

    for(i = 0; i < 8; i++) {
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
    res = res * 7 + k;
    p[p1] = 1;
    k = 0;
    for(i = 0; i < p2; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 6 + k;
    p[p2] = 1;
    k = 0;
    for(i = 0; i < p3; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 5 + k;
    p[p3] = 1;
    k = 0;
    for(i = 0; i < p4; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 4 + k;
    p[p4] = 1;
    k = 0;
    for(i = 0; i < p5; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 3 + k;
    p[p5] = 1;
    k = 0;
    for(i = 0; i < p6; i++) {
	if(!p[i]) {
	    k++;
	}
    }
    res = res * 2 + k;
    p[p6] = 1;
    return res;
}

static void val_perm8(int perm,int *p0,int *p1,int *p2,int *p3,int *p4,int *p5,int *p6,int *p7)
{
int p[8], i, k, r;

    for(i = 0; i < 8; i++) {
	p[i] = 0;
    }
    k = perm / 5040;
    perm -= k * 5040;
    r = k;
    p[r] = 1;
    *p0 = r;
    k = perm / 720;
    perm -= k * 720;
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
    k = perm / 120;
    perm -= k * 120;
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
    k = perm / 24;
    perm -= k * 24;
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
    k = perm / 6;
    perm -= k * 6;
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
    *p4 = r;
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
    *p5 = r;
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
    *p6 = r;
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
    *p7 = r;
}

#ifdef IPERM
void inv_perm8(p)
int p[8];
{
int p1[8], i;

    for(i = 0; i < 8; i++) {
	p1[p[i]] = i;
    }
    for(i = 0; i < 8; i++) {
	p[i] = p1[i];
    }
}

int inv_perm8_val(i)
int i;
{
int p[8];

    val_perm8(i, p+0,p+1,p+2,p+3,p+4,p+5,p+6,p+7);
    inv_perm8(p);
    return perm8_val(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);
}
#endif /* IPERM */

#ifdef PARITY
int perm8_parity(p1)
int p1[8];
{
int p[8], i, j, par;
    for(i = 0; i < 8; i++) {
	p[i] = p1[i];
    }
    par = 0;
    for(i = 0; i < 8; i++) {
	if(p[i] != i) {
	    par = 1 - par;
	    for(j = i + 1; j < 8; j++) {
		if(p[j] == i) {
		    p[j] = p[i];
		}
	    }
	}
    }
    return par;
}
#endif /* PARITY */

