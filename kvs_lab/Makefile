SRCS = main.c
LIBSRCS = open.c close.c put.c get.c
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS_STATIC = -L. -lkvs
LIBS_DYNAMIC = -L. -lkvs -Wl,-rpath,.

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LSO = libkvs.so

all: static dynamic

# Static build
static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS_STATIC) -static

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)

# Dynamic build
dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LSO)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) $(LIBS_DYNAMIC)

$(LSO): $(LOBJS)
	$(CC) -shared -o $(LSO) $(LOBJS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LSO) $(TARG) $(TARG_DYNAMIC)
