#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

class HttpRequest {
    private:
    string url;
    string method;
    map<string, string>headers;
    map<string, string> queryParams;
    string body;
    int timeout;

    public:

    //constructor with only 1 arguement passed
    HttpRequest(const string& url){
        this->url = url;
        this->method = "GET";
        this->timeout = 90;
    }

    // 2 - args passed
    HttpRequest(const string& url, string method) {
        this->url = url;
        this->method = method;
        this->timeout = 30;
    }
    
    // 3 - args passed
    HttpRequest(const string& url, string method, int timeout) {
        this->url = url;
        this->method = method;
        this->timeout = timeout;
    }
    
    // 4 - args passed
    HttpRequest(const string& url, string method, int timeout, map<string, string> headers) {
        this->url = url;
        this->method = method;
        this->timeout = timeout;
        this->headers = headers;
    }

    // 5 - args passed
    HttpRequest(const string& url, string method, int timeout, 
        map<string, string> headers, map<string,string> queryParams) {
        this->url = url;
        this->method = method;
        this->timeout = timeout;
        this->headers = headers;
        this->queryParams = queryParams;
    }

    // 6 - args are passed
    HttpRequest(const string& url, string method, int timeout, 
        map<string, string> headers, map<string,string> queryParams, string body) {
        this->url = url;
        this->method = method;
        this->timeout = timeout;
        this->headers = headers;
        this->queryParams = queryParams;
        this->body = body;
    }

    //setters and getters;
    void setUrl(const string& url){
        this->url = url;
    }

    void setMethod(string method){
        this->method = method;
    }

    void addHeader(const string& key, const string& value){
        headers[key] = value;
    }

    void addQueryParam(const string& key, const string& value){
        queryParams[key] = value;
    }

    void setBody(const string& body){
        this->body = body;
    }

    void setTimeout(int timeout){
        this->timeout = timeout;
    }

    //Method to execute the HTTP request;
    void execute() {
        cout<<"Executing"<< method<<" request to "<<url<<endl;

        if(!queryParams.empty()){
            cout<<"Query Parameters: "<<endl;
            for(const auto& param : queryParams){
                cout<<" "<<param.first<<"="<<param.second<<endl;
            }
        }   

        cout<<"Headers: "<<endl;
        for(const auto& header: headers){
            cout<<" "<<header.first<<": "<<header.second<<endl;
        }

        if(!body.empty()){
            cout<<"Body: "<<body<<endl;
        }

        cout<<"Timeout: "<<timeout<<"seconds"<<endl;
        cout<<"Request executed successfully! "<<endl;
    }


};

int main(){
    // Using constructors can lead to constructor overloading which for larger no. of parameter is a problem
    HttpRequest* request1 = new HttpRequest("https://api.example.com");
    HttpRequest* request2 = new HttpRequest("https://api.example.com", "POST");
    HttpRequest* request3 = new HttpRequest("https://api.example.com", "PUT", 60);
    
    // Using setters (mutable object problem)
    HttpRequest* request4 = new HttpRequest("https://api.example.com");
    request4->setMethod("POST");
    request4->addHeader("Content-Type", "application/json");
    request4->addQueryParam("key", "12345");
    request4->setBody("{\"name\": \"Aditya\"}");
    request4->setTimeout(60);
    
    // if important field is not set then might lead to inconsistent state problem
    request4->execute();
}
