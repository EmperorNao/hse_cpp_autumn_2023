#pragma once

#include <cstddef>


class Allocator {

private:
    char* start;
    char* current;
    size_t maxSize;

    void initialize(size_t maxSize);
    void finalize();
    bool is_initialized();
    bool can_allocate(size_t size);

public:
    Allocator();
    ~Allocator();

    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();

};