CC = gcc

CFLAGS = -g

LIBS = -lclearblade

SRCS = $(wildcard ./*.c)

OBJS = $(SRCS:.c=.o)

MAIN = start_adapter

all: $(MAIN)
	@echo Compile complete. Execute main by ./start_adapter

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

clean:
	$(RM) *.o start_adapter
