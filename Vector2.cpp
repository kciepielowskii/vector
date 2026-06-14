#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// int add(int i1, int i2) {
//     return i1 + i2;
// }
//
// int add(double d1, double d2) {
//     return d1 + d2;
// }

// int add(string s1, string s2) {
//     return s1 + s2;
// }

template <typename T>
T add(T arg1, T arg2) {
    return arg1 + arg2;
}

template <typename T>
class Vector2 {
public:
    T x_;
    T y_;

    Vector2(T x, T y) {
        x_ = x;
        y_ = y;
    }

    Vector2<T> add(Vector2<T> v) {
        return Vector2<T>(x_ + v.x_, y_ + v.y_);
    }

    Vector2<T> subtract(Vector2<T> v) {
        return Vector2<T>(x_ - v.x_, y_ - v.y_);
    }

    Vector2<T> scalar_multiply(Vector2<T> v) {
        return Vector2<T>(x_ * v.x_, y_ * v.y_);
    }

    Vector2<T> operator+(const Vector2<T>& v) {
        return Vector2<T>(x_ + v.x_, y_ + v.y_);
    }

    Vector2<T> operator-(const Vector2<T>& v) {
        return Vector2<T>(x_ - v.x_, y_ - v.y_);
    }

    Vector2<T> operator*(const Vector2<T>& v) {
        return Vector2<T>(x_ * v.x_, y_ * v.y_);
    }

    T length() {

        return sqrt(x_ * x_ + y_ * y_);
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Vector2<T>& v) {
    os << "[ " << v.x_ << " , " << v.y_ << " ]";
    return os;
}

template <typename T>
istream& operator>>(istream& is, Vector2<T>& v) {
    // [ 34 , -75 ]         [    34    ,    -75    ]
    // is >> '[' << v.x_ << ',' << v.y_ << ']';

    // 34 -75
    string temp;
    is >> temp >> v.x_ >> temp >> v.y_ >> temp;


    return is;
}


int main()
{
    Vector2<int> v5(0, 0);
    cin >> v5;

    Vector2<int> v6(0, 0);
    cin >> v6;

    cout << v5 + v6 << endl;

    Vector2<int> v1(0,0);
    Vector2<int> v2(5,11);
    Vector2<int> v3 = v1 + v2;
    Vector2<int> v4 = v1 * v2;

    std::cout << v1 + v2 << std::endl;
    std::cout << v1 - v2 << std::endl;

    std::cout << v3.x_ << "," << v3.y_ << std::endl;
    std::cout << v4.x_ << "," << v4.y_ << std::endl;

    std::cout << "Length: " << v2.length() << std::endl;

    std::cout << v3;
}