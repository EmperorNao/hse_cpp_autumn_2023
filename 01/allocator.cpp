#include "allocator.hpp"


void Allocator::initialize(size_t maxSize) {
    this->maxSize = maxSize;
    this->start = new char[this->maxSize];
    this->current = this->start;
}

void Allocator::finalize() {
    delete[] this->start;
    this->start = nullptr;
    this->current = nullptr;
}

bool Allocator::isInitialized() {
    return this->start != nullptr;
}

bool Allocator::canAllocate(size_t size) {
    return (this->current - this->start) + size <= this->maxSize;
}


Allocator::Allocator(): start(nullptr), current(nullptr), maxSize(0) {}

Allocator::~Allocator() {
    if (this->isInitialized()) {
        this->finalize();
    }   
}


void Allocator::makeAllocator(size_t maxSize) {
    if (this->isInitialized()){
        this->finalize();
    }

    this->initialize(maxSize);
}

char* Allocator::alloc(size_t size) {
    if (!this->isInitialized() or !this->canAllocate(size)) {
        return nullptr;
    }

    char* allocated = this->current;
    this->current += size;
    return allocated;
}

void Allocator::reset() {
    this->current = this->start;
}