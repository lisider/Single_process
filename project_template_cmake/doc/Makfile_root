#这个是顶层目录 下的 Makefile

# root/Makefile


############################################################
# 编译 相关

CROSS_COMPILE =  

export DIR_INCLUDE=$(shell pwd)/inc
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
CFLAGS= -g  -I$(DIR_INCLUDE)
LDFLAGS = 


LIBS = sqlite3
LIBS += pthread

LDLIBS  = $(addprefix -l,$(LIBS))

############################################################
#目标
ALL = main

PHONY=clean

############################################################

# 文件夹相关
exclude_dirs := data  doc  inc 
dirs := $(shell find . -maxdepth 1 -type d)
dirs := $(basename $(patsubst ./%,%,$(dirs)))
dirs := $(filter-out $(exclude_dirs),$(dirs))
SUBDIRS := $(dirs)
SUBDIRS_ := $(addsuffix \/ ,$(dirs))

# 普通文件相关

CSRCS = $(wildcard *.c)  
COBJS = $(patsubst %.c, %, $(CSRCS))  
CPPSRCS = $(wildcard *.cpp)  
CPPOBJS += $(patsubst %.cpp, %, $(CPPSRCS))  

#OBJ = $(COBJS)
#OBJ += $(CPPOBJS)

# 当前文件夹内的目标

OBJ = $(addsuffix .o,$(COBJS)) 
OBJ += $(addsuffix .o,$(CPPOBJS))


# 下级目录的目标

#DIR_OBJ = $(addsuffix .a,$(addprefix lib,$(SUBDIRS)))

#DIR_OBJ_PATH = $(join $(SUBDIRS_) , $(DIR_OBJ))



DIR_OBJ_PATH = $(addsuffix build_in.o , $(SUBDIRS_))

############################################################

# 默认目标
all: $(ALL)

# 目标 1
$(ALL): $(OBJ) $(SUBDIRS)
	$(CC) $(OBJ) $(DIR_OBJ_PATH) -o $@ $(LDFLAGS) $(LDLIBS)
# 目标 2
dir:
	@echo $(SUBDIRS_)
	@echo $(DIR_OBJ)
	@echo $(DIR_OBJ_PATH)
	@echo $(DIR_INCLUDE)

# 目标 3
libs:
	@echo $(LDLIBS)

PHONY += $(SUBDIRS)

# 目标 4 这是一个 多目标 适配 所有的 目录
$(SUBDIRS):
	make -C $@

# 目标 5 这是一个 多目标 适配当前目录下所有 的 .c  文件

%.o:%.c 
	$(CC) -c $^ -o $@ $(CFLAGS)

# 目标 6 这是一个 多目标 适配当前目录下所有 的 .cpp  文件

%.o:%.cpp 
	$(CPP) -c $^ -o $@ $(CFLAGS)

clean:
	rm  $(OBJ) $(ALL)  -rf
	$(foreach i,$(SUBDIRS),$(shell make -C $(i) clean))

############################################################

.PHONY:$(PHONY)
