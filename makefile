CC= gcc
AR= ar
CFLAGS= -Ix11_hash

SRCS= aes_helper.c blake.c bmw.c cubehash.c echo.c groestl.c jh.c keccak.c luffa.c shavite.c simd.c skein.c x11.c
OBJS= aes_helper.o blake.o bmw.o cubehash.o echo.o groestl.o jh.o keccak.o luffa.o shavite.o simd.o skein.o x11.o
STATIC_LIB= libx11hash.a
UTIL= x11hash

VPATH= x11_hash

util: $(STATIC_LIB)
	$(CC) $(CFLAGS) -c main.c
	$(CC) main.o $(STATIC_LIB) -o $(UTIL)

libx11hash.a: $(OBJS)
	$(AR) rcs $(STATIC_LIB) $(OBJS)

clean:
	rm -fr $(OBJS) a.out a.out.dSYM $(STATIC_LIB) main.o $(UTIL)
