//
//  smc_desc_t.h
//  smc_utils
//
//  Created by Mark Garrett on 02/12/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_smc_desc_t_h
#define smc_utils_smc_desc_t_h

#define KA_NULL     0
#define KA_R        1
#define KA_W        2
#define KA_CONST    4
#define KA_VAR      8
#define KA_STR     16
#define KA_DESC    32
#define KA_FUNC    64
#define KA_ATOMIC 128

typedef enum {
    K_NULL          =   (KA_NULL),
    K_CONST         =   (KA_R|KA_CONST), 
    K_DESC_STR      =   (KA_R|KA_DESC|KA_STR), 
    K_FUNC_R        =   (KA_R|KA_FUNC), 
    K_FUNC_RW       =   (KA_R|KA_W|KA_FUNC),  
    K_FUNC_W        =   (KA_W|KA_FUNC), 
    K_VAR_ATOM_R    =   (KA_R|KA_VAR|KA_ATOMIC), 
    K_VAR_ATOM_RW   =   (KA_R|KA_W|KA_VAR|KA_ATOMIC),  
    K_VAR_R         =   (KA_R|KA_VAR),  
    K_VAR_RW        =   (KA_R|KA_W|KA_VAR), 
    K_VAR_W         =   (KA_W|KA_VAR)
} smc_attr_e;

// {"IG0R","fp4c",0,K_VAR_ATOM_RW,"GPU 0 rail current."},
typedef struct smc_desc_s {
    char        *d_keyname;
    char        *d_keytype;
    int         d_keylen;
    smc_attr_e  d_attrib;
    char        *d_desc;
} smc_desc_t;



#endif
