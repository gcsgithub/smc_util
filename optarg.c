//
//  smc_utils.c
//  smc_utils
//
//  Created by Mark Garrett on 26/11/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
// for sysctl()
#include <sys/types.h>
#include <sys/sysctl.h>
#include <assert.h>
//
// #include "smc_defs.h"
#include "smc_desc.h"
#include "smc_desc_t.h"

#include "smc_utils.h"
#include "fixedpoint.h"
#include "smc_types.h"
#include "reportfd.h"


kern_return_t smc_open(io_connect_t *connptr)
{
    kern_return_t           r0;
    mach_port_t             themaster;
    CFMutableDictionaryRef  AppleSMCdict;
    io_iterator_t           iointerator;
    io_object_t             ioobj;
    
    r0  = IOMasterPort(MACH_PORT_NULL, &themaster);
    if (r0 == kIOReturnSuccess) {
        if ((AppleSMCdict = IOServiceMatching( "AppleSMC" ))) {
            r0 = IOServiceGetMatchingServices( themaster, AppleSMCdict, &iointerator);
            
            if (r0 == kIOReturnSuccess) {
                ioobj = IOIteratorNext(iointerator); // Get the first item in the iterator.
                IOObjectRelease(iointerator);        // we done with iointerator, release it
                if (ioobj) {                         // yep got one there
                    r0 = IOServiceOpen(ioobj, mach_task_self(), 0, connptr);
                    IOObjectRelease(ioobj);          // conn is now setup we done with the entity
                    
                } else {
                    r0 = kIOReturnNoDevice;
                    
                }
            }
        } else {
            r0 = kIOReturnNotFound; // IOServiceMatching nothing matched
        }
    }
    return(r0);
}

kern_return_t smc_close(io_connect_t *conn)
{
    kern_return_t r0;
    r0 =  IOServiceClose(*conn);
    return(r0);
}

kern_return_t smc_io(io_connect_t conn, smc_io_data_t *in, smc_io_data_t *out )
{
    size_t          out_size;
    kern_return_t   r0;
    
    out_size = sizeof(*out);
    
    r0 = IOConnectCallStructMethod(
                                   /* mach_port_t */ conn,       // In
                                   /* uint32_t    */ 2,           // In 0,1,3 did nothing
                                   /* maybe this is the correct reference for the selector:
                                    # ioclasscount | grep AppleSMCC
                                    AppleSMCClient = 1,3 it varies
                                    maybe we can do what ever ioclasscount does?
                                    AppleSMCControl = 2
                                    
                                    */
                                   /* const void* */ in,          // In
                                   /* size_t      */ sizeof(*in), // In
                                   
                                   /* void*       */ out,         // Out
                                   /* size_t*     */ &out_size);  // In/Out
    
    return(r0);
}

kern_return_t SMC_key_getinfo(io_connect_t conn, char *keyname,SMC_key_val_t *keyval )
{
    smc_io_data_t in;
    smc_io_data_t out;
    kern_return_t r0;
    
    r0=0;
    
    bzero(&in, sizeof(in));
    bzero(&out,sizeof(out));
    in.cmd = kSMCGetKeyInfo;
    htosmclstr((char *)&in.key, keyname); // turn key into SMC byte order stored in integer
    
    r0 = smc_io(conn, &in, &out);
    if (r0 == kIOReturnSuccess) {
        if (out.io_sts == 0 ) {
            // we have the key info in out
            // UInt32          vsize;   // 2
            // SMC_type_t      vtype;   // fp88
            // SMC_keynam_t    vkey;    // PC1C
            // SMC_key_data_t  vbytes;  // 08 44
            keyval->vsize =  out.ksize; // TODO: probably need a endian swap
            htosmclstr(keyval->vtype, out.ktype); //need to endian swap results
            memcpy(keyval->vkey, keyname, 4);
            memcpy(keyval->vbytes, out.bytes,sizeof(keyval->vbytes));
        } else {
            r0 = out.io_sts;
        }
    }
    return(r0);
}

kern_return_t SMC_key_value_by_index_get(io_connect_t conn, UInt32 keyidx, SMC_key_val_t *keyval )
{
    smc_io_data_t in;
    smc_io_data_t out;
    kern_return_t r0;
    
    r0=0;
    
    bzero(&in, sizeof(in));
    bzero(&out,sizeof(out));
    bzero(keyval, sizeof(SMC_key_val_t));
    
    
    in.cmd = kSMCGetKeyFromIndex;
    in.p1_lw = keyidx;
    //htosmclstr((char *)&in.key, keyname); // turn key into SMC byte order stored in integer
    
    r0 = smc_io(conn, &in, &out);
    if (r0 == kIOReturnSuccess) {
        if (out.io_sts == 0) {
            // we have the key info in out
            // UInt32          vsize;   // 2
            // SMC_type_t      vtype;   // fp88
            // SMC_keynam_t    vkey;    // PC1C
            // SMC_key_data_t  vbytes;  // 08 44
            keyval->vsize =  out.ksize; // TODO: probably need a endian swap
            htosmclstr(keyval->vtype, out.ktype); //need to endian swap results
            htosmclstr(keyval->vkey, out.key); //need to endian swap results
            memcpy(keyval->vbytes, out.bytes,sizeof(keyval->vbytes));
            r0 = SMC_key_value_get(conn, keyval->vkey, keyval);
            
        } else {
            r0 = out.io_sts;
        }
    }
    return(r0);
}

//////////////////////////////////////////////////////////////////////////
kern_return_t SMC_key_write(io_connect_t conn, char *keyname, short val, SMC_key_val_t *keyval)
//////////////////////////////////////////////////////////////////////////
{
    smc_io_data_t in;
    smc_io_data_t out;
    kern_return_t r0;
    
    bzero(&in, sizeof(in));
    bzero(&out,sizeof(out));
    
    r0 = SMC_key_getinfo(conn, keyname, keyval); // find that the key name is valid
                                                 // also gets the defaults
    if (r0 == kIOReturnSuccess) {
        keyval->smc_defaults = smc_lookup_desc(keyval);
        if (keyval->smc_defaults->d_attrib & KA_W) {    // Only write key if the key attribute allows
            htosmclstr(in.key  , keyval->vkey);         // convert key name to SMC order
            htosmclstr(in.ktype, keyval->vtype);        // convert type to SMC order
            in.ksize = keyval->vsize;                   // convert to SMC byteorder
            in.cmd = kSMCWriteKey;
            in.bytes[0] = val >> 8;
            in.bytes[1] = val & 0x0F;
            
            r0 = smc_io(conn, &in, &out);
            if (r0 == kIOReturnSuccess) {
                if (out.io_sts == 0 ) {
                    // we have the key info in out
                    //memcpy(keyval->vbytes, out.bytes,sizeof(keyval->vbytes));
                } else {
                    r0 = out.io_sts;
                }
            }
        } else {
            r0 = EACCES; // Read only key cant be written
        }
    }
    
    return(r0);
}

///////////////////////////////////////////////////////////////////////////////
kern_return_t SMC_key_value_get(io_connect_t conn, char *keyname ,SMC_key_val_t *keyval )
///////////////////////////////////////////////////////////////////////////////
{
    smc_io_data_t in;
    smc_io_data_t out;
    kern_return_t r0;
    
    bzero(&in, sizeof(in));
    bzero(&out,sizeof(out));
    
    r0 = SMC_key_getinfo(conn, keyname, keyval);
    if (r0 == kIOReturnSuccess) {
        keyval->smc_defaults = smc_lookup_desc(keyval);
        if (keyval->smc_defaults->d_attrib & KA_R) {  // Only read key if the key attribute allows
            htosmclstr(in.key  , keyval->vkey);
            htosmclstr(in.ktype, keyval->vtype);
            in.ksize = keyval->vsize;    // convert to SMC byteorder
            in.cmd = kSMCReadKey;
            r0 = smc_io(conn, &in, &out);
            if (r0 == kIOReturnSuccess) {
                if (out.io_sts == 0 ) {
                    // we have the key info in out
                    memcpy(keyval->vbytes, out.bytes,sizeof(keyval->vbytes));
                } else {
                    r0 = out.io_sts;
                }
            }
        } else {
            r0 = EACCES; // Write only key cant be read
        }
    }
    
    return(r0);
}


double smc_key_read_numeric(io_connect_t conn, char *key)
{
    double          rval;
    kern_return_t   r0;
    SMC_key_val_t   keyvalue;
    
    r0 = SMC_key_value_get(conn, key,  &keyvalue);
    if (r0 == kIOReturnSuccess) {
        rval = numeric2float(keyvalue.vtype, keyvalue.vbytes);
    } else {
        rval = nan("-4");
    }
    return(rval);
}

double report_temp(io_connect_t conn, char *key, char *desc)
{
    
    double   temp;
    
    temp = smc_key_read_numeric(conn, key);
    
    //reportfd_fldidx();
    
    reportfd(F_DEBUG, "[%s]", key);
    reportfd(F_ALWAYS|F_NL,desc, temp);
    
    return(temp);
}

void report_fans(io_connect_t conn)
{
    int numfans;
    int fan;
    int fan_mode;
    
    fan_mode = (int) smc_key_read_numeric(conn, "FS!"); // 0=auto !=0 fixed
    numfans = (int) smc_key_read_numeric(conn, "FNum");
    reportfd(0, "# Found %d fans on this system\n", numfans);
    for (fan=0;fan < numfans;fan++) {
        report_fan(conn, fan);
        newline();
    }
    reportfd(0, "Fan Control mode: %s\n", fan_mode?"Auto":"Fixed");
    
}

void report_fan(io_connect_t conn, int fan)
{
    double          rpm_act, rpm_min, rpm_max, rpm_safe, rpm_trgt;
    char            *desc;
    SMC_key_val_t   desc_kval;
    kern_return_t   r0;
    
    
    char key_act[5]  = { "F0Ac" };
    char key_min[5]  = { "F0Mn" };
    char key_max[5]  = { "F0Mx" };
    char key_safe[5] = { "F0Sf" };
    char key_trgt[5] = { "F0Tg" };
    char key_desc[5] = { "F0ID" };
    struct {
        char    ob;
        char    key[15];
    } keystr;
    char    eolc;
    
    bzero(&keystr, sizeof(keystr));
    if (flag_test(F_DEBUG)) {
        keystr.ob = '[';
    }
    
    if (flag_test(F_NL)) {
        eolc = '\n';
    } else {
        eolc = ':';
    }
    
    if (fan < 0 || fan > 9 ) {
        reportfd(F_NOISY, "# Illegal fan index must be 0-9: %d\n", fan);
    	return;
    }
    key_act[1]  = '0'+fan;
    key_min[1]  = '0'+fan;
    key_max[1]  = '0'+fan;
    key_safe[1] = '0'+fan;
    key_trgt[1] = '0'+fan;
    key_desc[1] = '0'+fan;
    
    rpm_act  = smc_key_read_numeric(conn, key_act);
    rpm_min  = smc_key_read_numeric(conn, key_min);
    rpm_max  = smc_key_read_numeric(conn, key_max);
    rpm_safe = smc_key_read_numeric(conn, key_safe);
    rpm_trgt = smc_key_read_numeric(conn, key_trgt);
    r0       = SMC_key_value_get(   conn, key_desc,  &desc_kval);
    if (r0 != kIOReturnSuccess) {
        return;
    };
    desc = describe_fan(&desc_kval);
    if (desc) {
        sprintf((char *) keystr.key, "%s]", key_desc);
        reportfd(F_ALWAYS, "%s Fan#%d-%s", (char *) &keystr, fan, desc );
        free(desc);
    }
    
    sprintf((char *) keystr.key, "%s]", key_act);
    reportfd(F_INDEX,"%sFan#%d [act] : %g %c" ,(char *) &keystr, fan, rpm_act, eolc);
    
    sprintf((char *) keystr.key, "%s]", key_min);
    reportfd(F_INDEX,"%sFan#%d [min] : %g %c" , (char *) &keystr, fan, rpm_min, eolc);
    
    sprintf((char *) keystr.key, "%s]", key_max);
    reportfd(F_INDEX,"%sFan#%d [max] : %g %c" , (char *) &keystr, fan, rpm_max, eolc);
    
    sprintf((char *) keystr.key, "%s]", key_safe);
    reportfd(F_INDEX,"%sFan#%d [safe]: %g %c" , (char *) &keystr, fan, rpm_safe, eolc);
    
    sprintf((char *) keystr.key, "%s]", key_trgt);
    reportfd(F_INDEX,"%sFan#%d [trgt]: %g %c" , (char *) &keystr, fan, rpm_trgt, eolc);
    
}

int smc_display_allkeys(io_connect_t conn, char *model)
{
    UInt32          numkeys;
    UInt32          keyidx;
    SMC_key_val_t   keyval;
    
    numkeys = (int) smc_key_read_numeric(conn, "#KEY");
    
    
    reportfd(F_NOISY, "# Found %d keys on this system: %s\n", numkeys, model);
    
    for (keyidx=0;keyidx < numkeys;keyidx++) {
        SMC_key_value_by_index_get(conn, keyidx, &keyval); // errors esp WO are ignored
        smc_keyval_display(&keyval);
    }
    
    return(EINVAL);
    
}


kern_return_t smc_fan_set(io_connect_t conn, char *keyname, int rpm)
{
    short           val;
    kern_return_t   rval;
    SMC_key_val_t   key;
    
    // TODO: print value and check conversion is correct
    val  = rpm << 2;  // value is in fpe2 format so just shift left 2 int RPM
    
    rval = SMC_key_write(conn, keyname, val, &key);
    return(rval);
}


int smc_key_write(io_connect_t  conn, char *key, char *value)
{
    int rval;
    int rpm;
    
    rval  = -1;
    // TODO: obviously ;(
    if ((memcmp(key, "F0M", 3)== 0) ||
        (memcmp(key, "F1M", 3)== 0) ||
        (memcmp(key, "F0A", 3)== 0) ||
        (memcmp(key, "F1A", 3)== 0)  ){
        rpm = atoi(value);
        rval = smc_fan_set(conn, key, rpm);
    }
    return(rval);
}


int smc_key_display(io_connect_t conn, char *keyptr)
{
    kern_return_t   r0;
    SMC_key_val_t   keyvalue;
    char            key[5]; // must be space padded eg. "SIP "
    
    snprintf(key,sizeof(key), "%-4.4s", keyptr);
    r0 = SMC_key_value_get(conn, key,  &keyvalue);
    if (r0 != kIOReturnSuccess) {
        return(r0);
    }
    return (smc_keyval_display(&keyvalue));
}

int smc_keyval_display(SMC_key_val_t *keyvalue)
{
    double          fp;
    unsigned short  release;
    ssize_t         idx;
    
    reportfd(F_DESCRIBE, "%s|", keyvalue->smc_defaults->d_desc);
    
    
    reportfd(F_ALWAYS, "%-4.4s"    , keyvalue->vkey);
    
    if (flag_test(F_SHOWTYPE)) {
        reportfd(F_SHOWTYPE, "|[%-4.4s]",keyvalue->vtype);
        reportfd(F_SHOWSIZE, "|");
    }
    
    if (flag_test(F_SHOWSIZE)) {
        reportfd(F_SHOWSIZE, "|");
        reportfd(F_SHOWTYPE, "%lu", (unsigned long) keyvalue->vsize);
    }
    
    reportfd(F_ALWAYS, "|");
    
    if (flag_test(F_VALUES)) {
        if (flag_test(F_PRIVATE)) {
            if (memcmp(keyvalue->vkey, "B0SN", 4) == 0 ) {  // Blank out the System Serial#
                strcpy(keyvalue->vbytes, "<Private>");
                keyvalue->vsize = (SMC_keysize_t) strlen(keyvalue->vbytes);
            }
            
        }
        if (memcmp(keyvalue->vkey, "ACID", 4) == 0 ) {
            short pa_id;
            short pa_wattage;
            short pa_revision;
            short pa_family;
            unsigned int   pa_serialno;
            
            /* special case
             mark@zed> ./smc_util -tsv ACID
             ACID|[ch8*]|8|.#2.P...|( BA | 23 32 85|  50 05 10 A1 )
             ACID|[ch8*]|8|.#2.P...|( BA | 23 32 85|  50 05 10 A1 )
             0550
             AC Charger Information:
             
             Connected:        Yes
             ID:               0x0100
             Wattage (W):      85
             Revision:         0x0000
             Family:           0x00ba          0x00 keyvalue->vbytes[0]
             Serial Number:	0x00 85 32 23      0x00 keyvalue->vbytes[3,2,1]
             Charging:	No */
            
            pa_id       = 0; // TODO: NFI
            pa_revision = 0; // TODO: NFI
            pa_family   = 0;
            pa_serialno = 0;
            pa_wattage  = (keyvalue->vbytes[3] & 0xff); // BCD
            
            pa_family   |= keyvalue->vbytes[0]&0xff;
            pa_serialno = 0;
            pa_serialno = (pa_serialno<<8) | (keyvalue->vbytes[3] & 0xff);
            pa_serialno = (pa_serialno<<8) | (keyvalue->vbytes[2] & 0xff);
            pa_serialno = (pa_serialno<<8) | (keyvalue->vbytes[1] & 0xff);
            if (pa_serialno || pa_family) {
                reportfd(F_ALWAYS|F_NL, "AC PWR Adapter; Family: 0x%04x Serial Number: 0x%08x Wattage: %02X other bytes: %02x %02x %02x %02x",
                         pa_family,
                         pa_serialno,
                         pa_wattage, // BCD
                         (unsigned char) keyvalue->vbytes[4],
                         (unsigned char) keyvalue->vbytes[5],
                         (unsigned char) keyvalue->vbytes[6],
                         (unsigned char) keyvalue->vbytes[7]
                         );
            }
            else {
                reportfd(F_ALWAYS|F_NL, "AC PWR Adapter; None connected");
            }
            
            
        }
        else
            if ((keyvalue->vtype[0] == 'f' && keyvalue->vtype[1] == 'p')
               ){
                fp = numeric2float(keyvalue->vtype, keyvalue->vbytes);
                reportfd(F_ALWAYS,  "%g", fp);
                if (flag_test(F_DUMPHEX)) {
                    dump_hex(keyvalue->vsize, keyvalue->vbytes);
                }
                
                //reportfd(F_DUMPHEX|F_BINARY,")");
                //reportfd(F_ALWAYS|F_NL,"");
                
            }
            if (  (keyvalue->vtype[0] == 'f')
               && (keyvalue->vtype[1] == 'l')
               && (keyvalue->vtype[2] == 't')
               && (keyvalue->vtype[3] == ' ')
            ){
                fp = numeric2float(keyvalue->vtype, keyvalue->vbytes);
                reportfd(F_ALWAYS,  "%g", fp);
                if (flag_test(F_DUMPHEX)) {
                    assert(keyvalue->vsize == 4);
                    dump_hex(keyvalue->vsize, keyvalue->vbytes);
                }
                reportfd(F_ALWAYS|F_NL,"");
            }
            else if ((keyvalue->vtype[0] == 'u' && keyvalue->vtype[1] == 'i') ||
                       (keyvalue->vtype[0] == 's' && keyvalue->vtype[1] == 'i')) {
                fp = numeric2float(keyvalue->vtype, keyvalue->vbytes);
                if (keyvalue->vtype[0] == 's') {
                    reportfd(F_ALWAYS, "%d", (int) fp);
                }
                else {
                    reportfd(F_ALWAYS, "%u", (unsigned int) fp);
                }
                if (flag_test(F_DUMPHEX)) {
                    dump_hex(keyvalue->vsize, keyvalue->vbytes);
                }
                reportfd(F_ALWAYS,"");
                
            }
            else if  (memcmp(keyvalue->vtype, "ch8*", 4) == 0) {
                dump_ascii(keyvalue->vsize, keyvalue->vbytes);
                dump_hex(  keyvalue->vsize, keyvalue->vbytes);
            }
            else if  (memcmp(keyvalue->vtype, "char", 4) == 0) {
                dump_ascii( keyvalue->vsize, keyvalue->vbytes);
                dump_hex(   keyvalue->vsize, keyvalue->vbytes);
            }
            else if (memcmp(keyvalue->vtype,"{ala",4) == 0) { // ALS analog lux calculation information.
                ushort  als_m;   // slope
                short   als_b;   // Y intercept
                ushort  als_r;   // region
                als_m = readushort(&keyvalue->vbytes[0]);
                als_b = readshort( &keyvalue->vbytes[2]);
                als_r = readushort(&keyvalue->vbytes[4]);
                reportfd(F_ALWAYS|F_NL, "ALS LUX; slope: %u  y-intercept: %d region: %u ", als_m, als_b, als_r);
                
                /* {ala	\0\0\0\0		 K_DESC_STR
                 
                 struct ALSLuxLine {
                 UInt16 ui16ALSM;         // Slope of line.
                 Int16  i16ALSB;          // Y-Intercept of line.
                 UInt16 ui16ALSR;         // Region.
                 } */
                
            }
            else if (memcmp(keyvalue->vtype,"{alc",4) == 0) { // ALSConfig structure contains global ALS configuration and tuning info.
                ushort ALSI2CTime   = readushort(&keyvalue->vbytes[0]);   // Int interval (ms) for ALS I2C task
                ushort ALSADCTime   = readushort(&keyvalue->vbytes[2]);   // Int interval (ms) for ALS ADC ISR.
                ushort LMax         = readushort(&keyvalue->vbytes[4]);   // Maximum cd/m^2 for SIL.
                ushort LMin         = readushort(&keyvalue->vbytes[6]);   // Minimum cd/m^2 for SIL.
                ushort ELow         = readushort(&keyvalue->vbytes[8]);   // Low room illum threshold (lux).
                ushort EHigh        = readushort(&keyvalue->vbytes[10]);  // High room illum threshold (lux).
                ushort Reflect      = readushort(&keyvalue->vbytes[12]);  // Bezel reflection coefficient.
                u_char ALSSensors   = keyvalue->vbytes[14];               // Actual number of ALS sensors in system.
                u_char LidDelay     = keyvalue->vbytes[15];               // Delay after lid opens (in tenths of seconds)
                
                reportfd(F_ALWAYS|F_NL, "ALSConfig; I2Ctsktim: %ums ADCtsktim: %ums LMax: %u LMin: %u ELow: %u EHigh: %u Reflect: %u Sensor#: %2u LidDly: %2.1fs %s",
                        ALSI2CTime,
                        ALSADCTime,
                        LMax, LMin,
                        ELow, EHigh,
                        Reflect,
                        ALSSensors,
                        (LidDelay/10.0),
                         "");
                
            }
            else if (memcmp(keyvalue->vtype,"{ali",4) == 0) { // ALSSensor structure contains sensor-specific information for this system
                
                /*
                 ALI0|[{ali]|4|....|(04 00 0F 00 )
                 ALI1|[{ali]|4|.|(00 )
                 
                 {ali	\0\0\0\0		 K_DESC_STR
                 
                 enum ALSType { NoSensor, BS520, TSL2561CS, LX1973A, ISL29003 };
                 
                 struct ALSSensor {
                 enum  ALSType alstALSType;  // Type of sensor.
                 Flag  fValidWhenLidClosed;  // TRUE if no lid or if sensor works with
                 // closed lid.  FALSE otherwise.
                 Flag  fControlSIL;          // TRUE if the SIL brightness depends on
                 // this sensor's value.  FALSE otherwise.
                 }
                 */
                int alstypeidx = keyvalue->vbytes[0]&0xff;
                if (alstypeidx > 4 || alstypeidx < 0 ) {
                    alstypeidx = 0;
                }
                reportfd(F_ALWAYS|F_NL, "ALSSensor; type: %s sensorvalid: %s, SIL using this sensor: %s %02x ",
                        get_ALSType_str(alstypeidx),
                        keyvalue->vbytes[1]&0xff?"Yes":"No ",
                        keyvalue->vbytes[2]&0xff?"Yes":"No ",
                        keyvalue->vbytes[3]&0xff);
                
            }
            else if (memcmp(keyvalue->vtype,"{alr",4) == 0) {  //  ALS analog lux temperature coefficients.
                double ALSTempBase  = numeric2float("fpg0", &keyvalue->vbytes[0]);   // Temperature baseline (deg C, FP16.0)
                double ALSTempCoefV = numeric2float("fpc4", &keyvalue->vbytes[2]);   // Temperature coeff (ADC Counts/deg C, FP12.4
                double ALSTempInflV = numeric2float("fpg0", &keyvalue->vbytes[4]);   // Thermal compensation inflection point voltage (ADCCounts, FP16.0)
                double  ALSTempLow  = numeric2float("fpg0",&keyvalue->vbytes[6]);   // Low temperature boundary (deg C, FP16.0)
                double  ALSTempHigh = numeric2float("fpg0",&keyvalue->vbytes[8]);   // High temperature boundary (deg C, FP16.0)
                
                reportfd(F_ALWAYS|F_NL, "ALSAnalog; TempBase: %.1fC TempCoef: %.4fV, TempInfl: %.1fV TempLow: %.1f TempHigh: %.1f ",
                        ALSTempBase,
                        ALSTempCoefV,
                        ALSTempInflV,
                        ALSTempLow,
                        ALSTempHigh);
            }
            else if (memcmp(keyvalue->vtype,"{alt",4) == 0) { // ALS analog lux calculation thresholds
                ushort  ALSThrshLow;   // ADC threshold while in low gain
                ushort  ALSThrshHigh;  // ADC threshold while in high gain
                
                ALSThrshLow  = readushort(&keyvalue->vbytes[0]);
                ALSThrshHigh = readushort(&keyvalue->vbytes[2]);
                reportfd(F_ALWAYS|F_NL, "ALS Anallux Thrsh; Low: %u  High: %u ", ALSThrshLow, ALSThrshHigh);
                
            }
            else if (memcmp(keyvalue->vtype,"{alv",4) == 0) { // ALSValue structure contains latest ambient light info from x sensor
                                                                // ALV0|[{alv]|10|..........|(01 01 00 9C 00 1B 00 16 18 A4 )
                                                                // ALV1|[{alv]|10|...|(00 01 00 )
                ushort  fValid    = keyvalue->vbytes[0]&0xff;   // If TRUE, data in this struct is valid
                ushort  fHighGain = keyvalue->vbytes[1]&0xff;   // If TRUE, Chan0/1 are high-gain
                                                                // readings.  If FALSE, Chan0/1 are low-gain readings
                ushort  Chan0     = readushort(&keyvalue->vbytes[2]); // I2C channel 0 data or analog(ADC) data.
                ushort  Chan1     = readushort(&keyvalue->vbytes[4]); // I2C channel 1 data.
                double  RoomLux;
                char    RoomLuxStr[64];
                
                if (keyvalue->vsize > 6 ) {
                    RoomLux   = numeric2float("fpie", &keyvalue->vbytes[6]); // FP18.14
                    snprintf(RoomLuxStr, sizeof(RoomLuxStr), "RoomLux: %6.5f", RoomLux);
                }
                else {
                    RoomLux   = 0.0;
                    RoomLuxStr[0] = '\0';
                }
                reportfd(F_ALWAYS|F_NL, "ALSValue; Valid: %s  HighGain: %s Chan0: %u Chan1: %u %s ",
                        fValid?"Yes":"No ",
                        fHighGain?"Yes":"No ",
                        Chan0, Chan1,
                        RoomLuxStr);
            }
            else if (memcmp(keyvalue->vtype,"{fds",4) == 0) { // Fan Description
                reportfd(F_ALWAYS|F_NL, "type: %s Zone: %d loc: %s - %s", fan_type(keyvalue->vbytes[0]), keyvalue->vbytes[1], fan_loc(keyvalue->vbytes[2]), &keyvalue->vbytes[4]);
                
                /*
                 {fds	\0\0\0\0		 K_DESC_STR
                 Fan Diag description
                 typedef struct fanTypeDescStruct {
                 FanType       type;
                 UInt8         ui8Zone;
                 LocationType  location;
                 UChar         rsvd;   // padding to get us to 16 bytes
                 char          strFunction[DIAG_FUNCTION_STR_LEN];
                 } FanTypeDescStruct;
                 
                 
                 FAN constants
                 
                    +---+
                  z/   /|
                  /   / |
                 +---+  |
                 |   |  +
                y|   | /
                 |   |/
                 +---+
                 x
                 
                 typedef enum { LEFT_LOWER_FRONT, CENTER_LOWER_FRONT, RIGHT_LOWER_FRONT,
                 LEFT_MID_FRONT,   CENTER_MID_FRONT,   RIGHT_MID_FRONT,
                 LEFT_UPPER_FRONT, CENTER_UPPER_FRONT, RIGHT_UPPER_FRONT,
                 LEFT_LOWER_REAR,  CENTER_LOWER_REAR,  RIGHT_LOWER_REAR,
                 LEFT_MID_REAR,    CENTER_MID_REAR,    RIGHT_MID_REAR,
                 LEFT_UPPER_REAR,  CENTER_UPPER_REAR,  RIGHT_UPPER_REAR } LocationType;
                 
                 typedef enum { FAN_PWM_TACH, FAN_RPM, PUMP_PWM, PUMP_RPM, FAN_PWM_NOTACH, EMPTY_PLACEHOLDER } FanType;
                 */
            }
            else if (memcmp(keyvalue->vtype,"{lim",4) == 0) { // Plimits group is 3 UInt8  KPRIV_DESC_STR
                reportfd(F_ALWAYS|F_NL, "ProcLimits; CPU: %u GPU: %u MEM: %u ",  // MSB , middle, LSB
                        keyvalue->vbytes[0]&0xff,
                        keyvalue->vbytes[1]&0xff,
                        keyvalue->vbytes[2]&0xff);
                
            }
            else if (memcmp(keyvalue->vtype,"{lsc",4) == 0) { // K_DESC_STR LmsConfig structure provides overall system-specific config info for the SIL.
                                                                // LSCF|[{lsc]|10|......... |(00 C8 01 90 80 00 02 02 00 20 )
                ushort modvBrightnessBreatheMin;     // Breathe dwell PWM setting
                ushort modvMaxChangePerTick;         // Max PWM change per 1/152 sec
                ushort ScaleConstant;                // Scale constant (1.15 fixed-point representation) if not using ALS or TOD scaling
                u_char lmsmScaleMode;                // Scale by ALS, TOD, or constant
                u_char RampDuration;                 // Ramp length (equals 152 * ramp time in seconds)
                u_char fPowerSwitchOverridesSIL;     // TRUE if pressing the power switch should force the SIL to full brightness
                u_char MinTicksToTarget;             // Slow the slew rate so that it takes at least this many ticks to reach the target from the prev PWM value.
                
                const char *scmode[] = {
                    "kLmsScaleALS",        // Use ALS autoscale
                    "kLmsScaleTOD",        // Use TOD autoscale
                    "kLmsScaleConst"       // Scale only by a constant
                };
                
                modvBrightnessBreatheMin = readushort(&keyvalue->vbytes[0]);
                modvMaxChangePerTick     = readushort(&keyvalue->vbytes[2]);
                ScaleConstant            = readushort(&keyvalue->vbytes[4]);
                lmsmScaleMode            = keyvalue->vbytes[6]&0xff;
                RampDuration             = keyvalue->vbytes[7]&0xff;
                fPowerSwitchOverridesSIL = keyvalue->vbytes[8]&0xff;
                MinTicksToTarget         = keyvalue->vbytes[9]&0xff;
                
                reportfd(F_ALWAYS|F_NL,  "LmsConfig; BrightnessBreatheMin: %u MaxChangePerTick: %u (1/152 sec) ScaleConst: %u ScaleMode: %s RampDuration: %u PwrSwchOvrSIL: %u MinTicks2Trgt: %u ",
                        modvBrightnessBreatheMin,
                        modvMaxChangePerTick,
                        ScaleConstant,
                        scmode[lmsmScaleMode],
                        RampDuration,
                        fPowerSwitchOverridesSIL,
                        MinTicksToTarget);
                
                /*
                 
                 
                 {lsd	\0\0\0\0		 K_DESC_STR
                 LmsDwell structures provide dwell fade-up/down configuration
                 struct LmsDwell {
                 UInt16 ui16MidToStartRatio; // Mid-step size / start-step  size
                 UInt16 ui16MidToEndRatio;   // Mid-step size / end-step    size
                 UInt16 ui16StartTicks;      // # of ticks using start-step size
                 UInt16 ui16EndTicks;        // # of ticks using end-step   size
                 }
                 
                 {lsf	\0\0\0\0		 K_DESC_STR
                 LmsFlare structures provide flare config for non-breathing fade-up/down
                 See "{pwm" for details on PWMValue
                 
                 struct LmsFlare {
                 PWMValue modvFlareCeiling;  // Flare algorithm is active below this value.
                 PWMValue modvMinChange;     // Minimum rate of change while flaring.
                 UInt16   ui16FlareAdjust;   // Smaller value causes stronger flare as
                 }                              //   PWM value descends below modvFlareCeiling.
                 
                 {lsm	\0\0\0\0		 K_DESC_STR
                 LmsScaleMode enum
                 enum LmsScaleMode { kLmsScaleALS,        // Use ALS autoscale
                 kLmsScaleTOD,        // Use TOD autoscale
                 kLmsScaleConst       // Scale only by a constant
                 }
                 
                 {lso	\0\0\0\0		 K_DESC_STR
                 LmsOverrideBehavior structure provides a means to override the SIL's
                 behavior.
                 See "{lss" for details on LmsSelect
                 
                 struct LmsOverrideBehavior {
                 LmsSelect lmssTargetBehavior;  // Enumerated SIL behavior
                 Flag fRamp;                    // Set to 1 (LMS_RAMP) for a slew-rate
                 //   controlled transition.  Set to 0
                 //   (LMS_NO_RAMP) for a step change.
                 }
                 
                 {lss	\0\0\0\0		 K_DESC_STR
                 LmsSelect behavior enum
                 enum LmsSelect { kLmsOff,              // SIL off
                 kLmsOn,               // SIL on,        autoscale OK
                 kLmsBreathe,          // SIL breathing, autoscale OK
                 kLmsBrightNoScale     // SIL on bright, no autoscale
                 //   (for power switch override)
                 }
                 
                 {msp	\0\0\0\0		 K_DESC_STR
                 SSMPowerState typedef
                 enum SSMPowerState { SSM_POWER_STATE_S0     = 0,
                 SSM_POWER_STATE_S3     = 1,
                 SSM_POWER_STATE_S4     = 2,
                 SSM_POWER_STATE_S5     = 3,
                 SSM_POWER_STATE_G3_AC  = 4,
                 SSM_POWER_STATE_G3_HOT = 5,
                 SSM_POWER_STATE_QUERY  = 6,
                 }
                 
                 {mss	\0\0\0\0		 K_DESC_STR
                 SSMState typedef
                 enum SSMState { SSM_S0_DISP_WAKE        = 0,
                 SSM_S0_DISP_SLEEP       = 1,
                 SSM_G3_HOT              = 2,
                 SSM_S3_SLEEP            = 3,
                 SSM_S4_HIBER            = 4,
                 SSM_S5_OFF              = 5,
                 SSM_S0_ASP_WAIT         = 6,
                 SSM_S0_IMVP_WAIT        = 7,
                 SSM_S0_EARLY_DISP_SLEEP = 8,
                 SSM_S0_EARLY_DISP_WAKE  = 9,
                 SSM_S3_EARLY            = 10,
                 SSM_S4_EARLY            = 11,
                 SSM_QUERY               = 12,
                 SSM_ICH_RST             = 13,
                 SSM_G2_BATTERY_DEAD     = 14,
                 SSM_G2_POWER_WAIT       = 15,
                 SSM_G2_RESET_WAIT       = 16,
                 SSM_G3_AC               = 17,
                 SSM_G2_ACPWR_WAIT       = 18,
                 SSM_G2_ACRST_WAIT       = 19
                 }
                 
                 {pwm	\0\0\0\0		 K_DESC_STR
                 PWMValue typedef
                 typedef UInt16 PWMValue;
                 0xFFFF is full-on, 0x0 is full-off.
                 */
                
                
            }
            else if (memcmp(keyvalue->vtype, "flag", 4) == 0) {
                reportfd(F_ALWAYS|F_NL, "%03o",(unsigned char) keyvalue->vbytes[0]);
                
            }
            else if (memcmp(keyvalue->vtype, "hex_", 4) == 0) {
                // dump_ascii(params, keyvalue->vsize, keyvalue->vbytes);
                dump_hex(keyvalue->vsize, keyvalue->vbytes);
                
            }
            else if (memcmp(keyvalue->vtype, "{rev", 4) == 0) {
                release = (short) (keyvalue->vbytes[4]<<8) | keyvalue->vbytes[5];
                reportfd(F_ALWAYS|F_NL, "Version: %x.%x%x%x",
                        (unsigned char) keyvalue->vbytes[0],
                        (unsigned char) keyvalue->vbytes[1],
                        (unsigned char) keyvalue->vbytes[2], release);
                
            }
            else {
                dump_ascii(keyvalue->vsize, keyvalue->vbytes);
                dump_hex(  keyvalue->vsize, keyvalue->vbytes);
            }
    }
    else {
        reportfd(F_ALWAYS, "\n");
    }
    return(0);
}

short   readshort(char *sp)
{
    short rval;
    
    rval = (sp[0]&0xff) << 8 | (sp[1]&0xff);
    return (rval);
    
}

ushort  readushort(char *sp)
{
    ushort rval;
    
    rval = (sp[0]&0xff) << 8 | (sp[1]&0xff);
    return (rval);
}

int dump_hex(int size, char *buf)
{
    int idx;
    int outbytes;
    int r0;
    
    outbytes = 0;
    r0 = reportfd(F_ALWAYS, "|(");
    if (r0 >= 0) {
        outbytes = 2;
        // F_BYTEORDER
        if (flag_test(F_BYTEORDER)) {
            for (idx=size-1;idx >=0;idx--) {
                if (dump_hex_byte(size, buf, idx, -1) <= 0 ) {
                    break;
                }
            }
        }
        else {
            for (idx=0;idx< size;idx++) {
                if (dump_hex_byte(size, buf, idx, 1) <= 0 ) {
                    break;
                }
            }
        }
        
        if (r0 >= 0) {
            r0 = reportfd(F_DUMPHEX, ") ");
            if (r0 >= 0 ) {
                outbytes += r0;
            } else {
                outbytes = r0;
            }
        }
    }
    else {
        outbytes = r0;
    }
    
    if (flag_test(F_BINARY)) {
        if (flag_test(F_BYTEORDER)) {
            outbytes += dump_binary_h2l(size, buf);
            outbytes += dump_binary_l2h(size, buf);
        }
        else {
            outbytes += dump_binary_l2h(size, buf);
            outbytes += dump_binary_h2l(size, buf);
        }
    }
    r0 = reportfd(F_DUMPHEX|F_NL, "");
    
    return (outbytes);
}

int dump_hex_byte(int size, char *buf, int idx, int order)
{
    int r0;

    r0 = reportfd(F_DUMPHEX, "%02X ", (unsigned char) buf[idx]);
    if (r0>=0) {
        if (isnull2end(size-idx, &buf[idx])) {
            return(0); // 0 should be exit the calls loop ;
        }
    }

    return (r0);
}

int dump_binary_l2h(int size, char *buf)
{
    int idx, bidx;
    int outbytes;
    int r0;
    int bit, byte;
    
    outbytes = 0;
    r0 = reportfd(F_ALWAYS, "|(");
    if (r0 >= 0) {
        outbytes = 2;
        
        for (idx=0;idx< size;idx++) {
            byte = buf[idx];
            for (bidx = 0; bidx < 8; bidx++) {
                bit = (byte&1)?1:0;
                byte >>= 1;
                r0 = reportfd(F_BINARY, "%d", bit);
                
                if (r0>=0) {
                    outbytes += r0;
                } else {
                    outbytes = r0;
                    break;   // escape this loop there must have been an error
                }
            }
        }
        
        if (r0 >= 0) {
            r0 = reportfd(F_DUMPHEX|F_NL, ")");
            if (r0 >= 0 ) {
                outbytes += r0;
            }
            else {
                outbytes = r0;
            }
        }
    }
    else {
        outbytes = r0;
    }
    return (outbytes);
}


int dump_binary_h2l(int size, char *buf)
{
    int idx, bidx;
    int outbytes;
    int r0;
    unsigned int bit;
    unsigned char byte;
    
    outbytes = 0;
    r0 = reportfd(F_ALWAYS, "|(");
    if (r0 >= 0) {
        outbytes = 2;
        
        for (idx=size-1;idx>=0;idx--) {
            byte = (unsigned char) buf[idx];
            for (bidx = 0; bidx < 8; bidx++) {
                bit = (byte&0x80)?1:0;
                byte <<= 1;
                r0 = reportfd(F_BINARY, "%d", bit);
                
                if (r0>=0) {
                    outbytes += r0;
                } else {
                    outbytes = r0;
                    break;   // escape this loop there must have been an error
                }
            }
        }
        
        if (r0 >= 0) {
            r0 = reportfd(F_DUMPHEX|F_NL, ")");
            if (r0 >= 0 ) {
                outbytes += r0;
            }
            else {
                outbytes = r0;
            }
        }
    }
    else {
        outbytes = r0;
    }
    return (outbytes);
}

int isnull2end(int len, char *buf)
{ // return true if the rest of buf for len bytes is all 0's
    int allnuls = 1;
    int idx;
    
    for (idx=0;idx<len;idx++) {
        if (buf[idx]) {
            allnuls = 0;
            break;
        }
    }
    return(allnuls);
}

int dump_ascii(int size, char *buf)
{
    int idx;
    int outbytes;
    int r0;
    int c;
    
    outbytes = 0;
    
    for (idx=0;idx < size;idx++) {
        c = buf[idx];
        if (isprint(c)) {
            r0 = reportc(c);
        } else {
            r0 = reportc('.');
        }
        if (r0>=0) {
            outbytes++;
        } else {
            outbytes = r0;
            break;
        }
        if (isnull2end(size-idx, &buf[idx])) {
            break;
        }
    }
    return (outbytes);
}


/////////////////////////////////////////////
char *describe_fan(SMC_key_val_t   *keyvalue)
/////////////////////////////////////////////
{
    int len;
    char *dbuf;
    len = asprintf(&dbuf, "type: %s Zone: %d loc: %s - %s\n",
                   fan_type(keyvalue->vbytes[0]),
                   keyvalue->vbytes[1],
                   fan_loc(keyvalue->vbytes[2]),
                   &keyvalue->vbytes[4]);
    
    if (len == -1 ) {
        if (flag_test(F_NOISY)) {
            fprintf(stderr, "# Error allocating fan description\n");
        }
        
        exit(ENOMEM);
    }
    return(dbuf);
}

const char *fan_loc(int idx)
{
	const char *fan_location[] = {
        "LEFT_LOWER_FRONT", "CENTER_LOWER_FRONT", "RIGHT_LOWER_FRONT",
        "LEFT_MID_FRONT",   "CENTER_MID_FRONT",   "RIGHT_MID_FRONT",
        "LEFT_UPPER_FRONT", "CENTER_UPPER_FRONT", "RIGHT_UPPER_FRONT",
        "LEFT_LOWER_REAR",  "CENTER_LOWER_REAR",  "RIGHT_LOWER_REAR",
        "LEFT_MID_REAR",    "CENTER_MID_REAR",    "RIGHT_MID_REAR",
        "LEFT_UPPER_REAR",  "CENTER_UPPER_REAR",  "RIGHT_UPPER_REAR" };
    
	if (idx >= 0 && idx < (sizeof(fan_location)/sizeof( char *) )) {
		return(fan_location[idx]);
	} else {
		return("UNK_LOC");
	}
}

const char *fan_type(int idx)
{
	const char *fan_tp[] = {
        "FAN_PWM_TACH","FAN_RPM","PUMP_PWM","PUMP_RPM","FAN_PWM_NOTACH","EMPTY_PLACEHOLDER" };
	if (idx >= 0 && idx < (sizeof(fan_tp)/sizeof( char *))) {
		return(fan_tp[idx]);
	} else {
		return("UNK_TYPE");
	}
}

int smc_key_read(io_connect_t  conn, char *key)
{
    
    // TODO: ??
    return(EINVAL);
    
}

char *get_sysmodel_dynamic(void)
{
    /*
     hw.machine = x86_64
     hw.model = MacBookPro5,2
     */
    int         mib[4];
    char        buf[64];
    size_t      len = sizeof(buf);
    char        *model;
    
    mib[0] = CTL_HW;
    mib[1] = HW_MODEL;
    
    bzero(buf, len);
    
    if (!sysctl(mib, 2, &buf, &len, NULL, 0)) {
        model = (char *) malloc(len+1);
        if (model) {
            strcpy(model, buf);
        }
    } else {
        model=NULL;
    }
    return(model);
}
