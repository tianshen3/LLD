#ifndef CART_H
#define CART_H

#include<iostream>
#include<vector>
#include<string>
#include "MenuItem.h"
#include "Restaurant.h"
using namespace std;

class Cart {
    private:
    Restaurant* restaurant;
    vector<MenuItem> items;

    public:
    Cart(){
        restaurant = nullptr;
    }

    void addItem(const MenuItem &item){
        if(!restaurant){
            cout<<"Cart: Set a restaurant before adding items."<<endl;
            return;
        }
        items.push_back(item);
    }

    double getTotalCost() const {
        double sum = 0;
        for(const auto &it: items){
            sum += it.getPrice();
        }
    }

    bool isEmpty(){
        return (!restaurant || items.empty());
    }

    void clear() {
        items.clear();
        restaurant = nullptr;
    }

    //getters and setters

    void setRestaurant(Restaurant* r){
        restaurant = r;
    }

    Restaurant* getRestaurant() const {
        return restaurant;
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }
};

#endif