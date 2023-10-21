#pragma once


enum class Error {
    NoError,
    CorruptedArchive
};

Error operator&&(const Error& lhs, const Error& rhs);