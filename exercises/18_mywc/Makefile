CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = 18_mywc
SRCS = 18_mywc.c mywc.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^  -o $@

# 编译规则：将任意 .c 文件编译成对应的 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -g -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
