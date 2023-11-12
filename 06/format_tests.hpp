#pragma once

#include "gtest/gtest.h"

#include "format.hpp"


class TestFormat: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};

TEST_F(TestFormat, testWithoutFormatingFormat) {
    ASSERT_EQ("test", format("test", 1));
}

TEST_F(TestFormat, testSignleFormat) {
    ASSERT_EQ("test 0", format("test {0}", 0));
}

TEST_F(TestFormat, testSequnceFormat) {
    ASSERT_EQ("test 1 hello -1", format("test {0} {1} {2}", 1, "hello", -1));
}

TEST_F(TestFormat, testNonAscendingFormat) {
    ASSERT_EQ("test -1 hello 1", format("test {2} {1} {0}", 1, "hello", -1));
}

TEST_F(TestFormat, testRepeatingFormat) {
    ASSERT_EQ("test 1,1,1", format("test {0},{0},{0}", 1, "hello", "-1"));
}

TEST_F(TestFormat, testBraceExceptionFormat) {
    ASSERT_THROW(format("{}", 0), FormatBraseExeption);
    ASSERT_NO_THROW(format("{0}", 0));
    ASSERT_THROW(format("{{0}", 0), FormatBraseExeption);
    ASSERT_THROW(format("{0}}", 0), FormatBraseExeption);
    ASSERT_THROW(format("{{}}", 0), FormatBraseExeption);
    ASSERT_THROW(format("{", 0), FormatBraseExeption);
    ASSERT_THROW(format("}", 0), FormatBraseExeption);
    ASSERT_THROW(format("{0} {", 0), FormatBraseExeption);
    ASSERT_THROW(format("{0} }", 0), FormatBraseExeption);
    ASSERT_THROW(format("{0} {}", 0), FormatBraseExeption);
}

TEST_F(TestFormat, testArgumentNumberExceptionFormat) {
    ASSERT_NO_THROW(format("{0}", 0));
    ASSERT_THROW(format("{-1}", 0), FormatArgumentNumberException);
    ASSERT_THROW(format("{1}", 0), FormatArgumentNumberException);
    ASSERT_THROW(format("{0} {2}", 0, 1), FormatArgumentNumberException);
}