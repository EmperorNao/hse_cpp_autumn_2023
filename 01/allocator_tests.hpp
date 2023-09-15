#include "gtest/gtest.h"

#include "allocator.hpp"


class TestAllocator: public ::testing::Test {

protected:
    void setUp() {}
    void tearDown() {}

    Allocator allocator;
};