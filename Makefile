
#CC = cc
#CFLAGS = -mmacosx-version-min=10.7  -Wall -g
#LDFLAGS = -mmacosx-version-min=10.7  -Wall -g -framework IOKit

CFLAGS = 
LDFLAGS = -g -framework IOKit

SRCS = fixedpoint.c smc_util.c smc_utils.c smc_desc.c smc_types.c

all: smc_util

.c.o:
	                $(CC) $(CFLAGS) -c $*.c


smc_util:	smc_util.o fixedpoint.o smc_util.o smc_utils.o  smc_desc.o smc_types.o reportfd.o

depend:
	                mkdep $(CFLAGS) $(SRCS)
clean:
	        -rm -f fixedpoint.o smc_util.o smc_utils.o smc_types.o reportfd.o smc_util 
