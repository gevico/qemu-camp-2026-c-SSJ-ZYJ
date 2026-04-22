# =============================================
# 主 Makefile
# 功能：
#   - mybash：生成二进制，放到顶级目录
#   - 其他模块（mysed, myfile, mywc, mytrans）：生成静态库 .a，放到 obj/xxx/，.o 放到 obj/xxx/（或 out/，但建议统一）
#   - 所有子模块 Makefile 应支持 OBJDIR 和 BINDIR 参数
# =============================================

PWD := $(shell pwd)
OBJDIR ?= $(PWD)/obj
BINDIR ?= $(PWD)/bin

# 所有子模块目录（静态库：生成 .a）
SUBDIRS := \
	src/mywc \
	src/myfile \
	src/mysed \
	src/mytrans

# 默认目标：构建 mybash（依赖其他库）
all: $(SUBDIRS) mybash

# 通用规则：构建每个子模块（静态库）
$(SUBDIRS):
	@mkdir -p $(OBJDIR)
	@$(MAKE) -C $@ OBJDIR=$(OBJDIR)

# 构建 mybash（可执行文件，依赖上面的库）
mybash: $(SUBDIRS)
	@mkdir -p $(OBJDIR)
	@$(MAKE) -C src/mybash OBJDIR=$(OBJDIR) BINDIR=$(PWD)

# 清理所有生成的文件
clean:
	@for dir in $(SUBDIRS) src/mybash; do \
		$(MAKE) -C $$dir clean OBJDIR=$(OBJDIR); \
	done
	@rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all $(SUBDIRS) mybash clean