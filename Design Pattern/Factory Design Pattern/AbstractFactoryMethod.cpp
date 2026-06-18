#include<iostream>
using namespace std;

//Product 1 --->Burger
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

//Product2 --->GarlicBread
class GarlicBread {
    public:
    virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread {
    public: 
    void prepare() override {
        cout<<"Preparing Basic Garlic Bread with butter and garlic!\n";
    }
};

class CheeseGarlicBread : public GarlicBread {
    public: 
    void prepare() override {
        cout<<"Preparing Cheese Garlic Bread with extra cheese and butter!"<<endl;
    }
};

class BasicWheatGarlicBread : public GarlicBread {
    public:
    void prepare() override {
        cout<<"Preparing Basic Wheat Garlic Bread with Butter and Garlic"<<endl;
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
    public:
    void prepare() override {
        cout<<"Preparing Cheese Wheat Garlic Bread with butter and Garlic"<<endl;
    }
};

//Abstract Factory class and its concrete subclasses
//These factories cater to more than one product
class FoodFactory {
    public:
    virtual Burger* createBurger(string& type)=0;
    virtual GarlicBread* createGarlicBread(string& type) = 0;
};

class SinghBurger: public FoodFactory {
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

    GarlicBread* createGarlicBread(string& type) override {
        if(type == "basic"){
            return new BasicGarlicBread();
        }
        else if(type == "cheese"){
            return new CheeseGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread Type!"<<endl;
            return nullptr;
        }
    };
};

class KingBurger : public FoodFactory {
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

    GarlicBread* createGarlicBread(string& type){
        if(type == "basic"){
            return new BasicWheatGarlicBread();
        }
        else if(type == "cheese"){
            return new CheeseWheatGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread Type!"<<endl;
            return nullptr;
        }
    }
};

int main(){
    string burgerType = "standard";
    string garlicBreadType = "Cheese";

    FoodFactory* myFactory = new SinghBurger();

    Burger* burger = myFactory->createBurger(burgerType);
    GarlicBread* garlicBread = myFactory->createGarlicBread(garlicBreadType);

    burger->prepare();
    garlicBread->prepare();
}