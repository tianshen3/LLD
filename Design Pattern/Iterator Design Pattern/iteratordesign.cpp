#include<iostream>
#include<vector>
#include<stack>
#include<string>

using namespace std;

template<typename T>
class Iterator {
    public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template<typename T>
class Iterable {
    virtual Iterator<T>* getIterator() = 0;
};

//Linked List
class LinkedList : public Iterable<int> {
    public:
    int data;
    LinkedList* next;

    LinkedList(int value) {
        data = value;
        next = nullptr;
    }

    Iterator<int>* getIterator() override;
};

class LinkedListIterator : public Iterator<int> {
    private:
        LinkedList* current;

    public:
    LinkedListIterator(LinkedList* head){
        current = head;
    }

    bool hasNext() override {
        return current!=nullptr;
    }

    int next() override {
        int val = current->data;
        current = current->next;
        return val;
    }
};

int main(){
    LinkedList* list = new LinkedList(1);
    list->next = new LinkedList(2);
    list->next->next = new LinkedList(3);

    Iterator<int>* iterator1 = list->getIterator();

    cout << "LinkedList contents: ";

    while (iterator1->hasNext()) {
        cout << iterator1->next() << " ";
    }

    cout << "\n";
}




