## 目标名称
PROJECT(main)

##最小版本限制
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 


##编译问题
INCLUDE_DIRECTORIES(inc)
ADD_COMPILE_OPTIONS(-g)

## 链接目录问题
#LINK_DIRECTORIES("/home/suweishuai/pro/test/cmake/cmake_mutil2/src/")

## 子目录问题
ADD_SUBDIRECTORY(utils)
ADD_SUBDIRECTORY(modules)

## main file 问题
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(main ${DIR_SRCS}  )


## 链接档问题
TARGET_LINK_LIBRARIES(main utils modules )
