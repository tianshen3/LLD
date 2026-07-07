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

    //private empty constructor because we don't want the client to create a object of this type using new keyword directly
    HttpRequest() {}

    public:
    //essentially allowing this class to access the private members of the HttpRequest class
    friend class HttpRequestBuilder;
   

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

class HttpRequestBuilder {
    private:
    HttpRequest req;

    public:
    //method chaining
    HttpRequestBuilder& withUrl(const string& u){
        req.url = u;
        return *this;
    }

    HttpRequestBuilder& withMethod(string method){
        req.method = method;
        return *this;
    }

    HttpRequestBuilder& withHeader(const string& key, const string& value){
        req.headers[key] = value;
        return *this;
    }

    HttpRequestBuilder& withQueryParams(const string& key, const string& value){
        req.queryParams[key] = value;
        return *this;
    }

    HttpRequestBuilder& withBody(const string& body){
        req.body = body;
        return *this;
    }

    HttpRequestBuilder& withTimeout(int timeout){
        req.timeout = timeout;
        return *this;
    }

    //build method to create the immutable http request
    HttpRequest build() {
        if(req.url.empty()){
            throw runtime_error("URL cannot be empty");
        }

        return req;
    }


};

int main(){
    //using builder pattern
    HttpRequest request = HttpRequestBuilder()
        .withUrl("https://api.example.com")
        .withMethod("POST")
        .withHeader("Content-Type", "application/json")
        .withHeader("Accept", "application/json")
        .withQueryParams("key", "12345")
        .withBody("{\"name\": \"Aditya\"}")
        .withTimeout(60)
        .build();

    request.execute(); // Guaranteed to be in a consistent state
}
