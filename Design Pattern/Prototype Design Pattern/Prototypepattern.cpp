#include<iostream>
#include<string>
#include<vector>
using namespace std;

//Prototype Interface
class Cloneable {
    public:
    virtual Cloneable* clone() const = 0;
    virtual ~Cloneable() {}
};

class NPC : public Cloneable {
    public:
    string name;
    int health;
    int attack;
    int defense;

    //this type of constructor call can be expnesive
    NPC(const string& name, int health, int attack, int defense){
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        cout<<"Setting up template NPC ' "<<name <<" '\n";
    }

    //copy constructor
    NPC(const NPC& other){
        name = other.name;
        health = other.health;
        attack = other.attack;
        defense = other.defense;
        cout << "Cloning NPC '" << name << "'\n";
    }

    //the clone method required by Prototype
    Cloneable* clone() const override {
        return new NPC(*this);
    }

    void describe() {
        cout << "NPC " << name  << " [HP=" << health  << " ATK=" << attack 
             << " DEF=" << defense << "]\n";
    }

    // setters to tweak the clone…
    void setName(const string& n) { 
        name = n;
    }
    void setHealth(int h) { 
        health = h;
    }
    void setAttack(int a) {
         attack = a; 
    }
    void setDefense(int d){ 
        defense = d;
    }
};

int main() {
    NPC* boy = new NPC("Ra", 30, 5, 2);

    //cloning this boy to be a normal NPC
    NPC* copiedBoy1 = dynamic_cast<NPC*>(boy->clone());
    copiedBoy1->describe();

    //again cloning the boy but this time to be a hero
    NPC* copiedBoy2 = dynamic_cast<NPC*>(boy->clone());
    copiedBoy2->setName("Hero");
    copiedBoy2->setHealth(60);
    copiedBoy2->describe();

}
