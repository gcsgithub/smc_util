//
//  smc_desc.c
//  smc_utils
//
//  Created by Mark Garrett on 01/12/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smc_defs.h"
#define __DEF_SMS_DESC__
#include "smc_desc.h"

int cmp_smc_desc_name(const void *smc1ptr, const void *smc2ptr);

int cmp_smc_desc_name(const void *smc1ptr, const void *smc2ptr)
{
    int res;
    res = 0;
    smc_desc_t *smc1, *smc2;

    if (smc1ptr) {
        smc1 = (smc_desc_t *) smc1ptr;
        if (smc2ptr) {
            smc2 = (smc_desc_t *) smc2ptr;
            res = memcmp(smc1->d_keyname, smc2->d_keyname, 4);
        } else {
            res = -1;
        }
    } else {
        res = 1;
    }
    
    return(res);
}

///////////////////////////////////////////////
smc_desc_t *smc_lookup_desc(SMC_key_val_t *key)
///////////////////////////////////////////////
{
    smc_desc_t      desc_key;
    smc_desc_t      *res;
    const size_t    numelm = sizeof(SMC_DESC)/sizeof(smc_desc_t);
    static const smc_desc_t smc_desc_unknown =  {"UNKN","UNKN",0,K_NULL,"Unknown key"};
    
    desc_key.d_keyname = (char *) &key->vkey;
    
    
    res = (smc_desc_t *) bsearch(&desc_key, &SMC_DESC, numelm, sizeof(smc_desc_t),cmp_smc_desc_name);
    if (res == (smc_desc_t *) NULL) {
        res = (smc_desc_t *) &smc_desc_unknown;
    }
    return(res);
    
}