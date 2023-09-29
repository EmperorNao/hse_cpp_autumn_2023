#pragma once


#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>


enum class MatrixAxis {
    ROW = 0,
    COLUMN = 1
};


class Matrix {

private:
    class ProxyMatrixRow;
    int32_t* data;
    size_t nRows;
    size_t nColumns;

    static bool isEqualShape(const Matrix& rhs, const Matrix& lhs);
    static std::string getShapeExceptionString(const Matrix& rhs, const Matrix& lhs);
    static std::string getOutOfRangeExceptionString(size_t index, size_t maxIndex, MatrixAxis axis);

public:
    Matrix(size_t nRows, size_t nColumns);
    ~Matrix();

    size_t numberOfRows() const;
    size_t numberOfColumns() const;
    std::pair<size_t, size_t> shape() const;
    
    ProxyMatrixRow operator[](size_t rowIndex) const;

    Matrix operator*(int32_t number) const;
    Matrix operator+(const Matrix& rhs) const;
    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

};


class Matrix::ProxyMatrixRow {

private:
    int32_t* data;
    size_t nColumns;

public:

    ProxyMatrixRow(int32_t* data, size_t nColumns);
    ~ProxyMatrixRow() = default;

    int32_t& operator[](size_t index) const;

};
