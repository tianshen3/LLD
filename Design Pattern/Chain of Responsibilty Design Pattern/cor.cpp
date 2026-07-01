#include<iostream>
using namespace std;

//abstract handler (base class)
class MoneyHandler {
    protected :
    MoneyHandler* nextHandler;

    public:
    MoneyHandler(){
        this->nextHandler = nullptr;
    }

    void setNextHandler(MoneyHandler* next){
        nextHandler = next;
    }

    virtual void dispense(int amount) = 0;
};

// concrete class for thousand ruppes
class ThousandHandler : public MoneyHandler {
    private:
    int numNotes;

    public:
    ThousandHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount/1000;

        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else{
            numNotes-=notesNeeded;
        }

        //whatever number of notes that have been given will dispensed
        if(notesNeeded>0){
            cout<<"Dispensing "<<notesNeeded << " x Rs.1000 notes.\n";
        }

        int remainingAmount = amount - (notesNeeded * 1000);
        if(remainingAmount>0){
            if(nextHandler != nullptr){
                nextHandler->dispense(remainingAmount);
            }
            else{
                cout<<"Remaining amount of "<<remainingAmount <<" cannot be fulfilled (insufficient fund in ATM)\n";
            }
        }
    }
};

// Concrete Handler for 500 Rs Notes
class FiveHundredHandler : public MoneyHandler {
private:
    int numNotes;

public:
    FiveHundredHandler(int numNotes) {
        this->numNotes = numNotes;    
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 500;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0)
            cout << "Dispensing " << notesNeeded << " x ₹500 notes.\n";

        int remainingAmount = amount - (notesNeeded * 500);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};

// Concrete Handler for 200 Rs Notes
class TwoHundredHandler : public MoneyHandler {
private:
    int numNotes;

public:
    TwoHundredHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 200;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0)
            cout << "Dispensing " << notesNeeded << " x ₹200 notes.\n";

        int remainingAmount = amount - (notesNeeded * 200);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};

// Concrete Handler for 100 Rs Notes
class HundredHandler : public MoneyHandler {
private:
    int numNotes;

public:
    HundredHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 100;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0)
            cout << "Dispensing " << notesNeeded << " x ₹100 notes.\n";

        int remainingAmount = amount - (notesNeeded * 100);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};

int main(){
    //create Handler for each Note
    MoneyHandler* thousandHandler = new ThousandHandler(3);
    MoneyHandler* fiveHundredHandler = new FiveHundredHandler(10);
    MoneyHandler* twoHundredHandler = new TwoHundredHandler(10);
    MoneyHandler* hundredHandler = new HundredHandler(10);

    //setting up chain of responsibility;
    thousandHandler->setNextHandler(fiveHundredHandler);
    fiveHundredHandler->setNextHandler(twoHundredHandler);
    twoHundredHandler->setNextHandler(hundredHandler);

    int amountToWithdraw = 10000000;

    //Intializing the chain
    cout<<"\nDispensing Amount: Rs"<<amountToWithdraw<<endl;
    thousandHandler->dispense(amountToWithdraw);

}