#include "dynamic_array.hpp"
#include <iostream>


void DynamicArray::free() {
    if (this->ptr != nullptr) {
        delete[] this->ptr;
    }
}

void DynamicArray::alloc(std::size_t newSize, std::size_t oldLength) {
    auto newPtr = new DynamicArrayType[newSize];
    for (std::size_t i = 0; i < oldLength; ++i) {
        newPtr[i] = this->ptr[i];
    }
    free();
    for (std::size_t i = oldLength; i < newSize; ++i) {
        newPtr[i] = 0;
    }
    this->ptr = newPtr;
}

DynamicArray::DynamicArray(): ptr(nullptr), length(0), capacity(DefaultSize) {
    this->alloc(this->capacity, 0);    
}

DynamicArray::DynamicArray(std::size_t size): ptr(nullptr), length(size), capacity(size) {
    this->alloc(this->capacity, 0);
}

DynamicArray::~DynamicArray() {
    free();
}

DynamicArray::DynamicArray(const DynamicArray& arr) {
    this->ptr = nullptr;
    this->alloc(arr.capacity, 0);
    this->length = arr.length;
    this->capacity = arr.capacity;
    for (std::size_t i = 0; i < this->length; ++i) {
        this->ptr[i] = arr.ptr[i];
    }
}

DynamicArray::DynamicArray(DynamicArray&& arr) {
    this->ptr = arr.ptr;
    this->length = arr.length;
    this->capacity = arr.capacity;

    arr.ptr = nullptr;
    arr.length = 0;
    arr.capacity = 0;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& arr) {
    if (this == &arr) {
        return *this;
    }

    if (this->capacity < arr.capacity) {
        free();
        alloc(arr.capacity, 0);
        this->capacity = arr.capacity;
    }

    this->length = arr.length;
    for (std::size_t i = 0; i < arr.length; ++i) {
        this->ptr[i] = arr.ptr[i];
    }

    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& arr) {
    if (this == &arr) {
        return *this;
    }

    free();

    this->ptr = arr.ptr;
    this->length = arr.length;
    this->capacity = arr.capacity;

    arr.ptr = nullptr;
    arr.length = 0;
    arr.capacity = 0;
  
    return *this;
}

DynamicArrayType& DynamicArray::operator[](std::size_t idx) {
    if (idx >= this->length) {
        throw std::out_of_range("Index " + \
            std::to_string(idx) + " is out of range for length " +\
            std::to_string(this->length)
        );
    }
    return this->ptr[idx];
}

std::size_t DynamicArray::size() const {
    return this->length;
}

void DynamicArray::push_back(const DynamicArrayType& value) {
    if (this->length + 1 >= this->capacity) {
        auto newSize = this->capacity * 2;
        if (this->capacity == 0) {
            newSize = DefaultSize;
        }
        this->alloc(newSize, this->length);
        this->capacity = newSize;
    }
    this->ptr[this->length] = value;
    this->length += 1; 
}

void DynamicArray::resize(std::size_t length) {
    if (length == 0) {
        free();
        this->length = 0;
        this->capacity = 0;
    }
    if (length > this->capacity) {
        alloc(length, this->length);
    }
    this->length = length;
}