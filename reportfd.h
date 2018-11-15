//
//  reportfd.h
//  smc_utils
//
//  Created by mark on 29/03/2014.
//  Copyright (c) 2014 Garetech Computer Solutions. All rights reserved.
//

#ifndef smc_utils_reportfd_h
#define smc_utils_reportfd_h

#include "smc_utils_gbl.h"

int reportfd(flg_e flgmask, char *fmt, ...);
int reportc(int c);
//int reportfd_fldidx(void);
int flag_test(int flgmask);
void newline(void);

#endif
