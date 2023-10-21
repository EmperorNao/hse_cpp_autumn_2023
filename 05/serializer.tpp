#include "serializer.hpp"


Serializer::Serializer(std::ostream& out): out(out) { }

template <class T>
Error Serializer::save(T& object) {
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args) {
    this->out << std::boolalpha;
    auto err = process(std::forward<ArgsT>(args)...);
    this->out << std::noboolalpha;
    return err;
}

template <class T, class... ArgsT>
Error Serializer::process(T arg, ArgsT... args) {
    auto argError = this->process<T>(std::forward<T>(arg));
    this->out << separator;
    auto argsError = this->process(std::forward<ArgsT>(args)...);
    return argError && argsError;
}

template <class T = bool&&>
Error Serializer::process(bool&& arg) {
    this->out << arg;
    return Error::NoError;
}

template <class T = uint64_t&&>
Error Serializer::process(uint64_t&& arg) {
    this->out << arg;
    return Error::NoError;
}