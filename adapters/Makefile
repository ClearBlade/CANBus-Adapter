CC = gcc

CFLAGS = -g -Wall -Werror -std=c99

LIBS = -lclearblade

SRCS = $(wildcard ./*.c)

OBJS = $(SRCS_C:.c=.o)

MAIN = adapter

all: $(MAIN)
	@echo Compile complete. Execute main by ./adapter

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

clean:
	$(RM) *.o start_adapter
