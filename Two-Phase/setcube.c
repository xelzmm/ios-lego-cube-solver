#include "setcube.h"

static char corners[8][3][3] = {
    {"ULB", "BUL", "LBU"},
    {"UBR", "RUB", "BRU"},
    {"URF", "FUR", "RFU"},
    {"UFL", "LUF", "FLU"},
    {"DBL", "LDB", "BLD"},
    {"DRB", "BDR", "RBD"},
    {"DFR", "RDF", "FRD"},
    {"DLF", "FDL", "LFD"}};

static char edges[12][2][2] = {
    {"UB", "BU"},
    {"UR", "RU"},
    {"UF", "FU"},
    {"UL", "LU"},
    {"DB", "BD"},
    {"DR", "RD"},
    {"DF", "FD"},
    {"DL", "LD"},
    {"BL", "LB"},
    {"BR", "RB"},
    {"FR", "RF"},
    {"FL", "LF"}};

static int cube_found, orient_found;

static void find_corner(c)
char *c;
{
int i, j;

    for(i = 0; i < 8; i++) {
	for(j = 0; j < 3; j++) {
	    if(!strncmp(corners[i][j], c, 3)) {
		cube_found = i;
		orient_found = j;
		return;
	    }
	}
    }
    fprintf(stderr, "Illegal corner found: %.3s\n", c);
    exit(1);
}

static void find_edge(c)
char *c;
{
int i, j;

    for(i = 0; i < 12; i++) {
	for(j = 0; j < 2; j++) {
	    if(!strncmp(edges[i][j], c, 2)) {
		cube_found = i;
		orient_found = j;
		return;
	    }
	}
    }
    fprintf(stderr, "Illegal edge found: %.2s\n", c);
    exit(1);
}

void set_cube()
{
char corner[3], edge[2];
    corner[0] = U[0][0];
    corner[1] = L[0][2];
    corner[2] = B[2][0];
    find_corner(corner);
    cube[0][0][0][0] = cube_found;
    cube[0][0][0][1] = orient_found;
    corner[0] = U[0][2];
    corner[1] = B[2][2];
    corner[2] = R[0][0];
    find_corner(corner);
    cube[0][0][2][0] = cube_found;
    cube[0][0][2][1] = orient_found;
    corner[0] = U[2][2];
    corner[1] = R[2][0];
    corner[2] = F[0][2];
    find_corner(corner);
    cube[0][2][2][0] = cube_found;
    cube[0][2][2][1] = orient_found;
    corner[0] = U[2][0];
    corner[1] = F[0][0];
    corner[2] = L[2][2];
    find_corner(corner);
    cube[0][2][0][0] = cube_found;
    cube[0][2][0][1] = orient_found;
    corner[0] = D[2][2];
    corner[1] = B[0][0];
    corner[2] = L[0][0];
    find_corner(corner);
    cube[2][0][0][0] = cube_found;
    cube[2][0][0][1] = orient_found;
    corner[0] = D[2][0];
    corner[1] = R[0][2];
    corner[2] = B[0][2];
    find_corner(corner);
    cube[2][0][2][0] = cube_found;
    cube[2][0][2][1] = orient_found;
    corner[0] = D[0][0];
    corner[1] = F[2][2];
    corner[2] = R[2][2];
    find_corner(corner);
    cube[2][2][2][0] = cube_found;
    cube[2][2][2][1] = orient_found;
    corner[0] = D[0][2];
    corner[1] = L[2][0];
    corner[2] = F[2][0];
    find_corner(corner);
    cube[2][2][0][0] = cube_found;
    cube[2][2][0][1] = orient_found;
    edge[0] = U[0][1];
    edge[1] = B[2][1];
    find_edge(edge);
    cube[0][0][1][0] = cube_found;
    cube[0][0][1][1] = orient_found;
    edge[0] = U[1][2];
    edge[1] = R[1][0];
    find_edge(edge);
    cube[0][1][2][0] = cube_found;
    cube[0][1][2][1] = orient_found;
    edge[0] = U[2][1];
    edge[1] = F[0][1];
    find_edge(edge);
    cube[0][2][1][0] = cube_found;
    cube[0][2][1][1] = orient_found;
    edge[0] = U[1][0];
    edge[1] = L[1][2];
    find_edge(edge);
    cube[0][1][0][0] = cube_found;
    cube[0][1][0][1] = orient_found;
    edge[0] = D[2][1];
    edge[1] = B[0][1];
    find_edge(edge);
    cube[2][0][1][0] = cube_found;
    cube[2][0][1][1] = orient_found;
    edge[0] = D[1][0];
    edge[1] = R[1][2];
    find_edge(edge);
    cube[2][1][2][0] = cube_found;
    cube[2][1][2][1] = orient_found;
    edge[0] = D[0][1];
    edge[1] = F[2][1];
    find_edge(edge);
    cube[2][2][1][0] = cube_found;
    cube[2][2][1][1] = orient_found;
    edge[0] = D[1][2];
    edge[1] = L[1][0];
    find_edge(edge);
    cube[2][1][0][0] = cube_found;
    cube[2][1][0][1] = orient_found;
    edge[0] = B[1][0];
    edge[1] = L[0][1];
    find_edge(edge);
    cube[1][0][0][0] = cube_found;
    cube[1][0][0][1] = orient_found;
    edge[0] = B[1][2];
    edge[1] = R[0][1];
    find_edge(edge);
    cube[1][0][2][0] = cube_found;
    cube[1][0][2][1] = orient_found;
    edge[0] = F[1][2];
    edge[1] = R[2][1];
    find_edge(edge);
    cube[1][2][2][0] = cube_found;
    cube[1][2][2][1] = orient_found;
    edge[0] = F[1][0];
    edge[1] = L[2][1];
    find_edge(edge);
    cube[1][2][0][0] = cube_found;
    cube[1][2][0][1] = orient_found;
}

