PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
INCLUDE_DIRECTORIES(/usr/local/include/)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -Wall -g -fpermissive")

ADD_EXECUTABLE(simple_server simple_server.cpp
zsocket_util.cpp
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
zmutex_guard.hpp
zconnection.cpp
)
TARGET_LINK_LIBRARIES(simple_server
    pthread 
    boost_thread 
    boost_system
    protobuf
    )

ADD_EXECUTABLE(mini_web_server mini_web_server.cpp
zmini_web_server.cpp
zthread.cpp
zsocket.cpp
zsocket_util.cpp
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
zprocess_util.cpp
zmutex.hpp
zmutex_guard.hpp
zconnection.cpp
zthread.hpp
)

TARGET_LINK_LIBRARIES(mini_web_server
    pthread 
    boost_thread 
    boost_system
    protobuf
    )

ADD_EXECUTABLE(proxy_server proxy_server.cpp
zproxy_server.cpp
zproxy_client.cpp
zthread.cpp
zsocket.cpp
zsocket_util.cpp
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
zprocess_util.cpp
zmutex.hpp
zmutex_guard.hpp
zconnection.cpp
zthread.hpp
)

TARGET_LINK_LIBRARIES(proxy_server
    pthread 
    boost_thread 
    boost_system
    protobuf
    )

ADD_EXECUTABLE(work_server work_server.cpp
zwork_server.cpp
zwork_client.cpp
zthread.cpp
zsocket.cpp
zsocket_util.cpp
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
zprocess_util.cpp
zmutex.hpp
zmutex_guard.hpp
zconnection.cpp
zthread.hpp
)

TARGET_LINK_LIBRARIES(work_server
    pthread 
    boost_thread 
    boost_system
    protobuf
    )
