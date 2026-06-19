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
            if(instance == nullptr){ //second check is there 
                //when thread A already creates an object thread B is not able to do anything
                instance = new Singleton();
            }
        }
        return instance;
    }
};

//Intializing the static member 
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout<< (s1 == s2) <<endl;
}