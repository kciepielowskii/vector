#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>

using namespace std;

class Shape {
public:
    virtual double area() = 0;
};

class Rectangle : public Shape {
public:
    double a;
    double b;

    Rectangle(double a, double b) : a(a), b(b) {}

    double area() override {
        return a * b;
    }
};

class Circle : public Shape {
public:
    double radius;

    Circle(double radius) : radius(radius) {}

    double area() override {
        return 2 * M_PI * radius;
    }
};

class Triangle : public Shape {
public:
    double a, b, c;

    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double area() override {
        double x = (a + b + c) / 2;
        return sqrt(x * (x - a) * (x - b) * (x - c));
    }
};

int main() {
    // Shape s;

    Rectangle* r = new Rectangle(3, 4);
    Triangle* t = new Triangle(3, 4, 5);

    cout << r->area() << endl;
    cout << t->area() << endl;

    vector<Shape*> shapes;
    shapes.push_back(r);
    shapes.push_back(t);

    auto test = shapes[0];
    cout << typeid(*test).name() << '\n';

    cout << shapes[0]->area() << '\n';
    cout << shapes[1]->area() << '\n';

    auto r2 = dynamic_cast<Rectangle*>(test);
    if (r2 != nullptr) {
        cout << r2->a << ' ' << r2->b << ' ' << r2->area() << '\n';
    }

    auto t2 = dynamic_cast<Triangle*>(test);
    if (t2 != nullptr) {
        cout << t2->a << ' ' << t2->b << ' ' << t2->c << ' ' << t2->area() << '\n';
    }
}
