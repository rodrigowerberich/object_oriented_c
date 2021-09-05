#include "gtest/gtest.h"

extern "C" {
#include "ooc/ooc.h"
#include "ooc/malloc_analysis.h"
#include "o_mock_clonable.h"
}

class ClonableInterfaceTst : public ::testing::Test {

protected:
    uint32_t m_memory_before_test;
    uint32_t m_memory_after_test;

    ClonableInterfaceTst():
    m_memory_before_test{0},
    m_memory_after_test{0}
    {
        // Necessary to pre-allocate the mock-clonable metaclass data and avoid any problems in the autotesters
        MockClonableClass();
    }

    virtual ~ClonableInterfaceTst() {
    }

    virtual void SetUp() {
      m_memory_before_test = ooc_allocated_memory();
    }

    virtual void TearDown() {
        m_memory_after_test = ooc_allocated_memory();
        ASSERT_EQ(m_memory_before_test, m_memory_after_test) << "Test contains some memory leakage";
    }
};

TEST_F(ClonableInterfaceTst, mock_class_creation) {
    o_MockClonable o_mock_clonable = MockClonable(3);
    OOC_DELETE(o_mock_clonable);
}

TEST_F(ClonableInterfaceTst, interface_test) {
    o_MockClonable o_mock_clonable = MockClonable(3);
    CHECK_INTERFACE(clone_method, o_mock_clonable, M_CLONABLE_CLONE);
    ASSERT_NE(nullptr, clone_method);
    OOC_DELETE(o_mock_clonable);
}

TEST_F(ClonableInterfaceTst, using_cloning) {
    int expected_value = 8;
    o_MockClonable o_mock_clonable = MockClonable(expected_value);
    o_MockClonable o_mock_clonable_clone = OOC_CLONE(o_mock_clonable);
    ASSERT_EQ(MockClonable_getNumber(o_mock_clonable), MockClonable_getNumber(o_mock_clonable_clone));
    ASSERT_EQ(expected_value, MockClonable_getNumber(o_mock_clonable_clone));
    OOC_DELETE(o_mock_clonable);
    OOC_DELETE(o_mock_clonable_clone);
}

TEST_F(ClonableInterfaceTst, using_safe_cloning) {
    int expected_value = 8;
    o_MockClonable o_mock_clonable = MockClonable(expected_value);
    // For oo objects the second argument is ingnored
    o_MockClonable o_mock_clonable_clone = OOC_CLONE_S(o_mock_clonable, sizeof(o_mock_clonable));
    ASSERT_EQ(MockClonable_getNumber(o_mock_clonable), MockClonable_getNumber(o_mock_clonable_clone));
    ASSERT_EQ(expected_value, MockClonable_getNumber(o_mock_clonable_clone));
    OOC_DELETE(o_mock_clonable);
    OOC_DELETE(o_mock_clonable_clone);
}

TEST_F(ClonableInterfaceTst, using_cloning_c) {
    int expected_value = 8;
    int* p_copy_value = OOC_CLONE_C(&expected_value, int);
    ASSERT_EQ(expected_value, *p_copy_value);
    p_copy_value = (int*) ooc_delete(p_copy_value);
}

TEST_F(ClonableInterfaceTst, using_safe_cloning_c) {
    int expected_value = 8;
    int* p_copy_value = (int*) OOC_CLONE_S(&expected_value, sizeof(expected_value));
    ASSERT_EQ(expected_value, *p_copy_value);
    p_copy_value = (int*) ooc_delete(p_copy_value);
}