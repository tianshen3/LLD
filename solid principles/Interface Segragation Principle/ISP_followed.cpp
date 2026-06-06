#include<iostream>
using namespace std;

//seperate interface for the 2d and 3d shapes
class TwoDimensionalShape{
    public:
    virtual double area() = 0;
};

class ThreeDimensionalShape{
    public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Square: public TwoDimensionalShape{
    private:
    double side;

    public: 
    Square(double s) : side(s) {};

    double area() override {
        return side*side;
    }
};

class Rectangle : public TwoDimensionalShape {
    private:
    double length, width;

    public:
    Rectangle(double l, double w) : length(l), width(w) {};

    double area() override {
        return length*width;
    }
};

class Cube : public ThreeDimensionalShape {
    private: 
    double side;

    public:
    Cube(double s) : side(s) {};

    double area() override {
        return 6*side*side;
    }

    double volume() override {
        return side*side*side;
    }
};

int main(){
    TwoDimensionalShape* square = new Square(5);
    TwoDimensionalShape* rectangle = new Rectangle(4, 6);
    ThreeDimensionalShape* cube = new Cube(3);

    cout << "Square Area: " << square->area() << endl;
    cout << "Rectangle Area: " << rectangle->area() << endl;
    cout << "Cube Area: " << cube->area() << endl;
    cout << "Cube Volume: " << cube->volume() << endl;
    
    return 0;
}