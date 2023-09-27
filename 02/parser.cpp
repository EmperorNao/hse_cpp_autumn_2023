#include "parser.hpp"


void TokenParser::setStartCallback(StartEndCallback startCallback) {
    this->startCallback = startCallback;
}

void TokenParser::setEndCallback(StartEndCallback endCallback) {
    this->endCallback = endCallback;
}

void TokenParser::setDigitTokenCallback(DigitTokenCallback digitCallback) {
    this->digitCallback = digitCallback;
}

void TokenParser::setStringTokenCallback(StringTokenCallback stringCallback) {
    this->stringCallback = stringCallback;
}


std::pair<bool, uint64_t> TokenParser::convertToUint64(std::string_view& str) {

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


bool TokenParser::isDelimiter(char c) {
    return c == '\t' or c == '\n' or c == ' ';
}

std::vector<std::string_view> TokenParser::splitString(const std::string& str) {

    std::vector<std::string_view> tokens;

    auto view = std::string_view{str};
    size_t startIndex = 0;
    size_t currentIndex = 0;
    while (currentIndex < view.size()) {

        if (TokenParser::isDelimiter(view[currentIndex])) {
            currentIndex += 1;
            continue;
        }

        startIndex = currentIndex;
        while (currentIndex != view.size() and !TokenParser::isDelimiter(view[currentIndex])) {
            currentIndex += 1;
        }
        auto sourceToken = view.substr(startIndex, currentIndex - startIndex);
        tokens.push_back(sourceToken);
    }    

    return tokens;

}


void TokenParser::parse(const std::string& str) {

    if (this->startCallback) {
        this->startCallback();
    }

    for (auto& token: this->splitString(str)) {

        auto [isConverted, number] = this->convertToUint64(token);
        if (isConverted) {
            if (this->digitCallback) {
                this->digitCallback(number);
            }  
        }
        else {
            if (this->stringCallback) {
                this->stringCallback(token);
            }  
        }

    }
    
    if (this->endCallback) {
        this->endCallback();
    }

}
