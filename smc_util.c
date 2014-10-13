//
//  smc_util.c
//  smc_utils
//
//  Created by Mark Garrett on 25/11/2011.
//  Copyright (c) 2011 Garetech Computer Solutions. All rights reserved.
//

#include "smc_utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>


static void dousage(char *progid);

static void dousage(char *progid)
{
	// pDcqtsxnvdfw:lh?
	// pDf
    fprintf(stderr, "%s [-c] [-q] [-d] [-D] [-p] [-f] [-v] [-t] [-s] [-x] [-n] [-r <key> ] [ -w <key> ] [-l]   [ <value>|keys... ]\n", progid);
    fprintf(stderr, "   -c          suppress newline\n");
    fprintf(stderr, "   -q          be quiet as a mouse\n");
    fprintf(stderr, "   -d          increase debug output\n");
    fprintf(stderr, "   -D          Display known descriptions\n");
    fprintf(stderr, "   -p          Private/Paranoide, blank out the System Serial#\n");
    fprintf(stderr, "   -f          display FAN specific data\n");
    fprintf(stderr, "   -v          display values\n");
    
    fprintf(stderr, "   -t          display [type](s)\n");
    fprintf(stderr, "   -s          display :size\n");
    fprintf(stderr, "   -x          dump values in (hexbytes)\n");
    fprintf(stderr, "   -n          when normally a single line output line breaks between variables\n");
    
    fprintf(stderr, "   -w <key>    write value to key\n");
    fprintf(stderr, "   -l          list all keys to stdout\n");
    fprintf(stderr, " with out options -w or -l the default is to read args[] as a series of keys to display\n");
    
    exit(EINVAL);    
}

gbl_params_t PARAMS;

int main(int argc, char *argv[])
{
    char	c;
    int     usage;
    
    char    *value;
    char    *key;
    int     idx;
    direction_t  direction;
    kern_return_t   r0;
    gbl_params_t    *params = &PARAMS;
    
    usage =   0;
    optarg  =   NULL;
    
    bzero(params,sizeof(gbl_params_t));
    params->progid   =   strdup(argv[0]);
    params->dbg      =   0;
    
    params->fldidx   =   1;
    key             =   NULL;
    value           =   NULL;
    direction       =   RD;
    params->outfd    =   stdout;
    params->flg      =   0;
    params->newline  = "\n";
    params->model    = get_sysmodel_dynamic();
    
    params->flg      |= F_NOISY; // by default noisy output
    while (!usage && ((c=getopt(argc,argv, "pDcqtsxnvdfw:lh?")) != -1 )) {
        switch(c) {
            case 'p':
                params->flg |= F_PRIVATE;
                break;
            case 'D':
                params->flg |= F_DESCRIBE;
                break;
            case 'c':
                params->newline = "";
                break;
            case 'q':
                params->flg &= ~F_NOISY; // clear noisy
                break;
            case 't':
                params->flg |= F_SHOWTYPE;
                break;
            case 's':
                params->flg |= F_SHOWSIZE;
                break;
            case 'x':
                params->flg |= F_DUMPHEX;
                break;
            case 'n':
                params->flg |= F_NL;
                break;
            case 'v':
                params->flg |= F_VALUES;
                break;
                
            case 'd':
                params->flg |= F_DEBUG;
                params->dbg++;
                break;
                
            case 'f':
                direction = FAN;
                break;
                
            case 'w':
                key = strdup(optarg);
                if (key == NULL ) {
                    if (params->flg&F_NOISY)
                        fprintf(stderr, "# Out of memory on args, impossible i say ;)\n");
                    exit(ENOMEM);
                }
                direction=WR;
                break;
            case 'l':
                key = NULL; // a null value will list all
                direction=LST;
                break;
                
            default:
                usage++;
                break;
        }
    }
    argc -= (optind);
    argv += (optind);
    
    if (usage) {
	    dousage(params->progid);
        exit(EINVAL);
	}
    if (params->flg & F_DEBUG) {
        fprintf(params->outfd, "# System Model: %s %s", params->model, params->newline);
    }
    r0 = smc_open(&params->conn);
    if (r0 != kIOReturnSuccess) {
        if (params->flg&F_NOISY)
            fprintf(stderr, "# Error opening SMC subsystem: %d\n", r0);
        
    } else {
        
        switch (direction) {
            case WR:
                if (argc == 1) {
                    value = strdup(argv[0]);
                    if (value == NULL ) {
                        if (params->flg&F_NOISY)
                            fprintf(stderr, "# Out of memory on args, impossible i say ;)\n");
                        exit(ENOMEM);
                    }
                    r0 = smc_key_write(params->conn, key, value);
                } else {
                    dousage(params->progid);
                    r0 = EINVAL;
                }
                break;
                
            case FAN:
                report_fans(params->conn);
                break;
                
            case TEMP:
                break;
                
            case LST:
                r0 = smc_display_allkeys(params->conn, params->model);
                break;
            case RD:
                for (idx=0;idx<argc;idx++) {
                    r0 = smc_key_display(params->conn, argv[idx]);
                    if (r0 != kIOReturnSuccess) {
                        if (params->flg&F_NOISY)
                            fprintf(stderr, "# Error displaying key: %s: %d\n", argv[idx], r0);
                    }
                }
                break;
                
            case RW: // just to complete the values of direction, no function here
            case UD:
                if (params->flg&F_NOISY)
                    fprintf(stderr, "# internal error undefined direction\n");
                exit(EINVAL);
                break;
        }
        // TODO: r0 may hold a failure from an operation ?
        r0 = smc_close(&params->conn);
        if (r0 != kIOReturnSuccess) {
            if (params->flg&F_NOISY)
                fprintf(stderr, "# Error closing SMC subsystem: %d\n", r0);
        }
    }
    exit(r0);
}
