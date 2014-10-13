//
//  fixedpoint.h
//  smc_mon
//
//  Created by Mark Garrett on 24/11/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_mon_fixedpoint_h
#define smc_mon_fixedpoint_h

#include <math.h>
#include <sys/types.h>
#include <stdint.h>
#include <IOKit/IOKitLib.h>
#include <arpa/inet.h>

int     hextodecimal(char c);
double  numeric2float(char *dtype, char *dbytes);


UInt32  smctohl(char *smcintptr);
UInt16  htosmcstr(char *hintptr);



void    htosmclstr(char *dst, char *src);
UInt16  htosmcs(char *hintptr);


#endif
