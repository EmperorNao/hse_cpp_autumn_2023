#pragma once

#include <iostream>

#include "error.hpp"


class Deserializer {
    
private:
    static constexpr char separator = ' ';
    std::istream& in;
    
    std::pair<bool, uint64_t> convertToUint64(const std::string& str);

public:
    explicit Deserializer(std::istream& in);

    template <class T>
    Error load(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT&... args);

    template <class T, class... ArgsT>
    Error process(T& arg, ArgsT&... args);

    template <class T>
    Error process(T& arg);

    template <class T = bool&>
    Error process(bool& arg);

    template <class T = uint64_t&>
    Error process(uint64_t& arg);

};


#include "deserializer.tpp"