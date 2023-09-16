#include <limits>

#include "gtest/gtest.h"

#include "allocator.hpp"


class TestAllocator: public ::testing::Test {

protected:
    Allocator allocator;

    void setUp() { allocator = Allocator(); }
    void tearDown() { allocator.~Allocator(); }

};


TEST_F(TestAllocator, testEmptyAllocator) {
    ASSERT_EQ(nullptr, allocator.alloc(1));
}

TEST_F(TestAllocator, testAllocatorAlloc) {
    allocator.makeAllocator(10);
    ASSERT_NE(nullptr, allocator.alloc(10));
}

TEST_F(TestAllocator, testAllocatorAllocBig) {
    unsigned long bigNumber = std::numeric_limits<int>::max();
    allocator.makeAllocator(bigNumber + 1);
    ASSERT_NE(nullptr, allocator.alloc(bigNumber));
}

TEST_F(TestAllocator, testAllocatorAllocChunks) {
    allocator.makeAllocator(10);
    allocator.alloc(5);
    ASSERT_NE(nullptr, allocator.alloc(5));
}

TEST_F(TestAllocator, testAllocatorAllocOverflow) {
    allocator.makeAllocator(10);
    allocator.alloc(10);
    ASSERT_EQ(nullptr, allocator.alloc(1));
}

TEST_F(TestAllocator, testAllocatorReset) {
    allocator.makeAllocator(10);
    allocator.alloc(10);
    allocator.reset();
    ASSERT_NE(nullptr, allocator.alloc(10));
}

TEST_F(TestAllocator, testAllocatorResetChunks) {
    allocator.makeAllocator(10);
    allocator.alloc(10);
    allocator.reset();
    allocator.alloc(5);
    ASSERT_NE(nullptr, allocator.alloc(5));
}

TEST_F(TestAllocator, testAllocatorRecreationIncreasing) {
    allocator.makeAllocator(10);
    allocator.alloc(10);
    allocator.makeAllocator(15);
    ASSERT_NE(nullptr, allocator.alloc(15));
}

TEST_F(TestAllocator, testAllocatorRecreationDecreasing) {
    allocator.makeAllocator(10);
    allocator.alloc(10);
    allocator.makeAllocator(5);
    ASSERT_EQ(nullptr, allocator.alloc(15));
}