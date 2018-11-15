//
//  smc_desc.h
//  smc_utils
//
//  Created by Mark Garrett on 01/12/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_smc_desc_h
#define smc_utils_smc_desc_h
#include "smc_desc_t.h"
#include "smc_defs.h"

#ifndef __DEF_SMS_DESC__
extern const smc_desc_t **SMC_DESC;
#else

const smc_desc_t SMC_DESC[] =  {
    {"#KEY","ui32",4,K_CONST,"Number of Keys"},
    {"$Adr","ui32",4,K_VAR_R,"Unknown"},
    {"$Num","ui8 ",1,K_VAR_R,"Unknown"},
    {"+LKS","flag",1,K_FUNC_R,"Unknown"},
    {"ACCL","ui8 ",1,K_VAR_R,"Unknown"},
    {"ACEN","ui8 ",1,K_VAR_R,"Unknown"},
    {"ACFP","flag",1,K_VAR_R,"Unknown"},
    {"ACID","ch8*",8,K_VAR_R,"AC adapter ID"},
    {"ACIN","flag",1,K_VAR_R,"Unknown"},
    {"AL! ","ui16",2,K_VAR_RW ,"Unknown"},
    {"ALA0","{ala",6,K_VAR_ATOM_RW,"ALS analog lux calculation information"},
    {"ALA1","{ala",6,K_VAR_ATOM_RW,"ALS analog lux calculation information"},
    {"ALA2","{ala",6,K_VAR_ATOM_RW,"ALS analog lux calculation information"},
    {"ALA3","{ala",6,K_VAR_ATOM_RW,"ALS analog lux calculation information"},
    {"ALA4","{ala",6,K_VAR_ATOM_RW,"ALS analog lux calculation information"},
    {"ALA5","{ala",6,K_VAR_ATOM_RW,"ALS analog lux calculation information"},
    {"ALAT","{alt",4,K_VAR_ATOM_RW,"analog lux calculation thresholds"},
    {"ALI0","{ali",4,K_CONST,"ALS Sensor 0 Info"},
    {"ALI1","{ali",4,K_CONST,"ALS Sensor 1 Info"},
    {"ALP0","ui16",4,K_VAR_R,"Unknown"},
    {"ALP1","ui16",4,K_VAR_R,"Unknown"},
    {"ALRV","ui16",2,K_CONST,"ALS/SIL version ID for the application program interface"},
    {"ALSC","{alc",16,K_VAR_ATOM_RW,"Unknown"},
    {"ALSF","fp1f",2,K_VAR_ATOM_RW,"ALS Scale Factor for SIL in 1.15 fixed-point representation"},
    {"ALSL","ui16",2,K_VAR_ATOM_RW,"Average ALS Ambient Light Reading in Lux"},
    {"ALT0","ui16",2,K_VAR_ATOM_RW,"ALS Ambient Light Sensor Temperature for sensor 0 (deg C, FP16.0)"},
    {"ALT1","ui16",2,K_VAR_ATOM_RW,"ALS Ambient Light Sensor Temperature for sensor 1 (deg C, FP16.0)"},
    {"ALTH","{alr",10,K_VAR_ATOM_RW,"ALS Ambient Light Sensor Thermal Coefficient and baseline temperature"},
    {"ALV0","{alv",10,K_VAR_ATOM_RW,"Latest ambient light reading from sensor 0"},
    {"ALV1","{alv",10,K_VAR_ATOM_RW,"Latest ambient light reading from sensor 1"},
    {"AUPO","ui8 ",1,K_VAR_ATOM_RW ,"Unknown"},
    {"B0AC","si16",2,K_VAR_R,"Unknown"},
    {"B0AP","flag",1,K_VAR_R,"Unknown"},
    {"B0AV","ui16",2,K_VAR_R,"Unknown"},
    {"B0Ad","ui16",2,K_VAR_R,"Unknown"},
    {"B0Al","ui16",2,K_VAR_R,"Unknown"},
    {"B0Am","ui8 ",1,K_VAR_R,"Unknown"},
    {"B0Ar","ui8 ",1,K_VAR_R,"Unknown"},
    {"B0As","ui8 ",1,K_VAR_R,"Unknown"},
    {"B0At","ui16",2,K_VAR_R,"Unknown"},
    {"B0Au","ui16",2,K_VAR_R,"Unknown"},
    {"B0Az","ui8 ",1,K_VAR_R,"Unknown"},
    {"B0BI","ui8 ",1,K_VAR_R,"Unknown"},
    {"B0CT","ui16",2,K_VAR_R,"Unknown"},
    {"B0FC","ui16",2,K_VAR_R,"Unknown"},
    {"B0FV","ui16",2,K_VAR_R,"Unknown"},
    {"B0LI","ui16",2,K_VAR_R,"Unknown"},
    {"B0RI","ui16",2,K_VAR_R,"Unknown"},
    {"B0RM","ui16",2,K_VAR_R,"Unknown"},
    {"B0SN","ch8*",13,K_VAR_R,"System Serial#"},
    {"B0St","ui16",2,K_VAR_R,"Unknown"},
    {"B0TF","ui16",2,K_VAR_R,"Unknown"},
    {"BALG","flag",1,K_VAR_R,"Unknown"},
    {"BATP","flag",1,K_VAR_R,"System currently being powered by battery. Used by FW TDM. Needed on all platforms."},
    {"BBAD","flag",1,K_VAR_R,"Unknown"},
    {"BBIN","flag",1,K_VAR_R,"Unknown"},
    {"BC1V","ui16",2,K_VAR_R,"Unknown"},
    {"BC2V","ui16",2,K_VAR_R,"Unknown"},
    {"BCCT","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHA","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHB","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHF","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHG","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHL","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHO","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHP","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHR","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHT","ui8 ",1,K_VAR_R,"Unknown"},
    {"BCHX","ui8 ",1,K_VAR_R,"Unknown"},
    {"BEZL","ui8 ",1,K_VAR_R,"Unknown"},
    {"BILB","ui8 ",1,K_VAR_R,"Unknown"},
    {"BILO","ui8 ",2,K_VAR_R,"Unknown"},
    {"BNCM","ui8 ",1,K_VAR_R,"Unknown"},
    {"BNum","ui8 ",1,K_VAR_R,"Maximum number of supported batteries. Architecturally visiable key used by EFIUtil. Needed on all platforms."},
    {"BRSC","ui16",2,K_VAR_R,"Unknown"},
    {"BSAC","ui8 ",1,K_VAR_R,"Unknown"},
    {"BSDC","ui8 ",1,K_VAR_R,"Unknown"},
    {"BSIn","ui8 ",1,K_VAR_R ,"Unknown"},
    {"BTIL","ui16",2,K_VAR_R,"Unknown"},
    {"BTTI","ui8 ",1,K_VAR_R,"Unknown"},
    {"BTVI","ui8 ",1,K_VAR_R,"Unknown"},
    {"BTVR","ui8 ",1,K_VAR_R,"Unknown"},
    {"BTVT","ui8 ",1,K_VAR_R,"Unknown"},
    {"CHBI","ui16",2,K_VAR_R,"Unknown"},
    {"CHBV","ui16",2,K_VAR_R,"Unknown"},
    {"CHGC","ui16",2,K_VAR_R,"Unknown"},
    {"CHGD","flag",1,K_VAR_R,"Unknown"},
    {"CHGI","ui16",2,K_VAR_R,"Unknown"},
    {"CHGV","ui16",2,K_VAR_R,"Unknown"},
    {"CHPV","si16",2,K_VAR_R,"Unknown"},
    {"CLK!","ui8 ",1,K_VAR_R,"Unknown"},
    {"CLKC","{clc",10,K_VAR_R,"Unknown"},
    {"CLKH","{clh",8,K_VAR_R,"Unknown"},
    {"CLKS","fp1f",2,K_VAR_R,"Unknown"},
    {"CLKT","ui32",4,K_FUNC_RW,"Unknown"},
    {"CLSD","ui16",2,K_VAR_R,"Unknown"},
    {"CLWK","ui16",2,K_VAR_R,"Unknown"},
    {"CRCB","ui32",4,K_VAR_R,"Returns a CRC32 value representing all of UserBootMAT."},
    {"CRCU","ui32",4,K_FUNC_R,"Generates a CRC32 value representing all of UserMAT."},
    {"DPLM","{lim",3,K_VAR_R,"Unknown"},
    {"EPCA","ui32",4,K_CONST,"EPM CV Start Address"},
    {"EPCF","flag",1,K_FUNC_R,"EPM CV Flash Status 1=flashed"},
    {"EPCI","ui32",4,K_VAR_R,"EPM CV Configuration ID"},
    {"EPCV","ui16",2,K_VAR_R,"EPM CV Configuration Version"},
    {"EPMA","ch8*",4,K_FUNC_R,"EPM Meta Table Address First set EPMI and then read EPMA"},
    {"EPMI","ui8 ",1,K_VAR_ATOM_RW,"EPM Meta Table Index First set EPMI and then read EPMA"},
    {"EPUA","ui32",4,K_CONST,"EPM UV Start Address"},
    {"EPUF","flag",1,K_FUNC_R,"EPM UV Flash Status. 1=flashed"},
    {"EPUI","ui32",4,K_VAR_R,"EPM UV Configuration ID"},
    {"EPUV","ui16",2,K_VAR_R,"EPM UV Configuration Version"},
    {"EVCT","ui16",2,K_FUNC_R,"Unknown"},
    {"EVMD","ui32",0,K_FUNC_W,"Unknown"},
    {"EVRD","ch8*",32,K_FUNC_R,"Unknown"},
    {"F0Ac","fpe2",2,K_VAR_ATOM_RW,"Fan0 Actual RPM, DIAG_LOG"},
    {"F0ID","{fds",16,K_CONST,"Fan0 Description"},
    {"F0Mn","fpe2",2,K_VAR_ATOM_RW,"Fan0 Minimum RPM"},
    {"F0Mt","ui16",2,K_VAR_ATOM_RW,"Fan0 Max calculated target RPM"},
    {"F0Mx","fpe2",2,K_VAR_ATOM_RW,"Fan0 Maximum RPM"},
    {"F0Sf","fpe2",0,K_VAR_ATOM_RW,"Fan0 Safe RPM"},
    {"F0Tg","fpe2",2,K_VAR_ATOM_RW,"Unknown"},
    {"F1Ac","fpe2",2,K_VAR_ATOM_RW,"Fan1 Actual RPM"},
    {"F1ID","{fds",16,K_CONST,"Fan1 Description"},
    {"F1Mn","fpe2",2,K_VAR_ATOM_RW,"Fan1 Minimum RPM"},
    {"F1Mt","ui16",2,K_VAR_ATOM_RW,"Fan1 Max calculated target RPM"},
    {"F1Mx","fpe2",2,K_VAR_ATOM_RW,"Fan1 Maximum RPM"},
    {"F1Sf","fpe2",0,K_VAR_ATOM_RW,"Fan1 Safe RPM"},
    {"F1Tg","fpe2",2,K_VAR_ATOM_RW,"Unknown"},
    {"F2Ac","fpe2",0,K_VAR_ATOM_RW,"Fan2 Actual RPM"},
    {"F2ID","{fds",0,K_CONST,"Fan2 Description"},
    {"F2Mn","fpe2",0,K_VAR_ATOM_RW,"Fan2 Minimum RPM"},
    {"F2Mt","ui16",0,K_VAR_ATOM_RW,"Fan2 Max calculated target RPM"},
    {"F2Mx","fpe2",0,K_VAR_ATOM_RW,"Fan2 Maximum RPM"},
    {"F2Sf","fpe2",0,K_VAR_ATOM_RW,"Fan2 Safe RPM"},
    {"F2Tg","fpe2",0,K_VAR_ATOM_RW,"Unknown"},
    {"FNum","ui8 ",1,K_CONST,"Number of supported fans."},
    {"FPhz","si16",2,K_VAR_R,"Unknown"},
    {"FS! ","ui16",2,K_VAR_ATOM_RW ,"Unknown"},
    {"GCID","ui32",0,K_VAR_ATOM_RW,"Unknown"},
    {"GPU!","ui8 ",0,K_VAR_ATOM_RW ,"Unknown"},
    {"GTHR","ui8 ",0,K_VAR_ATOM_RW ,"Unknown"},
    {"HBWK","flag",1,K_VAR_RW,"Allows a one-time lid-open event to \"wake\" the system from S5."},
    {"HDBS","ui8 ",1,K_VAR_ATOM_R,"Hang Detect. A/B switch value"},
    {"HDST","ui16",4,K_VAR_ATOM_R,"Hang Detect. Current System State Machine value"},
    {"HDSW","ui32",4,K_VAR_ATOM_R,"Hang Detect. {Sleep[15:0] Wake[15:0]} Count."},
    {"HIBW","flag",1,K_VAR_R,"Unknown"},
    {"IC0C","fp6a",2,K_VAR_ATOM_RW,"CPU 0 core current."},
    {"IC0R","fp4c",2,K_VAR_R,"Unknown"},
    {"IC0c","ui16",2,K_VAR_R,"Unknown"},
    {"IC0r","ui16",2,K_VAR_R,"Unknown"},
    {"IC1C","fp4c",2,K_VAR_R,"Unknown"},
    {"IC2C","fp6a",2,K_VAR_R,"Unknown"},
    {"ID0R","fp3d",2,K_VAR_ATOM_RW,"DC In S0 rail current."},
    //{"ID5R","fp4c",0,K_VAR_ATOM_RW,"DC In S5 rail current."},
    {"ID5R","flt ",0,K_VAR_ATOM_RW,"DC In S5 rail current."},
    // 24-Jan-2018 now seing the type of IG0C as 'flt' WTF is it
    {"IG0C","fp6a",2,K_VAR_R,"Unknown"}, // IG0C|[fp4c]|0.00512695 (ice) IG0C|[fp6a]|0.000976562 (zed)
    //{"IG0R","fp4c",0,K_VAR_ATOM_RW,"GPU 0 rail current."},
    {"IG0R","flt ",0,K_VAR_ATOM_RW,"GPU 0 rail current."},
    {"IG0c","ui16",2,K_VAR_R,"Unknown"},
    {"IG0r","ui16",0,K_VAR_ATOM_RW,"GPU 0 rail current. Raw ADC input value."},
    {"IG1C","fp6a",2,K_VAR_R,"Unknown"},
    {"IM0R","fp4c",2,K_VAR_R,"Unknown"},
    {"IN0C","fp6a",2,K_VAR_R,"Unknown"},
    {"IN0R","fp6a",2,K_VAR_R,"Unknown"},
    {"IN0c","ui16",2,K_VAR_R,"Unknown"},
    {"IN1C","fp4c",2,K_VAR_R,"Unknown"},
    {"IN1R","fp6a",2,K_VAR_R,"Unknown"},
    {"IN1c","ui16",2,K_VAR_R,"Unknown"},
    {"IP0R","fp4c",2,K_VAR_R,"Unknown"},
    {"IP0r","ui16",2,K_VAR_R,"Unknown"},
    {"LAcN","ui8 ",1,K_VAR_R,"Unknown"},
    {"LAtN","ui16",2,K_VAR_R,"Unknown"},
    {"LCCN","ui8 ",1,K_VAR_R,"LPC Debug counter data: Num of Acpi Notifies"},
    {"LCCQ","ui8 ",1,K_VAR_R,"LPC Debug counter data: Num of Acpi Queries"},
    {"LCKA","ui8 ",1,K_VAR_R,"LPC Debug counter data: Num of Key Accesses"},
    {"LCSA","ui8 ",1,K_VAR_R,"LPC Debug counter data: Num of Smb Accesses"},
    {"LCTN","ui8 ",1,K_VAR_R,"LPC Debug counter data: Num of Attn Notifies"},
    {"LCTQ","ui8 ",1,K_VAR_R,"LPC Debug counter data: Num of Attn Queries"},
    {"LDSP","flag",0,K_VAR_W,"When OS X sleeps due to a lid-closed event, it writes a 1 in this key."},
    {"LKSB","{lkb",2,K_VAR_R,"Unknown"},
    {"LS! ","ui8 ",1,K_VAR_RW,"Unknown"},
    {"LSCF","{lsc",10,K_VAR_ATOM_RW,"LmsConfig structure provides overall system-specific config info for the SIL."},
    {"LSDD","{lsd",8,K_VAR_ATOM_RW,"LmsDwell structures provide dwell fade-down configuration"},
    {"LSDU","{lsd",8,K_VAR_ATOM_RW,"LmsDwell structures provide dwell fade-up configuration"},
    {"LSFD","{lsf",6,K_VAR_ATOM_RW,"LmsFlare structures provide flare config for non-breathing fade-down"},
    {"LSFU","{lsf",6,K_VAR_ATOM_RW,"LmsFlare structures provide flare config for non-breathing fade-up"},
    {"LSLB","{pwm",2,K_VAR_ATOM_RW,"SIL's PWM \"Full On\" value (usually 0xFFFF, used for power switch override)"},
    {"LSLF","{pwm",2,K_VAR_ATOM_RW,"SIL's PWM \"Off\" value (usually 0)"},
    {"LSLN","{pwm",2,K_VAR_ATOM_RW,"SIL's PWM \"On\" value (varies per system)"},
    {"LSOF","flag",1,K_VAR_R,"Reads TRUE (1) if the SIL is Off"},
    {"LSOO","flag",0,K_FUNC_W,"Unknown"},
    {"LSPV","{pwm",2,K_VAR_R,"SIL's Current PWM value"},
    {"LSRB","flag",0,K_FUNC_W,"Unknown"},
    {"LSSB","{lso",0,K_FUNC_W,"Unknown"},
    {"LSSE","flag",1,K_VAR_RW,"Unknown"},
    {"LSSS","{lso",0,K_FUNC_W,"Unknown"},
    {"LSSV","ui16",2,K_VAR_RW,"Unknown"},
    {"LSUP","ui8 ",0,K_FUNC_W ,"Unknown"},
    {"MACA","ui32",4,K_VAR_ATOM_RW,"Memory Address Cycle Address. Sets the address for subsequent MACR calls"},
    {"MACM","flag",1,K_VAR_ATOM_RW,"Memory Address Cycle Mode. Sets the addressing mode for MACR calls. Defaults to auto-incrementing"},
    {"MACR","ch8*",0,K_FUNC_R,"Unknown"},
    {"MOCF","ui16",2,K_VAR_ATOM_RW,"MOtion sensor (SMS) Configuration register"},
    {"MOCN","ui16",2,K_VAR_ATOM_RW,"MOtion sensor (SMS) Control register - enables accelerometer and threshold testing"},
    {"MOHD","ui8 ",1,K_VAR_R,"Unknown"},
    {"MOHT","sp78",2,K_VAR_R,"Unknown"},
    {"MOLD","ui8 ",1,K_VAR_R,"Unknown"},
    {"MOLT","sp78",2,K_VAR_R,"Unknown"},
    {"MOST","ui16",2,K_VAR_R,"Unknown"},
    {"MOVX","sp78",2,K_VAR_R,"Unknown"},
    {"MOVY","sp78",2,K_VAR_R,"Unknown"},
    {"MOVZ","sp78",2,K_VAR_R,"Unknown"},
    {"MO_X","sp78",2,K_VAR_R,"Unknown"},
    {"MO_Y","sp78",2,K_VAR_R,"Unknown"},
    {"MO_Z","sp78",2,K_VAR_R,"Unknown"},
    {"MSAL","ui8 ",1,K_VAR_R,"Unknown"},
    {"MSAR","ui16",2,K_VAR_R,"Unknown"},
    {"MSAc","fp88",2,K_VAR_ATOM_R,"Returns the average CPU PLIMIT sent by the SMC, DIAG_LOG"},
    {"MSAg","fp88",2,K_VAR_ATOM_R,"Returns the average GPU PLIMIT sent by the SMC, DIAG_LOG"},
    {"MSAi","fp88",2,K_VAR_R,"Unknown"},
    {"MSAm","fp88",2,K_VAR_ATOM_R,"Returns the average MEM PLIMIT sent by the SMC, DIAG_LOG"},
    {"MSBC","ui16",2,K_VAR_R,"Unknown"},
    {"MSBP","ui16",2,K_VAR_R,"Unknown"},
    {"MSBc","ui16",2,K_VAR_R,"Unknown"},
    {"MSBp","ui16",2,K_VAR_R,"Unknown"},
    {"MSC0","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSC1","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSC2","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSC3","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCP","ui16",0,K_VAR_ATOM_RW,"Total number of sub samples to calibrate with"},
    {"MSCR","ui16",0,K_VAR_ATOM_RW,"Total number of sub samples to calibrate with"},
    {"MSCS","ui8 ",0,K_FUNC_W,"Calibration Start key - Writing a value of 0x11 to this key will begin"},
    {"MSCT","ui8 ",0,K_VAR_ATOM_RW,"Total number of samples to calibrate with"},
    {"MSCa","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCb","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCc","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCd","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCl","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCm","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCn","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSCo","ui16",0,K_VAR_ATOM_RW,"Calibration key"},
    {"MSDI","flag",1,K_VAR_R,"Unknown"},
    {"MSDW","flag",0,K_FUNC_W,"Unknown"},
    {"MSFG","ui8 ",1,K_VAR_R,"Unknown"},
    {"MSHA","fp79",0,K_VAR_ATOM_R,"Average HDD activity (range 0 to 1)"},
    {"MSLD","ui8 ",1,K_VAR_R,"Returns the current Lid Switch state"},
    {"MSPA","fp6a",2,K_VAR_ATOM_R,"Average count of prochot assertions between 0 and 1"},
    {"MSPC","ui8 ",1,K_FUNC_RW,"Available \"Power states\" for the CPU"},
    {"MSPS","ui16",2,K_VAR_R,"Unknown"},
    {"MSPZ","ui8 ",1,K_VAR_R,"Unknown"},
    {"MSPs","ui16",2,K_VAR_R,"Unknown"},
    {"MSSD","si8 ",1,K_FUNC_RW ,"Unknown"},
    {"MSSE","ui16",2,K_VAR_R,"Unknown"},
    {"MSSF","ui32",4,K_FUNC_RW,"Unknown"},
    {"MSSP","si8 ",1,K_VAR_RW,"Stores the last known Sleep Request cause. See MSSD for list of causes."},
    {"MSSS","{mss",1,K_VAR_R,"Returns the current (enumerated) state of the SMC's System State Machine"},
    {"MSTC","ui16",2,K_VAR_ATOM_RW,"- ScratchPad register that outputs via Tlog so that a script running on the SUT can add to the log what test case was running."},
    {"MSTM","ui8 ",1,K_FUNC_R,"Returns whether power balancing is enabled or not."},
    {"MSTc","ui8 ",1,K_VAR_ATOM_R,"Returns the last CPU PLIMIT sent by the SMC"},
    {"MSTg","ui8 ",1,K_VAR_ATOM_R,"Returns the last GPU PLIMIT sent by the SMC"},
    {"MSTm","ui8 ",1,K_VAR_ATOM_R,"Returns the last MEM PLIMIT sent by the SMC"},
    {"MSWR","ui8 ",0,K_FUNC_W ,"Unknown"},
    {"MSXC","ch8*",4,K_VAR_R,"Unknown"},
    {"MSXD","ch8*",16,K_VAR_R,"Unknown"},
    {"MSXK","ch8*",32,K_VAR_R,"Unknown"},
    {"MSXN","ui8 ",1,K_VAR_R,"Unknown"},
    {"MSXS","ch8*",4,K_VAR_R,"Unknown"},
    {"MSXb","ui8 ",1,K_VAR_R,"Unknown"},
    {"MSXc","ch8*",4,K_VAR_R,"Unknown"},
    {"MSXd","ch8*",16,K_VAR_R,"Unknown"},
    {"MSXk","ch8*",32,K_VAR_R,"Unknown"},
    {"MSXm","ui16",2,K_VAR_R,"Unknown"},
    {"MSXn","ui8 ",1,K_VAR_R,"Unknown"},
    {"MSXs","ui32",4,K_VAR_R,"Unknown"},
    {"NATJ","ui8 ",1,K_VAR_RW ,"Ninja Action Timer Job"},
    {"NATi","ui16",2,K_VAR_ATOM_RW,"Ninja Action Timer"},
    {"NOPB","ui8 ",1,K_VAR_R,"Unknown"},
    {"NTOK","ui8 ",0,K_FUNC_W,"Key for OS X to write to turn on Proprietary Host Notifies."},
    {"ONMI","ui8 ",1,K_VAR_ATOM_RW,"NMI flag (For OS NMI)"},
    {"OSK0","ch8*",32,K_VAR_R,"OSKey0"},
    {"OSK1","ch8*",32,K_VAR_R,"OSKey1"},
    {"OWCT","ui16",2,K_VAR_R,"Unknown"},
    {"PC0C","fp88",2,K_VAR_ATOM_RW,"CPU 0 core power"},
    {"PC0R","fp88",2,K_VAR_R,"Unknown"},
    {"PC0c","ui16",0,K_VAR_ATOM_RW,"CPU 0 core power. Raw ADC input value."},
    {"PC1C","fp88",2,K_VAR_R,"Unknown"},
    {"PC2C","fp88",2,K_VAR_R,"Unknown"},
    {"PD0R","fp88",2,K_VAR_ATOM_RW,"DC-In MLB S0 rail power"},
    {"PD5R","fp88",0,K_VAR_ATOM_RW,"DC-In MLB S5 rail power"},
    {"PDMR","fp88",0,K_VAR_ATOM_RW,"DC-In MLB Total (S0+S5) power"},
    {"PDTR","fpa6",0,K_VAR_ATOM_RW,"DC-In System Total (S0+S5+LCD+HDD) power"},
    {"PG0C","fp88",2,K_VAR_R,"Unknown"},
    {"PG0R","fp88",0,K_VAR_ATOM_RW,"GPU0 rail power"},
    {"PG1C","fp88",2,K_VAR_R,"Unknown"},
    {"PHPC","fp88",2,K_VAR_R,"Unknown"},
    {"PM0R","fp88",2,K_VAR_R,"Unknown"},
    {"PN0C","fp88",2,K_VAR_R,"Unknown"},
    {"PN0R","fp88",2,K_VAR_R,"Unknown"},
    {"PN1C","fp88",2,K_VAR_R,"Unknown"},
    {"PN1R","fp88",2,K_VAR_R,"Unknown"},
    {"PP0R","fp88",2,K_VAR_R,"Unknown"},
    {"PTHC","fp88",2,K_VAR_R,"Unknown"},
    {"PZ0E","fp88",0,K_VAR_ATOM_RW,"Zone0 average target power (PC0C+PG0R)"},
    {"PZ0G","fp88",0,K_VAR_ATOM_RW,"Zone0 average power (PC0C+PG0R)"},
    {"RBr ","ch8*",8,K_DESC_STR,"Source branch"},
    {"REV ","{rev",6,K_CONST,"Source revision"},
    {"RMde","char",1,K_CONST,"Mode. What code is currently being executed. 'B'=base flasher, 'U'=update flasher or 'A'=app code"},
    {"RPlt","ch8*",8,K_CONST,"Platform String"},
    {"RSvn","ui32",4,K_CONST,"SVN database revision"},
    {"RVBF","{rev",6,K_FUNC_R,"Base flasher revision"},
    {"RVUF","{rev",6,K_FUNC_R,"Update flasher revision"},
    {"SAS!","ui32",4,K_VAR_R,"Unknown"},
    {"SBF ","ui16",0,K_VAR_ATOM_R ,"Unknown"},
    {"SBFC","ui16",0,K_VAR_ATOM_RW,"Unknown"},
    {"SBFE","flag",0,K_VAR_ATOM_RW,"Unknown"},
    {"SBS!","ui16",2,K_VAR_R,"Unknown"},
    {"SCIA","ui16",2,K_FUNC_RW,"Lpc Base Address for SCIF, default is 0x3F8"},
    {"SCIL","ui8 ",1,K_FUNC_RW,"Set this to 1 to enable SCIF to be LPC slave for EFI debug"},
    {"SCTg","sp78",0,K_VAR_ATOM_RW,"CPU Thermal Target Temp"},
    {"SCTh","ui16",2,K_VAR_R,"Unknown"},
    {"SCTi","ui8 ",2,K_VAR_R,"Unknown"},
    {"SCTj","ui8 ",2,K_VAR_R,"Unknown"},
    {"SDPE","ui8 ",0,K_VAR_ATOM_RW,"Mode bit to enable polling of developmental build sensors. Default state will vary depending on build."},
    {"SDRd","ui16",0,K_FUNC_W,"Unknown"},
    {"SGHT","ui8 ",0,K_VAR_ATOM_R,"Sensor Graphics HoT. 1 = GPU Overtemp"},
    {"SGTT","sp78",0,K_VAR_ATOM_RW,"Unknown"},
    {"SGTg","sp78",0,K_VAR_ATOM_RW,"GPU Thermal Target Temp"},
    {"SHTg","sp78",0,K_VAR_ATOM_RW,"HDD Thermal Target Temp"},
    {"SIP ","ui8 ",1,K_VAR_R,"Unknown"},
    {"SIS!","ui16",2,K_VAR_R,"Unknown"},
    {"SIT!","hex_",2,K_VAR_R,"Unknown"},
    {"SLPT","sp78",0,K_VAR_ATOM_RW,"LCD Prochot threshold. TL0P temp at which Prochot will be asserted."},
    {"SLST","sp78",0,K_VAR_ATOM_RW,"LCD Sleep threshold. TL0P temp at which Sleep will be requested."},
    {"SLTg","sp78",0,K_VAR_ATOM_RW,"LCD Fan Temp Target"},
    {"SLTp","sp78",0,K_VAR_ATOM_RW,"LCD Power Temp Target"},
    {"SM0x","ui16",2,K_VAR_R,"Unknown"},
    {"SM0y","ui16",2,K_VAR_R,"Unknown"},
    {"SM0z","ui16",2,K_VAR_R,"Unknown"},
    {"SMBC","ch8*",5,K_VAR_R,"Unknown"},
    {"SMBG","ui8 ",1,K_VAR_R,"Unknown"},
    {"SMBR","ch8*",32,K_VAR_R,"Unknown"},
    {"SMBS","ch8*",2,K_VAR_R,"Unknown"},
    {"SMBW","ch8*",32,K_VAR_R,"Unknown"},
    {"SOTg","sp78",0,K_VAR_ATOM_RW,"ODD Thermal Target Temp"},
    {"SPH0","ui16",2,K_VAR_R,"CPU Prochot event count since last boot"},
    {"SPHR","ui32",0,K_VAR_ATOM_R,"Unknown"},
    {"SPHS","ui8 ",1,K_VAR_ATOM_RW,"Indicates if PROCHOT was ever set after entering S0, DIAG_LOG"},
    {"SPHT","ui8 ",1,K_VAR_ATOM_R,"Unknown"},
    {"SPHZ","ui8 ",0,K_FUNC_W ,"Unknown"},
    {"SPS!","ui16",2,K_VAR_R,"Unknown"},
    {"SpCP","fps4",0,K_VAR_ATOM_R,"Unknown"},
    {"SpCS","fps4",0,K_VAR_ATOM_R,"Unknown"},
    {"SpCT","fpc4",0,K_VAR_ATOM_R,"Unknown"},
    {"SpPT","sp78",0,K_VAR_ATOM_RW,"PS Prochot threshold. Tp0P temp at which Prochot will be asserted"},
    {"SpST","sp78",0,K_VAR_ATOM_RW,"PS Sleep threshold. Tp0P temp at which Sleep will be requested."},
    {"SpTg","sp78",0,K_VAR_ATOM_RW,"PS Fan Temp Target"},
    {"TA0P","sp78",0,K_VAR_ATOM_RW,"Ambient temp"},
    {"TB0T","sp78",2,K_VAR_R,"Unknown"},
    {"TB1T","sp78",2,K_VAR_R,"Unknown"},
    {"TB2T","sp78",2,K_VAR_R,"Unknown"},
    {"TB3T","sp78",2,K_VAR_R,"Unknown"},
    
    {"TC0D","sp78",2,K_VAR_ATOM_RW,"CPU 0 die temp"},
    {"TC0F","sp78",2,K_VAR_R,"CPU 0 Unknown"},
    {"TC0H","sp78",0,K_VAR_ATOM_RW,"CPU 0 Heatsink temp"},
    {"TC0P","sp78",2,K_VAR_ATOM_RW,"CPU 0 Proximity temp"},
    
    {"TG0D","sp78",2,K_VAR_ATOM_RW,"GPU 0 die temp"},
    {"TG0F","sp78",2,K_VAR_R,"GPU 0 Unknown"},
    {"TG0H","sp78",2,K_VAR_ATOM_RW,"GPU 0 Heatsink temp"},
    {"TG0P","sp78",2,K_VAR_ATOM_RW,"GPU 0 Proximity temp"},
    {"TG0T","sp78",2,K_VAR_R,"GPU 0 Unknown"},
    
    {"TG1D","sp78",2,K_VAR_ATOM_RW,"GPU 1 die temp"},
    {"TG1F","sp78",2,K_VAR_R,"GPU 1 Unknown"},
    {"TG1H","sp78",2,K_VAR_ATOM_RW,"GPU 1 Heatsink temp"},
    {"TG1P","sp78",2,K_VAR_ATOM_RW,"GPU 1 Proximity temp"},
    {"TG1T","sp78",2,K_VAR_R,"GPU 1 Unknown"},
    
    {"TH0P","sp78",0,K_VAR_ATOM_RW,"HardDisk proximity temp"},
    {"TL0P","sp78",0,K_VAR_ATOM_RW,"LCD proximity temp"},
    {"TN0D","sp78",2,K_VAR_R,"Unknown"},
    {"TN0P","sp78",2,K_VAR_R,"Unknown"},
    {"TO0P","sp78",0,K_VAR_ATOM_RW,"Optical Drive proximity temp"},
    {"TTF0","sp78",2,K_VAR_R,"Unknown"},
    {"TW0P","sp78",0,K_VAR_ATOM_RW,"Airport temp"},
    {"Th2H","sp78",2,K_VAR_R,"Unknown"},
    {"Tm0P","sp78",2,K_VAR_ATOM_RW,"Misc Local temp"},
    {"Tp0P","sp78",0,K_VAR_ATOM_RW,"Power Supply Proximity temp"},
    {"Ts+S","sp78",2,K_VAR_R,"Unknown"},
    {"Ts0P","sp78",2,K_VAR_R,"Unknown"},
    {"Ts0S","sp78",2,K_VAR_R,"Unknown"},
    {"UPRC","ui16",2,K_CONST,"Type of SMC microcontroller upon which system is based (value of UPROC macro)"},
    {"VC0C","fp2e",2,K_VAR_ATOM_RW,"CPU 0 core voltage."},
    {"VC0c","ui16",2,K_VAR_ATOM_RW,"CPU 0 core voltage. Raw ADC input value."},
    {"VD0R","fp4c",0,K_VAR_ATOM_RW,"DC In S0 rail voltage."},
    {"VD0r","ui16",2,K_VAR_R,"Unknown"},
    {"VD5R","fp4c",0,K_VAR_ATOM_RW,"DC In S5 rail voltage."},
    {"VG0C","fp2e",2,K_VAR_R,"Unknown"}, // fp2e on  1.21f4 ice iMac7,1 fp4c on 1.42f4 zed MacBookPro5,2
    {"VG0R","fp4c",0,K_VAR_ATOM_RW,"GPU 0 rail voltage."},
    {"VG0c","ui16",2,K_VAR_R,"Unknown"},
    {"VG0r","ui16",0,K_VAR_ATOM_RW,"GPU 0 rail voltage. Raw ADC input value."},
    {"VG1C","fp2e",2,K_VAR_R,"Unknown"},
    {"VN0C","fp2e",2,K_VAR_R,"Unknown"},
    {"VN0R","fp2e",2,K_VAR_R,"Unknown"},
    {"VN0r","ui16",2,K_VAR_R,"Unknown"},
    {"VP0R","fp4c",2,K_VAR_R,"Unknown"},
    {"dBA0","sp78",0,K_VAR_ATOM_R,"Acoustic Reporting. Fan 0 Noise Component (dBA)."},
    {"dBA1","sp78",0,K_VAR_ATOM_R,"Acoustic Reporting. Fan 1 Noise Component (dBA)."},
    {"dBA2","sp78",0,K_VAR_ATOM_R,"Acoustic Reporting. Fan 2 Noise Component (dBA)."},
    {"dBAH","sp78",0,K_VAR_ATOM_R,"Acoustic Reporting. HDD Noise Component (dBDA)."},
    {"dBAT","sp78",0,K_VAR_ATOM_R,"Acoustic Reporting. Total Noise of all calculated components (dBDA)."},
    {"zDBG","ui8 ",1,K_FUNC_RW,"Set this to 1 to enable SCIF debug output to USB 0 Port"}
};
#endif /* __DEF_SMS_DESC__ */

smc_desc_t *smc_lookup_desc(SMC_key_val_t *key);

#endif
