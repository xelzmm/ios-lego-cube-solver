//
//  phase1.h
//  NXT Cuber
//
//  Created by xelz on 15-1-30.
//  Copyright (c) 2015年 xelz. All rights reserved.
//

#ifndef NXT_Cuber_phase1_h
#define NXT_Cuber_phase1_h

#include "globals.h"

#include "twist.h"
#include "flip.h"
#define CHOICE4
#include "choice.h"
#ifdef LARGE_MEM
#include "mixed1.h"
#endif /* LARGE_MEM */
#include "permcube.h"
#include "prntsol.h"
#include "phase2.h"

void init_phase1();

int init_phase1_cube();

void do_phase1(int twist, int flip, int choice, int dont1, int dont2);

int phase1(int max_todo) ;

#endif
