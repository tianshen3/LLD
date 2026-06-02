#include<iostream>
#include<vector>
using namespace std;

class Product {
    public: 
    string name;
    double price;

    //constructor of the Product class
    Product(string name, double price){
        this->name = name;
        this->price = price;    
    }
};


class ShoppingCart {
private:
    vector<Product*> products;

public:
    //adding a product to the cart
    void addProduct(Product *p){
        products.push_back(p);
    }

    //getting list of all the products in the cart
    const vector<Product *>& getProducts() {
        return products;
    }

    //calculating the total of the cart value
    double calculateTotal() {
        double total = 0;
        for(auto p: products){
            total += p->price;
        }
        return total;
    }
    //the above 3 are not violating SRP because they are the part of the cart's business logic
    //essentially the same shared responsibilty to make the cart functioning
    //but printing an inovice is entirely a different duty all together

    //printing inovice (violating SRP )
    void printInovice(){
        cout<<"Shopping Cart Inovice: \n";
        for(auto p: products){
            cout<<p->name<<" -Rs "<< p->price <<endl;
        }

        cout<<"Total: Rs "<< calculateTotal() <<endl; 
    }

    //saving the cart to DB (violating SRP)
    void saveToDB() {
        cout<<"Saving shopping cart to database.. "<<endl;
    }
};