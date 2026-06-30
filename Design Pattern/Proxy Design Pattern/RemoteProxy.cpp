#include<iostream>
#include<string>

using namespace std;

class IDataService {
    public:
    virtual string fetchData() = 0;
    virtual ~IDataService() = default;
};

class RealDataService : public IDataService {
    public:
    RealDataService(){
        //This real data service connects to remote server or loads a heavy resources.
        cout<<"[RealDataService] Initalized (simulating remote setup)\n";
    }

    string fetchData() override {
        cout<<"[RealDataService] Data from server";
    }
};

class DataServiceProxy : public IDataService {
    private:
    RealDataService* realService;

    public:
    //this is lazy intialization of service to optimize for expensive object creation
    DataServiceProxy(){
        this->realService = nullptr;
    }


    string fetchData() override {
        if(!realService){
            realService = new RealDataService();
        }

        return realService->fetchData();
    }
};


int main() {
    IDataService* dataService = new DataServiceProxy();
    dataService->fetchData();
}