
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "pow.h"

using Error = std::string;

template<class Number>
class Calculator {

public:
    void Set(Number number) {
        active_number_ = number;
    }

    Number GetNumber() const {
        return active_number_;
    }

    std::optional<Error> Add(Number number) {
        active_number_ += number;
        return std::nullopt;
    }

    std::optional<Error> Div(Number number) {
        if constexpr (std::is_same_v<Number, Rational>) {
            if (number.GetNumerator() == 0) {
                return Error{"Division by zero"};
            }
        }
        else if constexpr (std::is_integral_v<Number>){
            if (number == 0) {
                return Error{"Division by zero"};
            }
        }
        active_number_ /= number;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number number) {
        active_number_ *= number;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number number) {
        active_number_ -= number;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number number) {
        if constexpr (std::is_integral_v<Number>) {
            if (number == 0 && active_number_ == 0){
                return Error{"Zero power to zero"};
            }
            if (number < 0){
                return Error{"Integer negative power"};
            }
            active_number_ = IntegerPow(active_number_, number);
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>){
            if (number.GetNumerator() == 0 && active_number_ == 0){
                return Error{"Zero power to zero"};
            }
            if (number.GetDenominator() != 1){
                return Error{"Fractional power is not supported"};
            }
            active_number_ = ::Pow(active_number_ , number);
            return std::nullopt;
        } else {
            active_number_ = std::pow(active_number_ , number);
            return std::nullopt;
        }
    }

    void Save() {
        mem_ = active_number_;
    }

    void Load() {
        if (mem_.has_value()) {
            active_number_ = mem_.value();
        }
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

private:
    Number active_number_ = 0;
    std::optional<Number> mem_ = std::nullopt;
};

