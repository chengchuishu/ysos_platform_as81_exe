##最低版本号要求##
cmake_minimum_required (VERSION 2.8)

##project info##
set(EXE_NAME test_core)
project(${EXE_NAME})

#set compile flags
#添加-fPIC编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

##Enable C++11##
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

##LIB_DIR##
set(LIB_DIR "/usr/local/lib")
#set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(LIB_DIR "/home/kevin/cplus_ws/ysos_platform/core/trunk/main/framework/lib")

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

if(CONAN_LIBCXX STREQUAL "libstdc++11")
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
elseif(CONAN_LIBCXX STREQUAL "libstdc++")
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
endif()

##add inlude include_directories and link_libraries ##
include_directories(. /usr/local/include ../protect/include ../public/include)

##添加非标准的共享库搜索路径
link_directories(${LIB_DIR})

#链接库
#link_libraries(os_hal_package)

##查找当前目录下的所有源文件####并将名称保存到DIR_SRCS变量##
aux_source_directory(./src SRC_LIST)

##指定生成目标##
add_executable(${EXE_NAME} ${SRC_LIST})

##把目标文件与库文件进行链接
#target_link_libraries(${EXE_NAME} -lboost_unit_test_framework -lboost_log -lpthread -lboost_log_setup  -lboost_system -lboost_thread -los_hal_package -lcore_help_package -lboost_date_time -los_hal_package)
target_link_libraries(${EXE_NAME} boost_unit_test_framework boost_log pthread boost_log_setup boost_system boost_thread boost_date_time boost_serialization sys_framework_package protocol_help_package os_hal_package core_help_package)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}//linux/bin)