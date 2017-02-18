//
//  cube.h
//  NXT Cuber
//
//  Created by xelz on 15-2-1.
//  Copyright (c) 2015年 xelz. All rights reserved.
//

#ifndef NXT_Cuber_cube_h
#define NXT_Cuber_cube_h
#include "globals.h"
#include "string.h"
#include "phase1.h"
#include "phase2.h"
#include "setcube.h"

#if defined __cplusplus
extern "C" {
#endif
    
char* solvecube(char const* state);

void init();
    
#if defined __cplusplus
};
#endif

#endif
