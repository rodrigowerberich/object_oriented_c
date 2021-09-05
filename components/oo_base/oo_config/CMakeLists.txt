CMAKE_MINIMUM_REQUIRED(VERSION 3.10)


ADD_LIBRARY(ooc_config 
    STATIC
    src/base_malloc.c
)

TARGET_INCLUDE_DIRECTORIES(ooc_config
    PUBLIC
        inc
)

ADD_SUBDIRECTORY(tst)