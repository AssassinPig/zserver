PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
INCLUDE_DIRECTORIES(/usr/local/include/)
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main pthread)
TARGET_LINK_LIBRARIES(main boost_thread)

ADD_EXECUTABLE(thread_group thread_group.cpp)
TARGET_LINK_LIBRARIES(thread_group pthread)
TARGET_LINK_LIBRARIES(thread_group boost_thread)

ADD_EXECUTABLE(condition condition.cpp)
TARGET_LINK_LIBRARIES(condition pthread)
TARGET_LINK_LIBRARIES(condition boost_thread)

ADD_EXECUTABLE(interrupt interrupt.cpp)
TARGET_LINK_LIBRARIES(interrupt pthread)
TARGET_LINK_LIBRARIES(interrupt boost_thread)
