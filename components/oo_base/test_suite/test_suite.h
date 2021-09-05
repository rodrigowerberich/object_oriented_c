#ifndef TEST_SUITE_H__
#define TEST_SUITE_H__

#include <lua_system_def.h>
#include <lua_assert.h>

#ifdef ESP_32
#include <esp_system.h>
#endif

#ifdef ESP_32
#define UNIT_TEST(test_name_)\
    static bool test_name_();\
    static bool test_name_##_tu(){\
        NOTIFY("Starting test of " #test_name_);\
        size_t heap1 = esp_get_free_heap_size();\
        if (test_name_()){\
            NOTIFY(#test_name_ " ---------- Test OK!");\
        }else{\
            ERROR_NOTIFY(#test_name_ " ---------- Test Failed!");\
        }\
        size_t heap2 = esp_get_free_heap_size();\
        ASSERT_NOTIFY_F(heap1 == heap2, false, #test_name_ " has a memory leak of %d bytes!", heap1-heap2);\
        return true;\
    }
#else
#define UNIT_TEST(test_name_)\
    static bool test_name_();\
    static bool test_name_##_tu(){\
        NOTIFY("Starting test of " #test_name_);\
        if (test_name_()){\
            NOTIFY(#test_name_ " Test OK!");\
        }else{\
            ERROR_NOTIFY(#test_name_ " Test Failed!");\
        }\
        return true;\
    }
#endif

#define RUN_TEST(test_name_) test_name_##_tu();

#endif //TEST_SUITE_H__