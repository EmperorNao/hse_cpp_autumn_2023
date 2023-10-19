#include "bigint.hpp"


BigInt::BigInt(): positiveSign(true) {
    this->digits.push_back(0);
}

BigInt::BigInt(int32_t number) {
    positiveSign = number >= 0;
    number = std::abs(number);
    if (number == 0) {
        this->digits.push_back(0);
    }

    while (number > 0) {
        int32_t residual = number % BigInt::Base;
        this->digits.push_back(residual);
        number /= BigInt::Base;
    }
}

void BigInt::removeZerosWithSign() {
    size_t i = 0;
    auto length = this->digits.size();
    while (i + 1 < length and this->digits[length - i - 1] == 0) {
        i += 1;
    }
    this->digits.resize(length - i);
    if (this->digits.size() == 1 and this->digits[0] == 0) {
        this->positiveSign = true;
    }
}

std::string BigInt::toString() const {
    std::stringstream ss;
    if (!this->positiveSign) {
        ss << "-";
    }
    std::size_t length = this->digits.size();
    ss << this->digits[length - 1];
    for (size_t i = 1; i < length; ++i) {

        ss << std::setfill('0') << std::setw(BigInt::BaseDegree) << this->digits[length - 1 - i];
    }
    return ss.str();
}

BigInt::BigInt(std::string strNumber) {
    std::int32_t i = 0;
    while (i < static_cast<std::int32_t>(strNumber.size()) and strNumber[i] == ' ') {
        i += 1;
    }

    this->positiveSign = true;
    if (strNumber[i] == '-' or strNumber[i] == '+') {
        this->positiveSign = strNumber[i] == '+';
        i += 1;
    }

    std::int32_t j = strNumber.size() - 1;
    while (j >= i) {
        int32_t number = 0;
        std::size_t residual = std::min(4, j - i + 1);
        for (std::size_t k = 0; k < residual; ++k) {
            number *= 10;
            number += static_cast<int>(strNumber[j - residual + 1 + k] - '0');
        }
        this->digits.push_back(number);
        j -= 4;
    }
}

std::ostream& operator<<(std::ostream& os, const BigInt& number) {
    os << number.toString();
    return os;
}

BigInt BigInt::operator+(const BigInt& rhs) const {
    auto& lhs = *this;

    if (lhs.positiveSign == rhs.positiveSign) {
        // positive + positive or negative + negative

        BigInt res;
        size_t nDigits = std::min(lhs.digits.size(), rhs.digits.size());

        res.digits[0] = lhs.digits[0] + rhs.digits[0];
        int32_t carry = res.digits[0] / BigInt::Base;
        res.digits[0] = (res.digits[0] % BigInt::Base);

        size_t i = 1;

        for (i = 1; i < nDigits; ++i) {
            res.digits.push_back(0);
            res.digits[i] = lhs.digits[i] + rhs.digits[i] + carry;
            carry = res.digits[i] / BigInt::Base;
            res.digits[i] = (res.digits[i] % BigInt::Base);      
        }

        while (i < lhs.digits.size()) {
            res.digits.push_back(0);
            res.digits[i] = lhs.digits[i] + carry;
            carry = res.digits[i] / BigInt::Base;
            res.digits[i] = (res.digits[i] % BigInt::Base); 
            i += 1;
        }

        while (i < rhs.digits.size()) {
            res.digits.push_back(0);
            res.digits[i] = rhs.digits[i] + carry;
            carry = res.digits[i] / BigInt::Base;
            res.digits[i] = (res.digits[i] % BigInt::Base); 
            i += 1;
        }

        if (carry) {
            res.digits.push_back(1);
        }

        res.positiveSign = lhs.positiveSign;
        return res;
    }
    else {
        // positive + negative or negative + positive
        BigInt positive;
        BigInt negative;
        if (lhs.positiveSign) {
            positive = lhs;
            negative = rhs;
        }
        else {
            positive = rhs;
            negative = lhs;
        }
        negative.positiveSign = true;
        return positive - negative;
    }
}

BigInt BigInt::operator-(const BigInt& rhs) const {
    auto lhs = *this;

    if (lhs.positiveSign != rhs.positiveSign) {  
        // positive - negative or negative - positive 
        bool finalSign;
        BigInt positive;
        BigInt negative;

        if (lhs.positiveSign) {
            finalSign = true;
            positive = lhs;
            negative = rhs;
        }
        else {
            finalSign = false;
            positive = rhs;
            negative = lhs;
        }
        negative.positiveSign = true;
        auto res = positive + negative;
        res.positiveSign = finalSign;

        return res;
    }
    else {
        // positive - positive or negative - negative
        BigInt lOperand;
        BigInt rOperand;
        bool finalSign;

        if (lhs.positiveSign) {
            lOperand = lhs;
            rOperand = rhs;
            finalSign = true;
        }
        else {
            lOperand = rhs;
            lOperand.positiveSign = true;
            rOperand = lhs;
            rOperand.positiveSign = true;
            finalSign = false;
        }

        if (lOperand < rOperand) {
            finalSign = !finalSign;
            std::swap(lOperand, rOperand);
        }

        BigInt res;

        size_t nDigits = std::min(lOperand.digits.size(), rOperand.digits.size());

        res.digits[0] = lOperand.digits[0] - rOperand.digits[0];
        int32_t carry = res.digits[0] < 0;
        res.digits[0] = carry ? BigInt::Base + res.digits[0] : res.digits[0];
    

        size_t i = 1;

        for (i = 1; i < nDigits; ++i) {
            res.digits.push_back(0);
            res.digits[i] = lOperand.digits[i] - rOperand.digits[i] - carry;
            carry = res.digits[i] < 0;
            res.digits[i] = carry ? BigInt::Base + res.digits[i] : res.digits[i];
        }

        while (i < lOperand.digits.size()) {
            res.digits.push_back(0);
            res.digits[i] = lOperand.digits[i] - carry;
            carry = res.digits[i] < 0;
            res.digits[i] = carry ? BigInt::Base + res.digits[i] : res.digits[i];
            i += 1;
        }

        if (carry) {
            res.digits.push_back(1);
        }
        
        res.positiveSign = finalSign;
        res.removeZerosWithSign();
        return res;
    }
}

BigInt BigInt::operator*(const BigInt& rhs) const {
    auto lhs = *this;
    BigInt res;
    
    if (lhs.positiveSign == rhs.positiveSign) {
        res.positiveSign = true;
    } else {
        res.positiveSign = false;
    }

    auto lLength = lhs.digits.size();
    auto rLength = rhs.digits.size();
    res.digits.resize(lLength * rLength);
    for (std::size_t l = 0; l < lLength; ++l) {
        int32_t residual = 0;
        for (std::size_t r = 0; r < rLength; ++r) {
            res.digits[l + r] += lhs.digits[l] * rhs.digits[r] + residual;
            residual = res.digits[l + r] / BigInt::Base;
            res.digits[l + r] = (res.digits[l + r] % BigInt::Base);
        }
        if (residual) {
            if (l + rLength >= res.digits.size()) {
                res.digits.push_back(residual);
            } else {
                res.digits[l + rLength] = residual;
            }
        }
    }

    res.removeZerosWithSign();
    return res;
}

BigInt BigInt::operator+(int32_t rhs) const {
    auto lhs = *this;
    return lhs + BigInt(rhs);
}

BigInt BigInt::operator-(int32_t rhs) const {
    auto lhs = *this;
    return lhs - BigInt(rhs);
}

BigInt BigInt::operator*(int32_t rhs) const {
    auto lhs = *this;
    return lhs * BigInt(rhs);
}

BigInt BigInt::operator-() const {
    BigInt res = *this;
    res.positiveSign = !res.positiveSign;
    res.removeZerosWithSign();
    return res;
}

bool BigInt::operator==(const BigInt& rhs) const {
    auto& lhs = *this;
    if (lhs.positiveSign != rhs.positiveSign or lhs.digits.size() != rhs.digits.size()) {
        return false;
    }

    for (std::size_t i = 0; i < lhs.digits.size(); ++i) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return false;
        }
    }

    return true;
}

bool BigInt::operator!=(const BigInt& rhs) const {
    auto& lhs = *this;
    return !(lhs == rhs);
}

bool BigInt::operator>=(const BigInt& rhs) const {
    auto& lhs = *this;
    return (lhs > rhs) or (lhs == rhs);
}

bool BigInt::operator<=(const BigInt& rhs) const {
    auto& lhs = *this;
    return !(lhs > rhs);
}

bool BigInt::operator>(const BigInt& rhs) const {
    auto& lhs = *this;
    if (lhs.positiveSign == rhs.positiveSign) {

        bool finalFlag;
        if (lhs.positiveSign) {
            finalFlag = true;
        }
        else {
            finalFlag = false;
        }

        if (lhs.digits.size() < rhs.digits.size()) {
            return !finalFlag;
        }
        else if (lhs.digits.size() > rhs.digits.size()) {
            return finalFlag;
        }
        else {
            auto length = lhs.digits.size();
            for (size_t i = 0; i < length; ++i) {
                if (lhs.digits[length - i - 1] > rhs.digits[length - i - 1]) {
                    return finalFlag;
                }
                else if (lhs.digits[length - i - 1] < rhs.digits[length - i - 1])
                {
                    return !finalFlag;
                }
            }
            return false;
        }

    }
    else {
        if (lhs.positiveSign) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool BigInt::operator<(const BigInt& rhs) const {
    auto& lhs = *this;
    return !(lhs > rhs) and (lhs != rhs);
}

BigInt::BigInt(BigInt&& number) {
    this->digits = std::move(number.digits);
    this->positiveSign = number.positiveSign;

    number.positiveSign = true;
    number.digits.resize(0);
    number.digits.push_back(0);
}

BigInt& BigInt::operator=(BigInt&& number) {
    if (this == &number) {
        return *this;
    }
    this->digits = std::move(number.digits);
    this->positiveSign = number.positiveSign;

    number.positiveSign = true;
    number.digits.resize(0);
    number.digits.push_back(0);

    return *this;
}