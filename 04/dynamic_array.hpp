#pragma once

#include <cstdint>
#include <stdexcept>


using DynamicArrayType = int32_t;

class DynamicArray {
private:
    static const std::size_t DefaultSize = 10;
    DynamicArrayType* ptr;
    std::size_t length;
    std::size_t capacity;

    void alloc(std::size_t newSize, std::size_t oldLength);
    void free();

public:
    DynamicArray();
    DynamicArray(std::size_t size);
    ~DynamicArray();

    DynamicArray(const DynamicArray& number);
    DynamicArray(DynamicArray&& number);

    DynamicArray& operator=(const DynamicArray& number);
    DynamicArray& operator=(DynamicArray&& number);

    DynamicArrayType& operator[](std::size_t idx);
    std::size_t size() const;
    void push_back(const DynamicArrayType& value);
    void resize(std::size_t length);

};