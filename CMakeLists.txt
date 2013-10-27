PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
INCLUDE_DIRECTORIES(/usr/local/include/)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -Wall -g")

ADD_EXECUTABLE(main main.cpp
zthread_module.cpp
zclient.cpp
zconfig.cpp
zepoll.cpp
zlog.cpp
zpacket.cpp
zserver.cpp
zstream.cpp
zworld.cpp
zexample_module.cpp
zthread_util.hpp
zmutex.hpp
zconnection.cpp
)
TARGET_LINK_LIBRARIES(main pthread boost_thread)
