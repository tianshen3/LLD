#include<iostream>
#include<stdexcept>
using namespace std;

//single interface for all shapes which violates ISP
class Shape{
    public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Square : public Shape {
    private:
    double side;

    public: 
    Square(double s) : side(s) {};

    double area() override {
        return side * side;
    }

    //unnecassry method
    double volume() override {
        throw logic_error("Volume not applicable for Square");
    }
};

class Rectangle : public Shape {
    private:
    double length, width;

    public:
    Rectangle(double l, double w) : length(l), width(w) {};

    double area() override {
        return length*width;
    }

    //unnecassary method 
    double volume() override {
        throw logic_error("Volume not applicable for Recangle");
    }
};

class Cube : public Shape {
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
    Shape* square = new Square(10);
    Shape* rectangle = new Rectangle(10, 50);
    Shape* cube = new Cube(10);

    cout << "Square Area: " << square->area() << endl;
    cout << "Rectangle Area: " << rectangle->area() << endl;
    cout << "Cube Area: " << cube->area() << endl;
    cout << "Cube Volume: " << cube->volume() << endl;

    try{
        cout<<"Square Volume : "<<square->volume()<<endl;
    } catch(logic_error&e){
        cout<<"Exception: "<<e.what()<<endl;
    }
}