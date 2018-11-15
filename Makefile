
#CC = cc
#CFLAGS = -mmacosx-version-min=10.7  -Wall -g
#LDFLAGS = -mmacosx-version-min=10.7  -Wall -g -framework IOKit

CFLAGS = 
LDFLAGS = -g -framework IOKit

SRCS = fixedpoint.c optarg.c reportfd.c smc_desc.c smc_types.c  mc_util.c

all: smc_util

.c.o:
	                $(CC) $(CFLAGS) -c $*.c


smc_util:	smc_util.o fixedpoint.o smc_util.o smc_desc.o smc_types.o reportfd.o optarg.c

depend:
	                mkdep $(CFLAGS) $(SRCS)
clean:
	        -rm -f fixedpoint.o smc_util.o  smc_types.o reportfd.o smc_util
