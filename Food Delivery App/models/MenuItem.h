#ifndef MENUITEM_H
#define MENUTIEM_H

#include<string>
using namespace std;

class MenuItem {
    private:
    string code;
    string name;
    int price;

    public:
    MenuItem(const string& code, const string& name, const int& price){
        this->code = code;
        this->name = name;
        this->price = price;
    }

    //getter and setters for code
    string getCode() const {
        return code;
    }

    void setCode(const string& c){
        code = c;
    }

    //getter and setter for name;
    string getName() const {
        return name;
    }

    void setName(const string &n){
        name = n;
    }

    //getter and setter for price;
    int getPrice() const {
        return price;
    }

    void setPrice(const int &p){
        price = p;
    }
};


#endif