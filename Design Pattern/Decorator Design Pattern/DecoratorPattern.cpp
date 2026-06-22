#include<iostream>
#include<string>

using namespace std;

//Component Interface: defines a common interface for Mario and all power up decorators.
class Character {
    public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {}
};

//Concrete Component : Basic Mario character with no power ups
class Mario : public Character {
    public:
    string getAbilities() const override {
        return "Mario";
    }
};

//Abstract Decorator : Character Decorator  has "is-a" and "has-a" relation with Character Class;
class CharacterDecorator : public Character {
    protected:
    Character* character; //wrapped component;

    public:
    CharacterDecorator(Character* c)
    {
        this->character = c;
    }
};

//concrete class for the decorator abstract class
class HeightUp : public CharacterDecorator {
    public:
    HeightUp(Character* c) : CharacterDecorator(c){}

    //we are overriding the function received from the inheritance
    string getAbilities() const override {
        return character->getAbilities() + "with HeightUp";
    }
};

// Concrete Decorator: Gun Shooting Power-Up.
class GunPowerUp : public CharacterDecorator {
public:
    GunPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with Gun";
    }
};

// Concrete Decorator: Star Power-Up (temporary ability).
class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with Star Power (Limited Time)";
    }
    
    ~StarPowerUp() {
        cout << "Destroying StarPowerUp Decorator" << endl;
    }
};

int main(){
    Character* mario = new Mario();
    cout<<"Basic Character : "<<mario->getAbilities()<<endl;

    mario = new HeightUp(mario);
    cout<<"After HeightUp :" <<mario->getAbilities()<<endl;

    mario = new GunPowerUp(mario);
    cout<<"After GunPowerUp :"<<mario->getAbilities()<<endl;

    mario = new StarPowerUp(mario);
    cout<<"After StarPowerUp :"<<mario->getAbilities()<<endl;

    delete mario;
}