CFLAGS := -Wall -Wextra -c -lm

LDFLAGS := -lm

CC := gcc

OBJ = $(shell for i in */*.c ; do echo $${i%.c}.o ; done )

AR := ar

LIBNAME = gc

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so

DYNCC = CC="$(CC) -fpic"


all:

	$(MAKE) static
	$(MAKE) cleanobj
	$(MAKE) dynamic


static: $(OBJ)

	$(MAKE) static_link
	$(MAKE) static_create


dynwrap: $(OBJ)

	
dynamic: 

	$(MAKE) $(DYNCC) dynwrap
	$(MAKE) dynamic_link
	$(MAKE) dynamic_create 


static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)


dynamic_link:

	$(CC) -shared -Wl,-soname,$(DYNLIB) -o $(DYNLIB) $(OBJ)


static_create: 

	$(CC) -o static_driver ../tests/driver.c $(STATLIB) $(LDFLAGS)


dynamic_create:

	$(CC) ../tests/driver.c -L. -l$(LIBNAME) -o dynamic_driver $(LDFLAGS)


exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) *driver log stringmath

