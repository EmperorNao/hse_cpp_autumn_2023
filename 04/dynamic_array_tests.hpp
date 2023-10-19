#pragma once

#include "gtest/gtest.h"

#include "dynamic_array.hpp"


class TestDynamicArray: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};


TEST_F(TestDynamicArray, TestEmptyDynamicArray) {
    DynamicArray arr;
    ASSERT_EQ(arr.size(), 0);
}

TEST_F(TestDynamicArray, TestConstructorWithSizeDynamicArray) {
    DynamicArray arr(5);
    ASSERT_EQ(arr.size(), 5);
}

TEST_F(TestDynamicArray, TestElementPushingDynamicArray) {
    DynamicArray arr;
    arr.push_back(42);
    ASSERT_EQ(arr.size(), 1);
    ASSERT_EQ(arr[0], 42);
    arr.push_back(322);
    ASSERT_EQ(arr.size(), 2);
    ASSERT_EQ(arr[1], 322);
}

TEST_F(TestDynamicArray, TestOutOfRangeDynamicArray) {
    DynamicArray arr;
    arr.push_back(42);
    ASSERT_THROW(arr[1], std::out_of_range);
}

TEST_F(TestDynamicArray, TestCopyConstructorEmptyDynamicArray) {
    DynamicArray arr1;

    DynamicArray arr2 = arr1;
    ASSERT_EQ(arr1.size(), 0);
    ASSERT_EQ(arr2.size(), 0);
}

TEST_F(TestDynamicArray, TestCopyConstructorDynamicArray) {
    DynamicArray arr1;
    arr1.push_back(42);

    DynamicArray arr2 = arr1;
    ASSERT_EQ(arr1.size(), 1);
    ASSERT_EQ(arr1[0], 42);
    ASSERT_EQ(arr2.size(), 1);
    ASSERT_EQ(arr2[0], 42);
}

TEST_F(TestDynamicArray, TestMoveConstructorEmptyDynamicArray) {
    DynamicArray arr1;
    DynamicArray arr2 = std::move(arr1);
    ASSERT_EQ(arr1.size(), 0);
    ASSERT_EQ(arr2.size(), 0);
}

TEST_F(TestDynamicArray, TestMoveConstructorDynamicArray) {
    DynamicArray arr1;
    arr1.push_back(42);

    DynamicArray arr2 = std::move(arr1);
    ASSERT_EQ(arr1.size(), 0);
    ASSERT_EQ(arr2.size(), 1);
    ASSERT_EQ(arr2[0], 42);
}

TEST_F(TestDynamicArray, TestCopyOperatorEmptyDynamicArray) {
    DynamicArray arr1;
    DynamicArray arr2;

    arr2 = arr1;
    ASSERT_EQ(arr1.size(), 0);
    ASSERT_EQ(arr2.size(), 0);
}

TEST_F(TestDynamicArray, TestCopyOperatorSelfcopyDynamicArray) {
    DynamicArray arr1;

    arr1.push_back(42);

    arr1 = arr1;
    ASSERT_EQ(arr1.size(), 1);
    ASSERT_EQ(arr1[0], 42);
}

TEST_F(TestDynamicArray, TestCopyOperatorDynamicArray) {
    DynamicArray arr1;
    DynamicArray arr2;

    arr1.push_back(42);

    arr2 = arr1;
    ASSERT_EQ(arr1.size(), 1);
    ASSERT_EQ(arr1[0], 42);
    ASSERT_EQ(arr2.size(), 1);
    ASSERT_EQ(arr2[0], 42);
}

TEST_F(TestDynamicArray, TestMoveOperatorEmptyDynamicArray) {
    DynamicArray arr1;
    DynamicArray arr2;

    arr2 = std::move(arr1);
    ASSERT_EQ(arr1.size(), 0);
    ASSERT_EQ(arr2.size(), 0);
}

TEST_F(TestDynamicArray, TestMoveOperatorSelfcopyDynamicArray) {
    DynamicArray arr1;

    arr1.push_back(42);

    arr1 = std::move(arr1);
    ASSERT_EQ(arr1.size(), 1);
    ASSERT_EQ(arr1[0], 42);
}

TEST_F(TestDynamicArray, TestMoveOperatorDynamicArray) {
    DynamicArray arr1;
    DynamicArray arr2;

    arr1.push_back(42);

    arr2 = std::move(arr1);
    ASSERT_EQ(arr1.size(), 0);
    ASSERT_EQ(arr2.size(), 1);
    ASSERT_EQ(arr2[0], 42);
}