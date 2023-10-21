#pragma once

#include "gtest/gtest.h"

#include "error.hpp"


class TestError: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};


TEST_F(TestError, testAndError) {
    ASSERT_EQ(Error::NoError && Error::NoError, Error::NoError);
    ASSERT_EQ(Error::NoError && Error::CorruptedArchive, Error::CorruptedArchive);
    ASSERT_EQ(Error::CorruptedArchive && Error::NoError, Error::CorruptedArchive);
    ASSERT_EQ(Error::CorruptedArchive && Error::CorruptedArchive, Error::CorruptedArchive);
    ASSERT_EQ(Error::NoError && Error::CorruptedArchive && Error::CorruptedArchive, Error::CorruptedArchive);
}