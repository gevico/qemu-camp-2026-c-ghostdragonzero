CC = gcc
CFLAGS = -Wall -g -O2 -fPIE

TARGET := 17_myfile
SRCS := 17_myfile.c
OBJS := $(SRCS:.c=.o)
#吧SRC中的c后缀改成o

all: $(TARGET)
	gcc -c $(SRCS)
	gcc $(OBJS) -o $(TARGET)


clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean