#include "gtest/gtest.h"

extern "C" {
#include "ooc/ooc.h"
#include "ooc/malloc_analysis.h"
}

class OOC_BASE : public ::testing::Test {

protected:
    uint32_t m_memory_before_test;
    uint32_t m_memory_after_test;

    OOC_BASE():
    m_memory_before_test{0},
    m_memory_after_test{0}
    {
    }

    virtual ~OOC_BASE() {
    }

    virtual void SetUp() {
      m_memory_before_test = ooc_allocated_memory();
    }

    virtual void TearDown() {
        m_memory_after_test = ooc_allocated_memory();
        ASSERT_EQ(m_memory_before_test, m_memory_after_test) << "Test contains some memory leakage";
    }
};

TEST_F(OOC_BASE, check_not_object_if_object_with_is_a) {
    int not_an_object = 3;
    ASSERT_FALSE(IS_A(&not_an_object, Object));
}

TEST_F(OOC_BASE, check_object_if_object_with_is_a) {
    o_Object object = Object();
    ASSERT_TRUE(IS_A(object, Object));
    OOC_DELETE(object);
    ASSERT_FALSE(IS_A(object, Object));
    ASSERT_EQ(nullptr, object);
}

TEST_F(OOC_BASE, check_not_object_if_object_with_is_Object) {
    int not_an_object = 3;
    ASSERT_FALSE(ooc_isObject(&not_an_object));
}

TEST_F(OOC_BASE, check_object_if_object_with_is_Object) {
    o_Object object = Object();
    ASSERT_TRUE(ooc_isObject(object));
    OOC_DELETE(object);
    ASSERT_FALSE(ooc_isObject(object));
    ASSERT_EQ(nullptr, object);
}