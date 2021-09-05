ADD_EXECUTABLE(ooc_base_tst 
    main.cc
    test_ooc_base.cc
)

ADD_TEST(NAME ooc_base_tst COMMAND ooc_base_tst)

TARGET_LINK_LIBRARIES(ooc_base_tst 
    PUBLIC 
        gtest
        ooc_base
        ooc_config
)