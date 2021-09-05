#include "gtest/gtest.h"

extern "C" {
#include "ooc/malloc.h"
#include "ooc/malloc_analysis.h"
#include <stdbool.h>
}

TEST(OOC_BASE, simple_malloc_and_free) {
	auto memory_before_malloc = ooc_allocated_memory();
	int* p_i = (int*) ooc_malloc(sizeof(int));
	auto memory_after_malloc = ooc_allocated_memory();
	ASSERT_GT(memory_after_malloc, memory_before_malloc) << "Memory allocated should be greater after a malloc";
	
	*p_i = 3;
	ASSERT_EQ(3, *p_i);

	ooc_free(p_i);
	auto memory_after_free = ooc_allocated_memory();
	ASSERT_EQ(memory_after_free, memory_before_malloc) << "Memory not being correclty freed";
}

TEST(OOC_BASE, simple_calloc_and_free) {
	auto memory_before_calloc = ooc_allocated_memory();
	int* p_vector =  (int*) ooc_calloc(10, sizeof(int));
	auto memory_after_calloc = ooc_allocated_memory();
	ASSERT_GT(memory_after_calloc, memory_before_calloc) << "Memory allocated should be greater after a calloc";

	ASSERT_NE(nullptr, p_vector);
	for(int i=0; i<10; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	ooc_free(p_vector);
	auto memory_after_free = ooc_allocated_memory();
	ASSERT_EQ(memory_after_free, memory_before_calloc) << "Memory not being correclty freed";
}

TEST(OOC_BASE, realloc_to_bigger) {
	auto memory_before_calloc = ooc_allocated_memory();
	int* p_vector =  (int*) ooc_calloc(2, sizeof(int));
	auto memory_after_calloc = ooc_allocated_memory();
	ASSERT_GT(memory_after_calloc, memory_before_calloc) << "Memory allocated should be greater after a calloc";

	for(int i=0; i<2; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	p_vector =  (int*) ooc_realloc(p_vector, 5*sizeof(int));
	auto memory_after_realloc = ooc_allocated_memory();
	ASSERT_GT(memory_after_realloc, memory_after_calloc) << "Memory allocated should be greater after realloc'ing to a bigger size";

	for(int i=0; i<5; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	ooc_free(p_vector);
	auto memory_after_free = ooc_allocated_memory();
	ASSERT_EQ(memory_after_free, memory_before_calloc) << "Memory not being correclty freed";
}

TEST(OOC_BASE, realloc_to_smaller) {
	auto memory_before_calloc = ooc_allocated_memory();
	int* p_vector =  (int*) ooc_calloc(50, sizeof(int));
	auto memory_after_calloc = ooc_allocated_memory();
	ASSERT_GT(memory_after_calloc, memory_before_calloc) << "Memory allocated should be greater after a calloc";

	for(int i=0; i<50; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	p_vector =  (int*) ooc_realloc(p_vector, 10*sizeof(int));
	auto memory_after_realloc = ooc_allocated_memory();
	ASSERT_LT(memory_after_realloc, memory_after_calloc) << "Memory allocated should be lesser after realloc'ing to a smaller size";


	for(int i=0; i<10; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	ooc_free(p_vector);
	auto memory_after_free = ooc_allocated_memory();
	ASSERT_EQ(memory_after_free, memory_before_calloc) << "Memory not being correclty freed";
}

TEST(OOC_BASE, realloc_to_same) {
	auto memory_before_calloc = ooc_allocated_memory();
	int* p_vector =  (int*) ooc_calloc(50, sizeof(int));
	auto memory_after_calloc = ooc_allocated_memory();
	ASSERT_GT(memory_after_calloc, memory_before_calloc) << "Memory allocated should be greater after a calloc";

	for(int i=0; i<50; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	p_vector =  (int*) ooc_realloc(p_vector, 50*sizeof(int));
	auto memory_after_realloc = ooc_allocated_memory();
	ASSERT_EQ(memory_after_realloc, memory_after_calloc) << "Memory allocated should be the same after realloc'ing to the same size";


	for(int i=0; i<50; i++){
		ASSERT_NE(nullptr, &p_vector[i]);
	}

	ooc_free(p_vector);
	auto memory_after_free = ooc_allocated_memory();
	ASSERT_EQ(memory_after_free, memory_before_calloc) << "Memory not being correclty freed";
}