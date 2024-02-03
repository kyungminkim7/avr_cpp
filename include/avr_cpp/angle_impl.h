namespace avr_cpp {

template<typename T>
T Degree<T>::convertAngle(T angle) {
    return modulo(angle, MAX) +
        (angle < 0 ? MAX : 0);
}

template<typename T>
Degree<T>::Degree(T angle) : angle(convertAngle(angle)) {}

template<typename T>
Degree<T>::Degree(const Radian<T> &radians) : angle(180 / PI<T> * radians) {}

template<typename T>
Degree<T>::operator T() const {
    return angle;
}

template<typename T>
Degree<T>& Degree<T>::operator+=(const Degree &other) {
    angle += other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
Degree<T>& Degree<T>::operator-=(const Degree &other) {
    angle -= other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
Degree<T>& Degree<T>::operator*=(const Degree &other) {
    angle *= other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
Degree<T>& Degree<T>::operator/=(const Degree &other) {
    angle /= other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
T Radian<T>::convertAngle(T angle) {
    return modulo(angle, MAX) +
        (angle < 0 ? MAX : 0);
}

template<typename T>
Radian<T>::Radian(T angle) : angle(convertAngle(angle)) {}

template<typename T>
Radian<T>::Radian(const Degree<T> &degrees) : angle(degrees * PI<T> / 180) {}

template<typename T>
Radian<T>::operator T() const {
    return angle;
}

template<typename T>
Radian<T>& Radian<T>::operator+=(const Radian &other) {
    angle += other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
Radian<T>& Radian<T>::operator-=(const Radian &other) {
    angle -= other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
Radian<T>& Radian<T>::operator*=(const Radian &other) {
    angle *= other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
Radian<T>& Radian<T>::operator/=(const Radian &other) {
    angle /= other;
    angle = convertAngle(angle);
    return *this;
}

template<typename T>
bool operator==(const Radian<T> &lhs, const Degree<T> &rhs) {
    return Degree<T>(lhs) == rhs;
}

template<typename T>
bool operator==(const Degree<T> &lhs, const Radian<T> &rhs) {
    return lhs == Degree<T>(rhs);
}

template<typename T>
bool operator<(const Radian<T> &lhs, const Degree<T> &rhs) {
    return Degree<T>(lhs) < rhs;
}

template<typename T>
bool operator<(const Degree<T> &lhs, const Radian<T> &rhs) {
    return lhs < Degree<T>(rhs);
}

template<typename T>
bool operator<=(const Radian<T> &lhs, const Degree<T> &rhs) {
    return Degree<T>(lhs) <= rhs;
}

template<typename T>
bool operator<=(const Degree<T> &lhs, const Radian<T> &rhs) {
    return lhs <= Degree<T>(rhs);
}

template<typename T>
bool operator>(const Radian<T> &lhs, const Degree<T> &rhs) {
return Degree<T>(lhs) > rhs;
}

template<typename T>
bool operator>(const Degree<T> &lhs, const Radian<T> &rhs) {
return lhs > Degree<T>(rhs);
}

template<typename T>
bool operator>=(const Radian<T> &lhs, const Degree<T> &rhs) {
    return Degree<T>(lhs) >= rhs;
}

template<typename T>
bool operator>=(const Degree<T> &lhs, const Radian<T> &rhs) {
    return lhs >= Degree<T>(rhs);
}

template<typename T>
Radian<T> operator*(const Radian<T> &lhs, const Degree<T> &rhs) {
    return lhs * Radian<T>(rhs);
}

template<typename T>
Radian<T> operator*(const Degree<T> &lhs, const Radian<T> &rhs) {
    return Radian<T>(lhs) * rhs;
}

template<typename T>
Radian<T> operator/(const Radian<T> &lhs, const Degree<T> &rhs) {
    return lhs / Radian<T>(rhs);
}

template<typename T>
Radian<T> operator/(const Degree<T> &lhs, const Radian<T> &rhs) {
    return Radian<T>(lhs) / rhs;
}

template<typename T>
Radian<T> operator+(const Radian<T> &lhs, const Degree<T> &rhs) {
    return lhs + Radian<T>(rhs);
}

template<typename T>
Radian<T> operator+(const Degree<T> &lhs, const Radian<T> &rhs) {
    return Radian<T>(lhs) + rhs;
}

template<typename T>
Radian<T> operator-(const Radian<T> &lhs, const Degree<T> &rhs) {
    return lhs - Radian<T>(rhs);
}

template<typename T>
Radian<T> operator-(const Degree<T> &lhs, const Radian<T> &rhs) {
    return Radian<T>(lhs) - rhs;
}

} // namespace avr_cpp