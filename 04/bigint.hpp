#pragma once


#include <cmath>
#include <string>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "dynamic_array.hpp"


class BigInt {

private:

    // реализация поддерживает основание 10 в степени k, где k <= 4
    static const int32_t Base = 10000;
    static const int32_t BaseDegree = 4;

    mutable DynamicArray digits;
    bool positiveSign;

    void removeZerosWithSign();

public:

    BigInt();
    BigInt(int32_t number);
    BigInt(std::string strNumber);

    friend std::ostream& operator<<(std::ostream& os, const BigInt& number);
    BigInt operator+(const BigInt& rhs) const;
    BigInt operator-(const BigInt& rhs) const;
    BigInt operator*(const BigInt& rhs) const;
    BigInt operator+(int32_t rhs) const;
    BigInt operator-(int32_t rhs) const;
    BigInt operator*(int32_t rhs) const;
    BigInt operator-() const;

    bool operator==(const BigInt& rhs) const;
    bool operator!=(const BigInt& rhs) const;
    bool operator>(const BigInt& rhs) const;
    bool operator<(const BigInt& rhs) const;
    bool operator>=(const BigInt& rhs) const;
    bool operator<=(const BigInt& rhs) const;

    BigInt(const BigInt& number) = default;
    BigInt(BigInt&& number);

    BigInt& operator=(const BigInt& number) = default;
    BigInt& operator=(BigInt&& number);

    std::string toString() const;

};