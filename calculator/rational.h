#pragma once

#include <numeric>
#include <iostream>
#include <cstdlib>

class Rational {
public:
    Rational() = default;
    Rational (const Rational& r) = default;
    Rational(int numerator, int denominator)
    : numerator_(numerator)
    , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        Reduction();
    }

    Rational(int value) {                           // Конструктор копирования.
        numerator_ = value;
        denominator_ = 1;        
    }

    Rational& operator=(const int value){           // Конструктор присваивания числом.
        numerator_ = value;
        denominator_ = 1;
        return *this;   
    }

    Rational& operator=(const Rational& other) {     // Конструктор присваивания другой дробью.
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        Reduction();
        return *this;
    }
    

    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    Rational Inv() const {    
        return Rational{denominator_, numerator_};  }
    

    Rational operator+() const {
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r);           // Перегрузки операторов ввода-вывода (определены после класса).
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    

    bool operator==(const Rational& r) const = default;    // Перегрузка оператора сравнения.
  

    Rational& operator*=(const Rational r2) {              // Перегрузки операторов присвоения.
        numerator_ *= r2.numerator_;
        denominator_ *= r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational r2) {
        numerator_ *= r2.denominator_;
        denominator_ *= r2.numerator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational r2) {        
        numerator_ = numerator_ * r2.denominator_ - denominator_ * r2.numerator_;
        denominator_ = denominator_ * r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator+=(const Rational r2) {        
        numerator_ = numerator_ * r2.denominator_ + denominator_ * r2.numerator_;
        denominator_ = denominator_ * r2.denominator_;
        Reduction();
        return *this;
    }
    

    Rational operator+(const Rational& r2) const {         // Перегрузки мат. операций.
        Rational other{*this};
        other += r2;    
        return other;
    }

    Rational operator-(const Rational& r2) const {
        Rational other{*this};
        other -= r2;    
        return other;
    }

    Rational operator*(const Rational& r2) const {
        Rational other{*this};
        other *= r2;    
        return other;
    }

    Rational operator/(const Rational& r2) const {
        Rational other{*this};
        other /= r2;    
        return other;
    }
    
    Rational operator-() const {        // Смена знака дроби.
        if (denominator_ < 0) {
            return Rational{-numerator_, -denominator_};
        }
        return Rational{-numerator_, denominator_};
    }

private:

    void Reduction() {                  // Метод для приведения дроби к корректной форме.
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {         // Перегрузка оператора вывода.
    using namespace std::literals;
    if (r.denominator_ == 1) { 
        os <<  r.numerator_;  
        return os; }  
    os << r.numerator_ << " / "s << r.denominator_;
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {               // Перегрузка оператора ввода.
    int n, d;
    char div;
    if (!(is >> n)) {
        return is;
    }
    if (!(is >> std::ws >> div)) {
        r = Rational(n, 1);
        is.clear();
        return is;
    }    
    if (div != '/') {
        r = Rational(n, 1);
        is.unget();
        return is;
    }
    if (!(is >> d) || (d == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Rational(n, d);
    return is;
}

inline auto operator<=>(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() <=>
        static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
}
