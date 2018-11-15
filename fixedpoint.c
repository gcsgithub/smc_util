//
//  fixedpoint.c
//  smc_utils
//
//  Created by Mark Garrett on 24/11/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#include "fixedpoint.h"
#include <ctype.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>


int hextodecimal(char c)
{
    int result;
    char    C;
    result = 0;
    // 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
    //           01234567890123456789012345
    //           1         2         3  
    
    C=toupper(c);
    
    if (C>='0' && C <='9') {
        result = (C-'0'); 
    } else {
        if (C>='A' && C<='Z') {
            result = C-'A'+10;
        }
    }
    return (result);
}

double  numeric2float(char *dtype, char *dbytes)
{
    /*
     deal with all numeric key values and return a double float representation
     if error or non-numeric data type  return nan()
     
     Fixed point data types are 4 char's long
     1st 2 are the type followed by 2 hex digits representing bits left of decimal and right of decimal
     
     */
    int     hassign = 0;
    int     bits_left, bits_right, total_bits;
    int     dsize;  // howmany bytes needed to hold total_bits rounded up of course
    int     sign;
    int     thebits;
    char    *bitsptr = (char *)&thebits;
    char    fltval[4];
    
    int     bitcount;
    int     idx;
    int     scale;
    typedef enum {
        t_int    = 1,
        t_fixed  = 2,
        t_float  = 3
    } dtype_t;
    
    dtype_t dt;
    
    double  result;
    
    if (dtype[0] == 's' && dtype[1] == 'p') {
        hassign = 1;    // Signed fixed Point
        dt = t_fixed;
        
    }
    else if (dtype[0] == 'f' && dtype[1] == 'p') {
        hassign = 0;    // Unsigned fixed Point
        dt      = t_fixed;
        
    }
    else if (dtype[0] == 'f' && dtype[1] == 'l' && dtype[2] == 't') { // "flt "
        dt         = t_float;
        hassign    = 0;
        total_bits = 32;
    }
    else if (dtype[0] == 'u' && dtype[1] == 'i') { //  "ui8 ", "ui16", "ui32
        hassign    = 0;    // Unsigned Integer
        dt         = t_int;
    }
    else if (dtype[0] == 's' && dtype[1] == 'i') { //  "si8 ", "si16", "si32"
        hassign    = 1;    // Signed Integer
        dt         = t_int;
    }
    else {
        result     = nan("-2");  // not a numeric type we know about
        return(result);
    }
    
    switch(dt) {
        case    t_fixed:
            bits_left  = hextodecimal(dtype[2]);
            bits_right = hextodecimal(dtype[3]);
            total_bits = hassign + bits_left + bits_right;
            break;
            
        case    t_float:
            total_bits = 32;
            break;
            
        default:
            total_bits = atoi(&dtype[2]);
            break;
    }
    
    dsize   = total_bits >> 3;     // howmany bytes
    if ((dsize<<3) < total_bits) { // check of a remainder and round up if needed
        dsize++;
    }
    
    if (dsize <1 || dsize > 4) {
        result = nan("-3");
        return(result);
    }
    
    if (hassign) {
        sign = dbytes[0] >> 7;
        thebits = dbytes[0] & 0x7f;
    }
    else {
        sign = 0;
        thebits = dbytes[0] & 0xff;        
    }
    
    bitcount = total_bits-8; // consumed 8 bits already
                             // used the 1st now consume all but last 
    for(idx=1;idx < dsize - 1;idx++)  {
        thebits  <<=8;   // make room for more
        thebits  |= dbytes[idx];
        bitcount -= 8; // consume 8 bits
    }
    // TODO: maybe reinstate the mask calculation to allow for chunks smaller than 8bits
    // to be properly masked off
    thebits <<= bitcount; // make room
    thebits |= (dbytes[idx] >> (8-bitcount)) &0xff;
    
    switch (dt) {
        case t_int:
            scale = 1;
            break;
        case t_fixed:
            // now scale the integer into a floating point number
            scale = 1<<(bits_right);
            break;
        case t_float:
            fltval[0] = bitsptr[3];
            fltval[1] = bitsptr[2];
            fltval[2] = bitsptr[1];
            fltval[3] = bitsptr[0];
            
            result = (double) (float) *(float *) fltval;
            //result = (double) (float ) thebits;
            return (result);
            break;
        default:
            break;
    }
    
    result = ((double) thebits) / scale;
    
    result *= (sign?-1:1);
    
    return(result);
}



UInt32 smctohl(char *smcintptr)
{ // read unaligned 32bit value in SMC word order
  // convert it to Intel little endian
  // Probably should make this usable on bigendian machines but
  // they are not likely to exist with this SMC
    
    UInt32 rval;
    int idx;
    
    rval = 0;
    for (idx=0; idx<=3; idx++)
    {
        rval =  rval << 8 | smcintptr[idx];
    }
    
    return rval;
}

void htosmclstr(char *dst, char *src)
{
    // convert host 32bit as a char string to smc string
    dst[3] = src[0];
    dst[2] = src[1];
    dst[1] = src[2];
    dst[0] = src[3];
    
}

UInt16 htosmcs(char *hintptr)
{ // convert a 16bit unaligned host order littleendian to SMC big endian
    UInt16 rval;
    
    rval = hintptr[0];
    rval = rval << 8 | hintptr[1];
    
    return (rval);
}


