#include "matrix.hpp"


bool Matrix::isEqualShape(const Matrix& rhs, const Matrix& lhs) {
    return lhs.nRows == rhs.nRows and lhs.nColumns == rhs.nColumns;
}

std::string Matrix::getShapeExceptionString(const Matrix& rhs, const Matrix& lhs) {
    return std::string("Expected matrixes in sum be with same shape, but") + \
        "(" + std::to_string(lhs.nRows) + "," + std::to_string(lhs.nColumns) + ")" + \
        "!=" + \
        "(" + std::to_string(rhs.nRows) + "," + std::to_string(rhs.nColumns) + ")";
}

std::string Matrix::getOutOfRangeExceptionString(size_t index, size_t maxIndex, MatrixAxis axis) {
    std::string axisString;
    if (axis == MatrixAxis::ROW) {
        axisString = "row";
    }
    else {
        axisString = "column";
    }
    return axisString + " index " + std::to_string(index) + \
        " is out of range for " + std::to_string(maxIndex) + " " + axisString + "s";
}


Matrix::Matrix(size_t nRows, size_t nColumns): nRows(nRows), nColumns(nColumns) {
    this->data = new int32_t[this->nRows * this->nColumns];
}

Matrix::~Matrix() {
    delete[] this->data;
}


size_t Matrix::numberOfRows() const {
    return this->nRows;
}

size_t Matrix::numberOfColumns() const {
    return this->nColumns;
}

std::pair<size_t, size_t> Matrix::shape() const {
    return std::make_pair(this->nRows, this->nColumns);
}


Matrix::ProxyMatrixRow Matrix::operator[](size_t rowIndex) const {

    if (rowIndex >= this->nRows) {
        throw std::out_of_range(Matrix::getOutOfRangeExceptionString(rowIndex, this->nRows, MatrixAxis::ROW));
    }
    return Matrix::ProxyMatrixRow(this->data + this->nColumns * rowIndex, this->nColumns);

}

Matrix Matrix::operator*(int32_t number) const {

    Matrix ret(this->nRows, this->nColumns);
    for (size_t idx = 0; idx < this->nRows * this->nColumns; ++idx) {
        ret.data[idx] = this->data[idx] * number;
    }
    return ret;

}

Matrix Matrix::operator+(const Matrix& rhs) const {
    const Matrix& lhs = *this;

    if (!Matrix::isEqualShape(lhs, rhs)) {
        throw std::logic_error(Matrix::getShapeExceptionString(lhs, rhs));
    }

    Matrix ret(lhs.nRows, lhs.nColumns);
    for (size_t idx = 0; idx < lhs.nRows * lhs.nColumns; ++idx) {
        ret.data[idx] = lhs.data[idx] + rhs.data[idx];
    }
    return ret;

}

bool Matrix::operator==(const Matrix& rhs) const {
    const Matrix& lhs = *this;

    if (!Matrix::isEqualShape(lhs, rhs)) {
        throw std::logic_error(Matrix::getShapeExceptionString(lhs, rhs));
    }

    for (size_t idx = 0; idx < lhs.nRows * lhs.nColumns; ++idx) {
        if (lhs.data[idx] != rhs.data[idx]) {
            return false;
        }
    }
    return true;

}

bool Matrix::operator!=(const Matrix& rhs) const {
    return !((*this) == rhs);
}


std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {

    for (size_t rowIdx = 0; rowIdx < matrix.nRows; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < matrix.nColumns; ++colIdx) {
            os << matrix.data[rowIdx * matrix.nColumns + colIdx] << " ";
        }    
        os << std::endl;
    }
    return os;

}


Matrix::ProxyMatrixRow::ProxyMatrixRow(int32_t* data, size_t nColumns): data(data), nColumns(nColumns) {};

int32_t& Matrix::ProxyMatrixRow::operator[](size_t colIndex) const {
    if (colIndex >= this->nColumns) {
        throw std::out_of_range(Matrix::getOutOfRangeExceptionString(colIndex, this->nColumns, MatrixAxis::COLUMN));
    }
    return this->data[colIndex];
}
