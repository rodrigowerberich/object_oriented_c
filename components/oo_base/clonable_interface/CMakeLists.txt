CMAKE_MINIMUM_REQUIRED(VERSION 3.10)


ADD_LIBRARY(clonable_interface 
    STATIC
    src/clonable_interface.c
)

TARGET_INCLUDE_DIRECTORIES(clonable_interface
    PUBLIC
        inc
)

TARGET_LINK_LIBRARIES(clonable_interface 
    PUBLIC 
        ooc_config
        ooc_base
)

ADD_SUBDIRECTORY(tst)