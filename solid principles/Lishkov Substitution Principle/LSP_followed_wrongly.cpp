#include<iostream>
#include<vector>
using namespace std;

class Account{
    public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;

};

class SavingAccount : public Account {
    private:
    double balance;

    public:
    SavingAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited : " <<amount<<" in Savings Account. New Balance : "<<balance <<endl;
    }

    void withdraw(double amount){
        if(balance >= amount){
            balance -= amount;
            cout<<"Withdraw: "<<amount<<" from Savings Account. New Balance : "<<balance <<endl;
        }
        else{
            cout<<"Insufficient funds to make the withdrawal";
        }
    }
};

class CurrentAccount : public Account {
    private:
    double balance;

    public:
    CurrentAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited : " <<amount<<" in Savings Account. New Balance : "<<balance <<endl;
    }

    void withdraw(double amount){
        if(balance >= amount){
            balance -= amount;
            cout<<"Withdraw: "<<amount<<" from Savings Account. New Balance : "<<balance <<endl;
        }
        else{
            cout<<"Insufficient funds to make the withdrawal";
        }
    }
};

class FixedTermAccount : public Account {
    private:
    double balance;

    public:
    FixedTermAccount() {
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount<<" in Fixed Term Acount. New Balance: "<<balance<<endl;
    }

    void withdraw(double amount){
        throw logic_error("Withdrawal not in allowed in Fixed Term Account!");
    }
};

class BankClient {
    private:
    vector<Account*> accounts;

    public:
    BankClient(vector<Account*> accounts){
        this->accounts = accounts;
    }

    void processTransactions(){
        for(auto acc: accounts){
            acc->deposit(1000);

            //Checking account type explicitly 
            //This is wrong because it shoves the reponsibility of having knowledge/ chekcing to the client
            if(typeid(*acc) == typeid(FixedTermAccount)){
                cout<<"Skipping Withdrawal for Fixed Term Account. \n";
            }
            else{
                try{
                acc->withdraw(500);
                } catch(const logic_error& e){
                    cout<<"Exception "<<e.what()<<endl;
                }
            }
        }
    }

};

int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransactions(); //  Throws exception when withdrawing from FixedTermAccount

    return 0;
}