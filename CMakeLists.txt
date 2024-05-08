cmake_minimum_required(VERSION 2.8)
if (NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release) 
endif()
find_program(CCACHE_PROGRAM ccache)  #使用ccache加速编译
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_STANDARD_REQUIRED ON) #必须支持指定的c++标准
set(CMAKE_CXX_EXTENSIONS OFF)  #关闭gcc扩展
#以上几句直接抄就行

project(app)  #每个相对的顶级cmake都要写一个，意思就是最顶级的要写一个，下面每个模块的顶级cmake也要写一个
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) #程序生成位置, PROJECT_SOURCE_DIR是当前项目的顶级路径

include_directories(
    ${PROJECT_SOURCE_DIR}/thirdparty
    ${PROJECT_SOURCE_DIR}/include
) #头文件路径


file(GLOB_RECURSE SRC    
	./main.cpp
	../thirdparty/ConvertUTF.cc
) #递归寻找

add_executable(${PROJECT_NAME} ${SRC})   #生成可执行程序one

target_link_libraries(${PROJECT_NAME} mysqlclient)  #指定要链接的库名

