//
//  phase2.h
//  NXT Cuber
//
//  Created by xelz on 15-1-30.
//  Copyright (c) 2015年 xelz. All rights reserved.
//

#ifndef NXT_Cuber_phase2_h
#define NXT_Cuber_phase2_h

#include "globals.h"
#include "stdlib.h"

#define SUBGROUP
#include "perm8.h"
#include "perm4.h"
#include "cperm.h"
#include "eperm.h"
#include "sperm.h"
#ifdef LARGE_MEM
#include "mixed2.h"
#endif /* LARGE_MEM */
#include "prntsol.h"

void init_phase2();

int init_phase2_cube();

void do_phase2(int cperm, int eperm, int sperm, int dont1, int dont2);

int phase2(int max_todo, int dont1, int dont2);

#endif
