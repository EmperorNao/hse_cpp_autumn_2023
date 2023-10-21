#pragma once

#include <iostream>
#include <type_traits>

#include "error.hpp"


class Serializer {
    
private:
    static constexpr char separator = ' ';
    std::ostream& out;

public:
    explicit Serializer(std::ostream& out);

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);

private:
    template <class T, class... ArgsT>
    Error process(T arg, ArgsT... args);

    template <class T >
    Error process(T&& arg);

    template <class T = bool&&>
    Error process(bool&& arg);

    template <class T = uint64_t&&>
    Error process(uint64_t&& arg);

};


#include "serializer.tpp"