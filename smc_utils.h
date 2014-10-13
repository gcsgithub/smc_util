//
//  smc_utils.h
//  smc_utils
//
//  Created by Mark Garrett on 25/11/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_smc_utils_h
#define smc_utils_smc_utils_h

#include <IOKit/IOKitLib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fixedpoint.h"
#include "smc_defs.h"
#include "smc_utils_gbl.h"

typedef enum { 
    UD, LST, RD, WR, RW, FAN,TEMP
} direction_t;


kern_return_t smc_open( io_connect_t *connptr);
kern_return_t smc_close(io_connect_t *connptr);
kern_return_t smc_io(   io_connect_t conn, smc_io_data_t *in, smc_io_data_t *out );


kern_return_t SMC_key_write(io_connect_t conn, char *keyname,short val, SMC_key_val_t *keyval );
kern_return_t SMC_key_getinfo(io_connect_t conn, char *keyname,SMC_key_val_t *keyval );
kern_return_t SMC_key_value_get(io_connect_t conn, char *keyname,SMC_key_val_t *keyval );
kern_return_t SMC_key_value_by_index_get(io_connect_t conn, UInt32 keyidx, SMC_key_val_t *keyval );

double        smc_key_read_numeric(io_connect_t conn, char *key);
int           smc_key_read(        io_connect_t conn, char *key);
kern_return_t smc_fan_set(         io_connect_t conn, char *key, int rpm);
int           smc_key_write(       io_connect_t conn, char *key, char *value);

int           smc_key_display(io_connect_t conn, char *keyptr);
int           smc_keyval_display(SMC_key_val_t *keyvalue);
int           smc_display_allkeys(io_connect_t conn, char *model);
double        report_temp(         io_connect_t conn, char *key, char *desc);
void          report_fans(io_connect_t conn);
void          report_fan (io_connect_t conn, int fan);

// CFStringRef	GetModelName(void);

const char *fan_loc(int idx);
const char *fan_type(int idx);
char        *describe_fan(SMC_key_val_t   *keyvalue);
char        *get_sysmodel_dynamic(void);
int         dump_hex(int size,  char *buf);
int         dump_ascii(int size, char *buf);
int         isnull2end(int len, char *buf);
short       readshort(char *sp);
ushort      readushort(char *sp);


#endif
