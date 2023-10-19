#pragma once

#include "gtest/gtest.h"

#include "bigint.hpp"


class TestBigInt: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};


TEST_F(TestBigInt, testEqualityBigInt) {
    ASSERT_EQ(BigInt(1), BigInt(1));
    ASSERT_EQ(BigInt(1234567), BigInt(1234567));
    ASSERT_NE(BigInt(1234567), BigInt(1234568));
    ASSERT_NE(BigInt(1), BigInt(0));
    ASSERT_NE(BigInt(-1), BigInt(0));
    ASSERT_NE(BigInt(-1), BigInt(1));
}

TEST_F(TestBigInt, testEmptyConstructorBigInt) {
    ASSERT_EQ(BigInt(), BigInt(0));
}

TEST_F(TestBigInt, testStringConstructorBigInt) {
    ASSERT_EQ(BigInt("0"), BigInt(0));
    ASSERT_EQ(BigInt("1"), BigInt(1));
    ASSERT_EQ(BigInt("1234567"), BigInt(1234567));
    ASSERT_NE(BigInt("1234567"), BigInt(1234568));
    ASSERT_EQ(BigInt("+1"), BigInt(1));
    ASSERT_EQ(BigInt("-1"), BigInt(-1));
    ASSERT_EQ(BigInt("-1"), BigInt(-1));
}

TEST_F(TestBigInt, testToStringBigInt) {
    ASSERT_EQ(BigInt("0").toString(), "0");
    ASSERT_EQ(BigInt("-1").toString(), "-1");
    ASSERT_EQ(BigInt("9999999999999999").toString(), "9999999999999999");
    ASSERT_EQ(BigInt("-9999999999999999").toString(), "-9999999999999999");
}

TEST_F(TestBigInt, testAdditionBigInt) {
    ASSERT_EQ(BigInt("0") + BigInt("1"), BigInt("1"));
    ASSERT_EQ(BigInt("-1") + BigInt("1"), BigInt("0"));
    ASSERT_EQ(BigInt("-1") + BigInt("-1"), BigInt("-2"));
    ASSERT_EQ(BigInt("-1234567") + BigInt("1234567"), BigInt("0"));
    ASSERT_EQ(BigInt("12340") + BigInt("12340"), BigInt("24680"));
    ASSERT_EQ(BigInt("9999999999999999") + BigInt("9999999999999999"), BigInt("19999999999999998"));
}

TEST_F(TestBigInt, testSubtractionBigInt) {
    ASSERT_EQ(BigInt("0") - BigInt("1"), BigInt("-1"));
    ASSERT_EQ(BigInt("1") - BigInt("1"), BigInt("0"));
    ASSERT_EQ(BigInt("-1") - BigInt("1"), BigInt("-2"));
    ASSERT_EQ(BigInt("-1") - BigInt("-1"), BigInt("0"));
    ASSERT_EQ(BigInt("1234567") - BigInt("1234567"), BigInt("0"));
    ASSERT_EQ(BigInt("12340") - BigInt("-12340"), BigInt("24680"));
    ASSERT_EQ(BigInt("-12340") - BigInt("-12340"), BigInt("0"));
    ASSERT_EQ(BigInt("9999999999999999") - BigInt("9999999999999999"), BigInt("0"));
}

TEST_F(TestBigInt, testMultiplicationBigInt) {
    ASSERT_EQ(BigInt("0") * BigInt("1"), BigInt("0"));
    ASSERT_EQ(BigInt("123") * BigInt("10"), BigInt("1230"));
    ASSERT_EQ(BigInt("-1") * BigInt("123"), BigInt("-123"));
    ASSERT_EQ(BigInt("-1") * BigInt("-1"), BigInt("1"));
    ASSERT_EQ(BigInt("1234567") * BigInt("1234567"), BigInt("1524155677489"));
    ASSERT_EQ(BigInt("1234567") * BigInt("-1234567"), BigInt("-1524155677489"));
    ASSERT_EQ(BigInt("123456789") * BigInt("11"), BigInt("1358024679"));
}

TEST_F(TestBigInt, testAdditionIntBigInt) {
    ASSERT_EQ(BigInt("0") + 1, BigInt("1"));
    ASSERT_EQ(BigInt("-1") + 1, BigInt("0"));
    ASSERT_EQ(BigInt("-1") + (-1), BigInt("-2"));
    ASSERT_EQ(BigInt("-1234567") + 1234567, BigInt("0"));
    ASSERT_EQ(BigInt("12340") + 12340, BigInt("24680"));
    ASSERT_EQ(BigInt("999999999") + 999999999, BigInt("1999999998"));
}

TEST_F(TestBigInt, testSubtractionIntBigInt) {
    ASSERT_EQ(BigInt("0") - 1, BigInt("-1"));
    ASSERT_EQ(BigInt("1") - 1, BigInt("0"));
    ASSERT_EQ(BigInt("-1") - 1, BigInt("-2"));
    ASSERT_EQ(BigInt("-1") - (-1), BigInt("0"));
    ASSERT_EQ(BigInt("1234567") - 1234567, BigInt("0"));
    ASSERT_EQ(BigInt("12340") - (-12340), BigInt("24680"));
    ASSERT_EQ(BigInt("-12340") - (-12340), BigInt("0"));
}

TEST_F(TestBigInt, testMultiplicationIntBigInt) {
    ASSERT_EQ(BigInt("0") * 1, BigInt("0"));
    ASSERT_EQ(BigInt("123") * 10, BigInt("1230"));
    ASSERT_EQ(BigInt("-1") * 123, BigInt("-123"));
    ASSERT_EQ(BigInt("-1") * -1, BigInt("1"));
    ASSERT_EQ(BigInt("1234567") * 1234567, BigInt("1524155677489"));
    ASSERT_EQ(BigInt("1234567") * -1234567, BigInt("-1524155677489"));
    ASSERT_EQ(BigInt("123456789") * 11, BigInt("1358024679"));
}

TEST_F(TestBigInt, testUnaryMinusBigInt) {
    ASSERT_EQ(BigInt("0"), -BigInt("0"));
    ASSERT_EQ(BigInt("-1"), -BigInt("1"));
    ASSERT_EQ(BigInt("1"), -BigInt("-1"));
    ASSERT_NE(BigInt("-1"), -BigInt("-1"));
    ASSERT_EQ(BigInt("-123456789"), -BigInt("123456789"));
}

TEST_F(TestBigInt, testNEBigInt) {
    ASSERT_FALSE(BigInt(1) != BigInt(1));
    ASSERT_FALSE(BigInt(1234567) != BigInt(1234567));
    ASSERT_TRUE(BigInt(1234567) != BigInt(1234568));
    ASSERT_TRUE(BigInt(1) != BigInt(0));
    ASSERT_TRUE(BigInt(-1) != BigInt(0));
    ASSERT_TRUE(BigInt(-1) != BigInt(1));
}

TEST_F(TestBigInt, testGTBigInt) {
    ASSERT_TRUE(BigInt(1) > BigInt(0));
    ASSERT_TRUE(BigInt(1) > BigInt(-1));
    ASSERT_FALSE(BigInt(-1) > BigInt(1));
    ASSERT_TRUE(BigInt(12456789) > BigInt(-12456789));
    ASSERT_FALSE(BigInt(12456789) > BigInt(12456789));
    ASSERT_TRUE(BigInt("99999999999") > BigInt("99999999990"));
}

TEST_F(TestBigInt, testLTBigInt) {
    ASSERT_FALSE(BigInt(1) < BigInt(0));
    ASSERT_FALSE(BigInt(1) < BigInt(-1));
    ASSERT_TRUE(BigInt(-1) < BigInt(1));
    ASSERT_FALSE(BigInt(12456789) < BigInt(-12456789));
    ASSERT_FALSE(BigInt(12456789) < BigInt(12456789));
    ASSERT_FALSE(BigInt("99999999999") < BigInt("99999999990"));
}

TEST_F(TestBigInt, testGEBigInt) {
    ASSERT_TRUE(BigInt(1) >= BigInt(0));
    ASSERT_TRUE(BigInt(1) >= BigInt(-1));
    ASSERT_FALSE(BigInt(-1) >= BigInt(1));
    ASSERT_TRUE(BigInt(12456789) >= BigInt(-12456789));
    ASSERT_TRUE(BigInt(12456789) >= BigInt(12456789));
    ASSERT_TRUE(BigInt("99999999999") >= BigInt("99999999990"));
}

TEST_F(TestBigInt, testLEBigInt) {
    ASSERT_FALSE(BigInt(1) <= BigInt(0));
    ASSERT_FALSE(BigInt(1) <= BigInt(-1));
    ASSERT_TRUE(BigInt(-1) <= BigInt(1));
    ASSERT_FALSE(BigInt(12456789) <= BigInt(-12456789));
    ASSERT_TRUE(BigInt(12456789) <= BigInt(12456789));
    ASSERT_FALSE(BigInt("99999999999") <= BigInt("99999999990"));
}

TEST_F(TestBigInt, testCopyConstructorBigInt) {
    BigInt num1("123456789");
    BigInt num2 = num1;
    BigInt num3;
    ASSERT_EQ(num1, num1);
    ASSERT_EQ(num1, num2);
    ASSERT_NE(num1, num3);
}

TEST_F(TestBigInt, testCopyOperatorBigInt) {
    BigInt num1("123456789");
    BigInt num2;
    BigInt num3;
    num2 = num1;
    ASSERT_EQ(num1, num1);
    ASSERT_EQ(num1, num2);
    ASSERT_NE(num1, num3);
    num1 = num1;
    ASSERT_EQ(num1, num1);
}

TEST_F(TestBigInt, testMoveConstructorBigInt) {
    BigInt num1("123456789");
    BigInt num2 = std::move(num1);
    BigInt num3;
    ASSERT_NE(num1, num2);
    ASSERT_EQ(num2, BigInt("123456789"));
    ASSERT_EQ(num1, BigInt("0"));
}

TEST_F(TestBigInt, testMoveOperatorBigInt) {
    BigInt num1("123456789");
    BigInt num2;
    BigInt num3;
    num2 = std::move(num1);
    ASSERT_NE(num1, num2);
    ASSERT_EQ(num2, BigInt("123456789"));
    ASSERT_EQ(num1, BigInt("0"));
}