//
//  smc_types.c
//  smc_utils
//
//  Created by Mark Garrett on 13/12/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//
#define __ALSType_str__
#include "smc_types.h"
#undef __ALSType_str__



const char *get_ALSType_str( int idx)
{
    if ((idx < 0) || ( idx >  ALSType_str_max )) {
        idx = 0;
    }
    return (ALSType_str[idx]);
}


ala_t   *get_ala(char *buf)
{
    ala_t *rval;
    rval = (ala_t * ) NULL;
    return (rval);
}
