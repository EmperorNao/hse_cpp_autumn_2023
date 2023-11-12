#include "format.hpp"
#include <iostream>


std::pair<bool, uint64_t> convertToUint64(const std::string& str) {
    bool result = true;
    uint64_t number = 0;
    for (auto ch: str) {

        if (!std::isdigit(ch)){
            result = false;
            break;
        }
        
        auto digit = static_cast<uint64_t>(ch - '0');
        if (number * 10 + digit < number) {
            result = false;
            break;
        }
        number = number * 10 + digit;

    }
    return std::make_pair(result, number);
}

template <class T>
void parseArgs(std::vector<std::string>& parameters, T arg) {
    std::stringstream ss;
    ss << arg;
    parameters.push_back(ss.str());
}

template <class T, class... ArgsT>
void parseArgs(std::vector<std::string>& parameters, T arg, ArgsT... args) {
    parseArgs(parameters, arg);
    parseArgs(parameters, std::forward<ArgsT>(args)...);
};

template <class... ArgsT>
std::string format(const std::string& fmt, ArgsT... args) {
    std::vector<std::string> parameters;
    parseArgs(parameters, std::forward<ArgsT>(args)...);

    std::string output;
    size_t index = 0;
    while (index < fmt.size()) {
        if (fmt[index] == '{') {

            size_t endIndex = index + 1;

            while (endIndex < fmt.size()) {
                if (fmt[endIndex] == '{') {
                    throw FormatBraseExeption();
                }
                else if (fmt[endIndex] == '}') {
                    break;
                }
                ++endIndex;
            }

            if (endIndex == output.size() or (index + 1 == endIndex)) {
                throw FormatBraseExeption();
            }

            auto [result, parameterNumber] = convertToUint64(fmt.substr(index + 1, endIndex - (index + 1)));
            if (!result or parameterNumber >= parameters.size()) {
                throw FormatArgumentNumberException();
            }
            output += parameters[parameterNumber];
            index = endIndex;

        }
        else if (fmt[index] == '}') {
            throw FormatBraseExeption();
        }
        else {
            output += fmt[index];
        }
        ++index;
    }
    
    return output;
}