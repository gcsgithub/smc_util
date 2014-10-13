//
//  smc_utils_gbl.h
//  smc_utils
//
//  Created by mark on 29/03/2014.
//  Copyright (c) 2014 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_smc_utils_gbl_h
#define smc_utils_smc_utils_gbl_h

#include <stdio.h>
#include <IOKit/IOKitLib.h>

typedef enum {
    F_ALWAYS   =    0,
    F_VERBOSE  =    1,
    F_NL       =    2,
    F_DUMPHEX  =    4,
    F_SHOWSIZE =    8,
    F_SHOWTYPE =   16,
    F_NOISY    =   32,
    F_VALUES   =   64,
    F_DESCRIBE =  128,
    F_PRIVATE  =  256,
    F_DEBUG    =  512,
    F_INDEX    = 1024
} flg_e;

typedef struct {
    char        *progid;
    flg_e       flg;
    
    
    char        *newline;
    int         dbg;
    long        fldidx;
    FILE        *outfd;
    char        *model;
    io_connect_t conn;
} gbl_params_t;


#endif
