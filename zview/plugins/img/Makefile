STACKSIZE		= 64k
OPTIMISATION		= -O2 -fomit-frame-pointer -finline-functions
CPU			= -m68020-60
LIB			= -lshare -lldg

CFLAGS			= $(CPU) $(OPTIMISATION) -Wall -I../../../common -I../common

OBJ 			= imgldg.o xp32.o

PROGRAM 		= img.ldg

include ../../../common.mak
