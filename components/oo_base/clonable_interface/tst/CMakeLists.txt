ADD_EXECUTABLE(clonable_interface_tst 
    main.cc
    mock/o_mock_clonable.c
    test_clonable_interface.cc
)

ADD_TEST(NAME clonable_interface_tst COMMAND clonable_interface_tst)

TARGET_INCLUDE_DIRECTORIES(clonable_interface_tst
    PUBLIC
        .
        mock
)

TARGET_LINK_LIBRARIES(clonable_interface_tst 
    PUBLIC 
        gtest
        ooc_base
        ooc_config
        clonable_interface
)