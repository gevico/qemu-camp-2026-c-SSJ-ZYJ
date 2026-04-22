# src/mybash/Makefile

CC = gcc
CFLAGS = -Wall -I../../include
LDFLAGS = -lmywc -lmysed -lmytrans -lmyfile

# 可执行文件名
TARGET := 20_mybash
# 最终输出到上级目录的上级（exercises/20_mybash）
BINDIR ?= ../..
# 中间文件目录（用 OBJDIR 变量）
OBJDIR ?= ../../obj
LINKDIRS ?= -L$(OBJDIR)

# 源文件
SRCS := main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

# 最终二进制路径
TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_PATH): $(OBJS) 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(LINKDIRS) $(LDFLAGS) -o $@

clean:
	@rm -rf $(OBJDIR)/*.o $(TARGET_PATH)