STACKSIZE		= 64k
OPTIMISATION		= -O2 -fomit-frame-pointer -finline-functions
CPU			= -m68020-60
LIB			= -lshare -ltiff -ljpeg -lldg -lz -llzma -lm

CFLAGS			= $(CPU) $(OPTIMISATION) -Wall -I. -I../../../common -I../common

OBJ			= tiffldg.o

PROGRAM 		= tiff.ldg

include ../../../common.mak
