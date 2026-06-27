#pragma once
#include<string>
#include<iostream>

using namespace std;

class HeadPhonesAPI {
    public:
    void playSoundViaJack(const string& data){
        cout<<"[Headphones] Playing: "<< data << "\n";

    }
};

