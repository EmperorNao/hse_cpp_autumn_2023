#pragma once

#include <cmath>
#include <string>
#include <limits>
#include <iostream>
#include <algorithm>
#include <functional>


using StartEndCallback = std::function<void(void)>;
using DigitTokenCallback = std::function<void(uint64_t)>;
using StringTokenCallback = std::function<void(std::string_view&)>;


class TokenParser {

private:
    StartEndCallback startCallback;
    StartEndCallback endCallback;
    DigitTokenCallback digitCallback;
    StringTokenCallback stringCallback;

    static bool isDelimiter(char);
    std::pair<bool, uint64_t> convertToUint64(std::string_view& str);
    std::vector<std::string_view> splitString(const std::string&);

public:
    TokenParser() = default;

    void setStartCallback(StartEndCallback startCallback = nullptr);
    void setEndCallback(StartEndCallback endCallback = nullptr);

    void setDigitTokenCallback(DigitTokenCallback digitCallback = nullptr);
    void setStringTokenCallback(StringTokenCallback stringCallback = nullptr);

    void parse(const std::string&);

};