#pragma once
#include <string>
#include <vector>
#include <exception>
#include <sstream>


class FormatBraseExeption {
public:
    const char* what() const noexcept {
        return "Incorrect format of curly brackets in the format string: expected {n}, "
            "where n is unsigned integer denoting number of argument";
    }
};

class FormatArgumentNumberException {
public:
    const char* what() const noexcept {
        return "Incorrect number of argument in curly brackets";
    }
};


std::pair<bool, uint64_t> convertToUint64(const std::string& str);

template <class T>
void parseArgs(std::vector<std::string>& parameters, T arg);

template <class T, class... ArgsT>
void parseArgs(std::vector<std::string>& parameters, T arg, ArgsT... args);

template <class... ArgsT>
std::string format(const std::string& fmt, ArgsT... args);

#include "format.tpp"