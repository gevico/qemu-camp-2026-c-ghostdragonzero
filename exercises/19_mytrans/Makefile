CC = gcc
CFLAGS = -Wall -g -O2


TARGET = 19_mytrans
SRCS = 19_mytrans.c mytrans.c myhash.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^  -o $@

# 编译规则：将任意 .c 文件编译成对应的 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -g -o $@
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
