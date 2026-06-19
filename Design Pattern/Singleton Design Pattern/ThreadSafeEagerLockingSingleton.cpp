#include<iostream>
#include<mutex>
using namespace std;

class Singleton {
    private:

    static Singleton* instance;
    static mutex mtx;

    Singleton(){
        cout<<"Singleton Constructor is called."<<endl;
    }

    public:
    //double check locking
    static Singleton* getInstance(){
        if(instance == nullptr){ // first check (no locking)
            lock_guard<mutex> lock(mtx); //lock if needed
            if(instance == nullptr){ 
                instance = new Singleton();
            }
        }
        return instance;
    }
};

//Intializing the static member 
Singleton* Singleton::instance = new Singleton(); //but this is expensive and should only be used in case you know there is a need for singleton class


int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout<< (s1 == s2) <<endl;
}