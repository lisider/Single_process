#这是1层目录下的Makefile,

#root/dir/Makefile

#每个类似的目录下有一个

############################################################
# 编译 相关

CROSS_COMPILE =  

CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
CFLAGS= -g  -I$(DIR_INCLUDE)



############################################################
#目标

PHONY=clean
ALL = build_in.o


############################################################
# 文件夹相关

PWD:=$(shell pwd)
pes_parent_dir:=$(shell basename $(PWD))


exclude_dirs := 
dirs := $(shell find . -maxdepth 1 -type d)
dirs := $(basename $(patsubst ./%,%,$(dirs)))
dirs := $(filter-out $(exclude_dirs),$(dirs))
SUBDIRS := $(dirs)
SUBDIRS_ := $(addsuffix \/ ,$(dirs))


############################################################
# 下级目录的目标


#DIR_OBJ = $(addsuffix .a,$(addprefix lib,$(pes_parent_dir)))

#DIR_OBJ_PATH = $(join $(SUBDIRS_) , $(DIR_OBJ))


DIR_OBJ_PATH = $(addsuffix build_in.o,$(SUBDIRS_))



############################################################
# 文件 相关

CSRCS = $(wildcard *.c)  
COBJS = $(patsubst %.c, %, $(CSRCS))  
CPPSRCS = $(wildcard *.cpp)  
CPPOBJS += $(patsubst %.cpp, %, $(CPPSRCS))  

#OBJ = $(COBJS)
#OBJ += $(CPPOBJS)

OBJ = $(addsuffix .o,$(COBJS)) 
OBJ += $(addsuffix .o,$(CPPOBJS))


############################################################
# 目标 相关

all: $(ALL)

$(ALL): $(OBJ) $(SUBDIRS) 
	$(LD) -r -s -o $@ $(OBJ) $(DIR_OBJ_PATH) 


dir:
	#echo $(pes_parent_dir)
	echo $(DIR_OBJ_PATH)

PHONY += $(SUBDIRS)

# 目标 4 这是一个 多目标 适配 所有的 目录
$(SUBDIRS):
	make -C $@


%.o:%.c 
	$(CC) -c $^ -o $@ $(CFLAGS)

%.o:%.cpp 
	$(CPP) -c $^ -o $@ $(CFLAGS)

clean:
	rm  $(OBJ)  $(ALL) -rf
	$(foreach i,$(SUBDIRS),$(shell make -C $(i) clean))

.PHONY:$(PHONY)
