#include<iostream>
using namespace std;

//abstract class of product and its various concrete sub classes
class Burger {
    public:
    virtual void prepare() = 0;
    virtual ~Burger() {}
};

class BasicBurger : public Burger {
    public:
    void prepare() override {
        cout<<"Preparing Basic Burger with bun , patty, and ketchup!"<<endl;
    }
};

class StandardBurger : public Burger {
    public:
    void prepare() override {
        cout<<"Preparing Standard Burger with bun, patty, cheese, and lettuce!"<<endl;
    }
};

class PremiumBurger : public Burger {
    public:
    void prepare() override {
        cout<<"Preparing Premium Burger with Gourmet bun, premium patty, cheese, lettuce, and secret sauce and lots of love"<<endl;
    }
};

class BasicWheatBurger : public Burger {
    public: 
    void prepare() override {
        cout<<"Preparing Basic Wheat Burger with bun, patty, and ketchup!" <<endl;
    }
};

class StandardWheatBurger : public Burger {
    public: 
    void prepare() override {
        cout<<"Preparing Standard Wheat Burger with bun, patty, cheese, and lettuce!"<<endl;
    }
};

class PremiumWheatBurger : public Burger {
    public:
    void prepare() override {
        cout<<"Preparing Premium Wheat Burger with bun, patty, cheese, and lettuce!"<<endl;
    }
};

//Abstract Factory class and its concrete subclasses
class BurgerFactory {
    public:
    virtual Burger* createBurger(string& type)=0;
};

class SinghBurger: public BurgerFactory {
    public:
    Burger* createBurger(string& type){
        if(type=="basic"){
            return new BasicBurger();
        }
        else if(type == "standard"){
            return new StandardBurger();
        }
        else if(type == "PremiumBurger"){
            return new PremiumBurger();
        }
        else{
            cout<<"Invalid Burger Type!"<<endl;
            return nullptr;
        }
    }
};

class KingBurger : public BurgerFactory {
    public:
    Burger* createBurger(string& type){
        if(type=="basic"){
            return new BasicWheatBurger();
        }
        else if(type == "standard"){
            return new StandardWheatBurger();
        }
        else if(type == "PremiumBurger"){
            return new PremiumWheatBurger();
        }
        else{
            cout<<"Invalid Burger Type!"<<endl;
            return nullptr;
        }
    }
};

int main(){
    string type = "standard";
    BurgerFactory* myBurgerFactory = new SinghBurger();
    Burger* burger = myBurgerFactory->createBurger(type);
    burger->prepare();
}