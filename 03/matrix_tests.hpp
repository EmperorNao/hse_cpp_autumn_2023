#pragma once

#include <fstream>
#include <cstdio>

#include "gtest/gtest.h"

#include "matrix.hpp"


class TestMatrix: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};


TEST_F(TestMatrix, testSizesMatrix) {

    Matrix a(3, 2);
    Matrix b(2, 3);
    ASSERT_EQ(a.numberOfRows(), 3);
    ASSERT_EQ(a.numberOfColumns(), 2);
    ASSERT_EQ(b.numberOfRows(), 2);
    ASSERT_EQ(b.numberOfColumns(), 3);
    
}

TEST_F(TestMatrix, testGetElementMatrix) {

    Matrix a(3, 2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    ASSERT_EQ(a[0][0], 1);
    ASSERT_EQ(a[0][1], 2);
    ASSERT_EQ(a[1][0], 3);

}

TEST_F(TestMatrix, testGetElementOutOfRangeMatrix) {

    Matrix a(3, 2);
    a[0][0] = 1;
    ASSERT_THROW(a[10][10], std::out_of_range);

}

TEST_F(TestMatrix, testMupltiplicationByNumberMatrix) {

    Matrix a(3, 2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    Matrix b = a * 2;
    ASSERT_EQ(b[0][0], 2);
    ASSERT_EQ(b[0][1], 4);
    ASSERT_EQ(b[1][0], 6);

}

TEST_F(TestMatrix, testAdditionMatrix) {

    size_t nrows = 2;
    size_t ncols = 3;
    Matrix a(nrows, ncols);
    Matrix b(nrows, ncols);

    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            a[i][j] = 1;
            b[i][j] = 2;
        }
    }

    Matrix c = a + b;
    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            ASSERT_EQ(c[i][j], 3);
        }
    }

}

TEST_F(TestMatrix, testAdditionShapesMismatchMatrix) {

    size_t nrows = 2;
    size_t ncols = 3;
    Matrix a(nrows, ncols);
    Matrix b(ncols, nrows);

    ASSERT_NE(nrows, ncols);
    ASSERT_THROW(a + b, std::logic_error);

}

TEST_F(TestMatrix, testComparisonMatrix) {

    size_t nrows = 2;
    size_t ncols = 3;
    Matrix a(nrows, ncols);
    Matrix b(nrows, ncols);

    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            a[i][j] = 1;
            b[i][j] = 2;
        }
    }

    ASSERT_EQ(a == b, false);
    ASSERT_EQ(a != b, true);

}

TEST_F(TestMatrix, testOstreamOutputMatrix) {

    std::ofstream ofile;
    ofile.open("testOstreamOutputMatrix.bin", std::ios::out | std::ios::binary);

    size_t nrows = 2;
    size_t ncols = 3;

    Matrix a(nrows, ncols);
    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            a[i][j] = 1;
        }
    }
    a[0][0] = 2;

    ofile << a;
    ofile.close();

    std::ifstream ifile;
    ifile.open("testOstreamOutputMatrix.bin", std::ios::in | std::ios::binary);

    int value;
    std::string line;
    Matrix b(nrows, ncols);
    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            ifile >> value;
            b[i][j] = value;
        }
    }
    ifile.close();

    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            ASSERT_EQ(a[i][j], b[i][j]);
        }
    }  
    
    remove("testOstreamOutputMatrix.bin");

}
