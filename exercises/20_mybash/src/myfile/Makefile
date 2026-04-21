# src/myfile/Makefile

CC = gcc
CFLAGS = -Wall -I../../include -g -fPIE

# 库名称
LIBNAME := myfile
# 静态库输出名：libmyfile.a
LIB := lib$(LIBNAME).a
# 最终库输出目录（比如 ./obj/src/myfile/）
OBJDIR_PATH ?= ./obj
OBJDIR := $(OBJDIR_PATH)/src/$(LIBNAME)
# 最终 .a 文件路径
LIB_PATH := $(OBJDIR)/$(LIB)

# 源文件
SRCS := myfile.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

all: $(LIB_PATH)

# TODO: 在这里添加你的代码
$(OBJDIR):
	mkdir -p $@

# 2. 规则：打包静态库
# 依赖是所有的 .o 文件
$(LIB_PATH): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# 3. 规则：编译 .c 到 .o
# 通用规则：将当前目录下的 %.c 编译到 $(OBJDIR)/%.o
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -rf $(OBJDIR)/*.o $(LIB_PATH)