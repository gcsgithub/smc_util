//
//  smc_defs.h
//  smc_utils
//
//  Created by Mark Garrett on 26/11/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_smc_defs_h
#define smc_utils_smc_defs_h

#include <IOKit/IOKitLib.h>
#include "smc_desc_t.h"

typedef UInt32  SMC_keysize_t;
typedef char    SMC_keytype_t[(sizeof(UInt32))];
typedef char    SMC_keynam_t[(sizeof(UInt32))];
typedef char    SMCKeyData_t[(sizeof(UInt32))];
typedef char    SMC_keyattr_t[(sizeof(UInt32))];
typedef char    SMC_key_data_t[32];

typedef struct {
    char            maj;
    char            min;
    char            bld;
    char            res; 
    UInt16          rel;
} SMC_ver_t; // refer:  REV   [{rev]  UNK(bytes 01 42 0f 00 00 04)
//  6bytes SMC Version (system):	 1.42f4 printf("%x.%x%x%x", maj,min,bld,res,rel)


typedef struct {             //eg PC1C  [fp88]  8.265625(bytes 08 44)
    SMC_keysize_t   vsize;   // 2
    SMC_keytype_t   vtype;   // fp88
    SMC_keynam_t    vkey;    // PC1C
    SMC_key_data_t  vbytes;  // 08 44
    smc_desc_t      *smc_defaults; // default key info from lookup of vkey
} SMC_key_val_t;

typedef struct {
    SMC_keynam_t    key; 
    SMC_ver_t       ver;         //  6 bytes 
    char            limits[16];  // 16 bytes 16+6 = 22
    
    SMC_keysize_t   ksize;       // key info 9 bytes
    SMC_keytype_t   ktype;
    SMC_keyattr_t   kattr;  
    
    char            io_sts;      // status of last cmd 0 or 1?
    char            status;
    char            cmd;         // see enum cmd_t
    UInt32          p1_lw;
    SMC_key_data_t  bytes;
} smc_io_data_t;


typedef enum {
    // the user client method name constants 
    kSMCUserClientOpen,  // 0
    kSMCUserClientClose, // 1
    kSMCHandleYPCEvent,  // 2
    kSMCPlaceholder1,	 // 3
    kSMCNumberOfMethods, // 4
    kSMCReadKey,         // 5
    kSMCWriteKey,        // 6
    kSMCGetKeyCount,     // 7
    kSMCGetKeyFromIndex, // 8
    kSMCGetKeyInfo,      // 9
    kSMCFireInterrupt,   // 10
    kSMCGetPLimits,      // 11
    kSMCGetVers,         // 12
    kSMCPlaceholder2,	 // 13
    kSMCReadStatus,      // 14
    kSMCReadResult,      // 15
    kSMCVariableCommand  // 16
} cmd_t;

#endif
