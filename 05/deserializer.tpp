#include "deserializer.hpp"


std::pair<bool, uint64_t> Deserializer::convertToUint64(const std::string& str) {

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

Deserializer::Deserializer(std::istream& in): in(in) { }

template <class T>
Error Deserializer::load(T& object)
{
    return object.deserialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&... args)
{
    auto err = process(std::forward<ArgsT&>(args)...);
    return err;
}

template <class T, class... ArgsT>
Error Deserializer::process(T& arg, ArgsT&... args) {
    auto argError = this->process<T&>(std::forward<T&>(arg));
    auto argsError = this->process(std::forward<ArgsT&>(args)...);
    return argError && argsError;
}

template <class T = bool&>
Error Deserializer::process(bool& arg) {
    std::string line;
    std::getline(this->in, line, separator);
    if (line == "true") {
        arg = true;
    }
    else if (line == "false") {
        arg = false;
    }
    else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

template <class T = uint64_t&>
Error Deserializer::process(uint64_t& arg) {
    std::string line;
    std::getline(this->in, line, separator);
    auto [result, number] = convertToUint64(line);
    arg = number;
    if (!result) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}