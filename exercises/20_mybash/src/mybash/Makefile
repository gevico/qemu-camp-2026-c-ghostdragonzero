# src/mybash/Makefile

CC = gcc
CFLAGS = -Wall -I../../include

# 可执行文件名
TARGET := mybash
# 最终输出到 BINDIR（比如 ./bin/）
BINDIR ?= ./bin
# 中间文件目录
OBJDIR_PATH ?= ./obj
OBJDIR := $(OBJDIR_PATH)/mybash

# --- 修改点 1：补充库名 (-l) ---
# 这里的路径指向了库文件所在的目录
# -lmysed 会自动寻找 libmysed.a
LINKLIBS := -L../../obj/src/mysed -lmysed \
            -L../../obj/src/mywc -lmywc \
            -L../../obj/src/mytrans -lmytrans \
            -L../../obj/src/myfile -lmyfile

# 源文件
SRCS := main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

# 最终二进制路径
TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

# --- 修改点 2：使用正确的变量 $(LINKLIBS) ---
$(TARGET_PATH): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LINKLIBS)

# 2. 规则：编译 .c 到 .o
# 通用规则：将当前目录下的 %.c 编译到 $(OBJDIR)/%.o
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 3. 规则：创建目录 (BINDIR 和 OBJDIR)
# 使用 order-only prerequisite (|) 确保目录存在但不触发重编译
$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	@rm -rf $(OBJDIR)/*.o $(TARGET_PATH)