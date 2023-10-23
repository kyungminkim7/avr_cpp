#pragma once

#include "math.h"

namespace avr_cpp {

template<typename T>
class Degree;

template<typename T>
class Radian;

template<typename T>
class Degree {
public:
    Degree(T angle);
    Degree(const Radian<T> &radians);

    operator T() const;

    Degree& operator+=(const Degree &other);
    Degree& operator-=(const Degree &other);
    Degree& operator*=(const Degree &other);
    Degree& operator/=(const Degree &other);

private:
    static constexpr T MAX = 360;

    static T convertAngle(T angle);

    T angle;
};

template<typename T>
class Radian {
public:
    Radian(T angle);
    Radian(const Degree<T> &degrees);

    operator T() const;

    Radian& operator+=(const Radian &other);
    Radian& operator-=(const Radian &other);
    Radian& operator*=(const Radian &other);
    Radian& operator/=(const Radian &other);

private:
    static constexpr T MAX = 2 * PI<T>;

    static T convertAngle(T angle);

    T angle;
};

template<typename T>
bool operator==(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
bool operator==(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
bool operator<(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
bool operator<(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
bool operator<=(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
bool operator<=(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
bool operator>(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
bool operator>(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
bool operator>=(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
bool operator>=(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
Radian<T> operator*(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
Radian<T> operator*(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
Radian<T> operator/(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
Radian<T> operator/(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
Radian<T> operator+(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
Radian<T> operator+(const Degree<T> &lhs, const Radian<T> &rhs);

template<typename T>
Radian<T> operator-(const Radian<T> &lhs, const Degree<T> &rhs);

template<typename T>
Radian<T> operator-(const Degree<T> &lhs, const Radian<T> &rhs);

} // namespace avr_cpp

#include "angle_impl.h"