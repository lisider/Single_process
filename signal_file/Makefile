
##################################################################
#编译器
CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc
CPP=$(CROSS_COMPILE)g++


##################################################################
#编译选项

# TODO
CFLAGS= -g -I.

#TODO
LDFLAGS = -L.

#TODO
LIBS = pthread
#LIBS += sqlite3
LDLIBS  = $(addprefix -l,$(LIBS))

#TODO

RUNTIME = -Wl,-rpath,.


ALLFLAG = $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(RUNTIME)


##################################################################
#筛选目标

CSRCS = $(wildcard *.c)  
COBJS = $(patsubst %.c, %, $(CSRCS))  
CPPSRCS = $(wildcard *.cpp)  
CPPOBJS += $(patsubst %.cpp, %, $(CPPSRCS))  

OBJ = $(COBJS)
OBJ += $(CPPOBJS)


#目标及依赖

all: $(OBJ)

%:%.c 
	$(CC) $^ -o $@ $(ALLFLAG)

%:%.cpp 
	$(CPP) $^ -o $@ $(ALLFLAG)

PHONY = clean
clean:
	rm $(OBJ) -f

#伪目标

.PHONY:$(PHONY)
