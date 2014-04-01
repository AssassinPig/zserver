PROJECT(zclient)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -Wall -g -fpermissive")
#AUX_SOURCE_DIRECTORY(. DIR_SRCS)

INCLUDE_DIRECTORIES(../)
INCLUDE_DIRECTORIES(/usr/local/include/)

ADD_EXECUTABLE(main main.cpp
    zclient.cpp
    ../zsocket.cpp
    ../zsocket_util.cpp
    )

#TARGET_LINK_LIBRARIES(main pthread)
#TARGET_LINK_LIBRARIES(main boost_thread)
