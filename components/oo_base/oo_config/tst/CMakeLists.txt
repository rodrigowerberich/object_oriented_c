ADD_EXECUTABLE(ooc_malloc_tst 
    main.cc
    test_ooc_malloc.cc
)

ADD_TEST(NAME ooc_malloc_tst COMMAND ooc_malloc_tst)

TARGET_LINK_LIBRARIES(ooc_malloc_tst 
    PUBLIC 
        gtest
        ooc_config
)