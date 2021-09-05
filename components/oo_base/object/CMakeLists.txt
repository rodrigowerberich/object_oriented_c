CMAKE_MINIMUM_REQUIRED(VERSION 3.10)


ADD_LIBRARY(ooc_base 
    STATIC
    src/ooc.c
)

TARGET_INCLUDE_DIRECTORIES(ooc_base
    PUBLIC
        inc
)

TARGET_LINK_LIBRARIES(ooc_base 
    PUBLIC 
        ooc_config
)

ADD_SUBDIRECTORY(tst)