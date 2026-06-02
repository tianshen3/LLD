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

class Persistance{
    private: 
    ShoppingCart* cart;

    public:
    virtual void save(ShoppingCart* cart);
};

class SQLPersistance : public Persistance{
    public:
    void save(ShoppingCart* cart) override {
        cout<<"Saving to SQL DB"<<endl;
    }
};

class MongoPersistence : public Persistance {
public:
    void save(ShoppingCart* cart) override {
        cout << "Saving to MongoDB..." << endl;
    }
};

class FilePersistence : public Persistance {
public:
    void save(ShoppingCart* cart) override {
        cout << "Saving to a file..." << endl;
    }
};

int main() {
    ShoppingCart* cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInovice();

   

    return 0;
}