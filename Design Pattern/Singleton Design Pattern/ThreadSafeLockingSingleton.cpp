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
    static Singleton* getInstance(){
        lock_guard<mutex> lock(mtx); // a lock for thread safety
        if(instance == nullptr){
            instance = new Singleton();
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