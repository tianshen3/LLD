#include<iostream>
#include<vector>
using namespace std;

class Product {
    public: 
    string name;
    double price;

    Product(string name, double price){
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart{
    private:
    vector<Product *> products;

    public: 
    void addProduct(Product* p){
        products.push_back(p);
    }

    const vector<Product*>& getProducts(){
        return products;
    }

    double calculateTotal(){
        double total = 0;
        for(auto p : products){
            total += p->price;
        }

        return total;
    }
};

class ShoppingCartPrinter {
    private:
    ShoppingCart* cart;

    public: 
    ShoppingCartPrinter(ShoppingCart *cart){
        this->cart = cart;
    }

    void printInovice() {
        cout<<"Shopping Cart Inovice:\n";
        for(auto p: cart->getProducts()){
            cout<<p->name<<" -Rs."<< p->price<<endl;
        }

        cout<<"Total: Rs"<< cart->calculateTotal()<<endl;
    }
};

//here storage violates the ocp because if added another method of storage then 
//this class needs to be modified which just violates the ocp principle
class ShoppingCartStorage {
    private: 
    ShoppingCart* cart;

    public:
    ShoppingCartStorage(ShoppingCart* cart){
        this->cart = cart;
    }

    void saveToSQLDatabase(){
        cout<<"Saving to SQL DB..."<<endl;
    }

    void saveToMongoDatabase(){
        cout<<"Saving to Mongo DB..."<<endl;
    }

    void saveToFIle(){
        cout<<"Saving to File.."<<endl;
    }
};

int main() {
    ShoppingCart* cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInovice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToSQLDatabase();

    return 0;
}