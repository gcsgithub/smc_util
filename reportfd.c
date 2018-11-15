//
//  reportfd.c
//  smc_utils
//
//  Created by mark on 29/03/2014.
//  Copyright (c) 2014 Garetech Computer Solutions. All rights reserved.
//
#include <stdarg.h>
#include <stdio.h>
#include "reportfd.h"
#include "smc_utils_gbl.h"


extern  gbl_params_t PARAMS;

/////////////////////////////////////////
int reportfd(flg_e flgmask, char *fmt, ...)
/////////////////////////////////////////
{
    va_list  ap;
    int rval;
    
    gbl_params_t    *params = &PARAMS;
    
    rval  = -1;
    
    va_start(ap, fmt);
    if (flag_test(F_INDEX)) {
        rval = fprintf(params->outfd, "(%ld)", (long) params->fldidx++);
        if (rval>=0) {
            rval = vfprintf(params->outfd, fmt, ap);
        }
    }
    else {
        if ((flag_test(F_ALWAYS)) || (flag_test(flgmask))) {
            rval = vfprintf(params->outfd, fmt, ap);
        }
    }
 
   if (flgmask & F_NL) {
       newline();
   }
    
    return(rval);
}

void newline()
{
    gbl_params_t    *params = &PARAMS;
    
    if ((params->newline) && (*params->newline)) {
        fputc(*params->newline, params->outfd);
    }
}

/*
/////////////////////////
int reportfd_fldidx(void)
/////////////////////////
{
    int rval;
    gbl_params_t    *params = &PARAMS;
    
    rval = fprintf(params->outfd, "(%ld)", (long) params->fldidx);
    
    return(rval);
}
*/

//////////////////////////
int flag_test(int flgmask)
//////////////////////////
{
    int rval;
    gbl_params_t    *params = &PARAMS;
    // 228 = F_DESCRIBE(128), F_VALUES(64), F_NOISY(32), F_DUMPHEX(4)
    if (flgmask == F_ALWAYS) {
        rval = 1;
    }
    else {
        rval = params->flg & flgmask;
    }
 
    return(rval);
}


//////////////////
int reportc(int c)
//////////////////
{
    int rval;
    gbl_params_t    *params = &PARAMS;

    rval = fputc(c, params->outfd);
    return(rval);
    
}
