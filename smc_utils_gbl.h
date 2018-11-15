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
    F_ALWAYS   =    1,
    F_VERBOSE  =    2,
    F_NL       =    4,
    F_DUMPHEX  =    8,
    F_SHOWSIZE =   16,
    F_SHOWTYPE =   32,
    F_NOISY    =   64,
    F_VALUES   =  128,
    F_DESCRIBE =  256,
    F_PRIVATE  =  512,
    F_DEBUG    = 1024,
    F_INDEX    = 2048,
    F_BINARY   = 4096,
    F_BYTEORDER= 8192
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
