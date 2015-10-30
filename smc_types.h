//
//  smc_types.h
//  smc_utils
//
//  Created by Mark Garrett on 13/12/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_smc_types_h
#define smc_utils_smc_types_h
#include "smc_utils.h"
#include <IOKit/IOKitLib.h>
#include <stdio.h>


typedef UInt16 PWMValue; // "{pwm"  0xFFFF is full-on, 0x0 is full-off.
typedef enum                  {  NoSensor ,  BS520 ,  TSL2561CS ,  LX1973A ,  ISL29003  , ALSType_str_max } ALSType_et;
#ifdef __ALSType_str__
const   char *ALSType_str[] = { "NoSensor", "BS520", "TSL2561CS", "LX1973A", "ISL29003", "VALOUTOFRNG" };
#else
extern const char **ALSType_str;
#endif
const char *get_ALSType_str( int idx);

typedef UInt8       Flag;
typedef enum {  LEFT_LOWER_FRONT, CENTER_LOWER_FRONT, RIGHT_LOWER_FRONT,
                LEFT_MID_FRONT,   CENTER_MID_FRONT,   RIGHT_MID_FRONT,
                LEFT_UPPER_FRONT, CENTER_UPPER_FRONT, RIGHT_UPPER_FRONT,
                LEFT_LOWER_REAR,  CENTER_LOWER_REAR,  RIGHT_LOWER_REAR,
                LEFT_MID_REAR,    CENTER_MID_REAR,    RIGHT_MID_REAR,
                LEFT_UPPER_REAR,  CENTER_UPPER_REAR,  RIGHT_UPPER_REAR } LocationType_et;

typedef enum { FAN_PWM_TACH, FAN_RPM, PUMP_PWM, PUMP_RPM, FAN_PWM_NOTACH, EMPTY_PLACEHOLDER } FanType_et; 

typedef enum  { 
    kLmsScaleALS,   // Use ALS autoscale
    kLmsScaleTOD,   // Use TOD autoscale
    kLmsScaleConst  // Scale only by a constant
} LmsScaleMode_et;   // {lsm 


typedef enum LmsSelect {
        kLmsOff,              // SIL off
        kLmsOn,               // SIL on,        autoscale OK
        kLmsBreathe,          // SIL breathing, autoscale OK
        kLmsBrightNoScale     // SIL on bright, no autoscale (for power switch override)
} LmsSelect_et;

typedef enum SSMPowerState { 
    SSM_POWER_STATE_S0     = 0,
    SSM_POWER_STATE_S3     = 1,
    SSM_POWER_STATE_S4     = 2,
    SSM_POWER_STATE_S5     = 3,
    SSM_POWER_STATE_G3_AC  = 4,
    SSM_POWER_STATE_G3_HOT = 5,
    SSM_POWER_STATE_QUERY  = 6,
} SSMPowerState_et;

typedef enum SSMState { 
    SSM_S0_DISP_WAKE        = 0,
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
}   SSMState_et; 

typedef struct ALSLuxLine {
        UInt16 ALSM;         // Slope of line.
        SInt16 ALSB;         // Y-Intercept of line.
        UInt16 ALSR;         // Region.
} ala_t; // ALS analog lux calculation information.
    
        
typedef struct ALSConfig { 
        UInt16 ALSI2CTime;   // Int interval (ms) for ALS I2C task.
        UInt16 ALSADCTime;   // Int interval (ms) for ALS ADC ISR.
        UInt16 LMax;         // Maximum cd/m^2 for SIL.
        UInt16 LMin;         // Minimum cd/m^2 for SIL.
        UInt16 ELow;         // Low room illum threshold (lux).
        UInt16 EHigh;        // High room illum threshold (lux).
        UInt16 Reflect;      // Bezel reflection coefficient.
        UInt8  ALSSensors;    // Actual number of ALS sensors in system.
        UInt8  LidDelay;      // Delay after lid opens (in tenths of seconds)
        //   during which ALS readings don't affect the  SIL.
} alc_t;    // ALSConfig structure contains global ALS configuration and tuning info
        

typedef struct ALSSensor {
        ALSType_et  alstALSType;          // Type of sensor.
        Flag        fValidWhenLidClosed;  // TRUE if no lid or if sensor works with closed lid.  FALSE otherwise.
        Flag        fControlSIL;          // TRUE if the SIL brightness depends on this sensor's value.  FALSE otherwise.
} ali_t;                              // {ali	 ALSSensor structure contains sensor-specific information for this system

typedef struct  ALSTherm {
        SInt16  ALSTempBase;    // Temperature baseline (deg C, FP16.0)
        UInt16  ALSTempCoefV;   // Temperature coeff (ADC Counts/deg C, FP12.4)
        UInt16  ALSTempInflV;   // Thermal compensation inflection point voltage (ADCCounts, FP16.0)
        SInt16  ALSTempLow;     // Low temperature boundary (deg C, FP16.0)
        SInt16  ALSTempHigh;    // High temperature boundary (deg C, FP16.0)
} alr_t;                        // {alr	ALS analog lux temperature coefficients.
    
                
typedef struct  ALSLuxThrsh {
        UInt16  ALSThrshLow;    // ADC threshold while in low gain.
        UInt16  ALSThrshHigh;   // ADC threshold while in high gain.
} alt_t;                        // {alt	 ALS analog lux calculation thresholds.
                    
                    
typedef struct ALSValue {
        Flag    fValid;         // If TRUE, data in this struct is valid.
        Flag    fHighGain;      // If TRUE, ui16Chan0/1 are high-gain
                                // readings.  If FALSE, ui16Chan0/1 are low-gain readings.
        UInt16  Chan0;          // I2C channel 0 data or analog(ADC) data.
        UInt16  Chan1;          // I2C channel 1 data.
                                // The following field only exists on systems that send ALS change notifications to the OS:
        UInt32  RoomLux;        // Room illumination in lux, FP18.14.
} alv_t;                        // {alv ALSValue structure contains latest ambient light info from 1 sensor
 
// fds_t actually 16 byte's but we may as well map fandescstr to the full size of key data
#define FANDESCSTRLEN   sizeof(SMC_key_data_t)-sizeof(FanType_et)-sizeof(UInt8)-sizeof(LocationType_et)-sizeof(u_char)
typedef struct fanTypeDescStruct {
    FanType_et      type;
    UInt8           Zone;
    LocationType_et location;
    u_char          rsvd;   // padding to get us to 16 bytes
    char            fandescstr[FANDESCSTRLEN];
} fds_t;                  // {fds Fan Diag description

typedef struct {
    UInt8   cpu_limit;
    UInt8   gpu_limit;
    UInt8   mem_limit;
} lim_t;            //    {lim   

typedef struct LmsConfig {
    PWMValue        modvBrightnessBreatheMin;   // Breathe dwell PWM setting
    PWMValue        modvMaxChangePerTick;       // Max PWM change per 1/152 sec
    UInt16          ScaleConstant;              // Scale constant (1.15 fixed-point representation) if not using ALS or TOD scaling
    LmsScaleMode_et  lmsmScaleMode;              // Scale by ALS, TOD, or constant
    UInt8           RampDuration;               // Ramp length (equals 152 * ramp time in seconds)
    Flag            fPowerSwitchOverridesSIL;   // TRUE if pressing the power switch should force the SIL to full brightness
    UInt8           ui8MinTicksToTarget;        // Slow the slew rate so that
                                                //   it takes at least this many ticks to reach the target from the prev PWM value.
} lsc_t;      // {lsc LmsConfig structure provides overall system-specific config info for the SIL.

// LmsDwell structures provide dwell fade-up/down configuration
typedef struct LmsDwell {
        UInt16 MidToStartRatio; // Mid-step size / start-step  size
        UInt16 MidToEndRatio;   // Mid-step size / end-step    size
        UInt16 StartTicks;      // # of ticks using start-step size
        UInt16 EndTicks;        // # of ticks using end-step   size
}  lsd_t;                       // "{lsd"


// LmsFlare structures provide flare config for non-breathing fade-up/down
typedef struct LmsFlare {
    PWMValue modvFlareCeiling;  // Flare algorithm is active below this value.
    PWMValue modvMinChange;     // Minimum rate of change while flaring.
    UInt16   FlareAdjust;       // Smaller value causes stronger flare as
} lsf_t;                        // "{lsf"   PWM value descends below modvFlareCeiling.
        

typedef struct LmsOverrideBehavior {
    LmsSelect_et lmssTargetBehavior;  // Enumerated SIL behavior
    Flag        fRamp;               // Set to 1 (LMS_RAMP) for a slew-rate
                                 //   controlled transition.  Set to 0 (LMS_NO_RAMP) for a step change.
} lso_t;                         // {lso	 LmsOverrideBehavior structure provides a means to override the SIL's  behavior.

typedef struct {
    
} lss_t;  // {lss	LmsSelect behavior enum

typedef struct {
    SSMPowerState_et powerstate;
} msp_t;    // {msp	
          
typedef struct {
    SSMState_et  state;
} mss_t;    //  {mss	


typedef  struct {
    PWMValue     pwm;
} pwm_t ; // "{pwm"  0xFFFF is full-on, 0x0 is full-off.


ala_t   *get_ala(char *buf);
#endif
