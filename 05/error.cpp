#include "error.hpp"


Error operator&&(const Error& lhs, const Error& rhs) {
    if (lhs != Error::NoError) {
        return lhs;
    }
    else if (rhs != Error::NoError) {
        return rhs;
    }
    return Error::NoError;
}