#include<iostream>
#include<string>

using namespace std;

class IImage {
    public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
    string filename;
    
    public:
    RealImage(string file){
        this->filename = file;
        cout<<"[Real Image] Loading image from disk : "<<filename <<"\n";
    }

    void display() override {
        cout << "[RealImage] Displaying " << filename << "\n";
    }
};

class ImageProxy : public IImage {
    RealImage* realImage;
    string filename;

    public:
    ImageProxy(string file){
        this->filename = file;
        realImage = nullptr;
    }

    void display() override {
        //Lazy intializaion
        if(!realImage){
            realImage = new RealImage(filename);
        }

        realImage->display();
    }
};

int main(){
    IImage* image1 = new ImageProxy("sample1.png");
    image1->display();
}