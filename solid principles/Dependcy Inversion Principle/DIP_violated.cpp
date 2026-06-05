#include<iostream>
using namespace std;

class MySQLDatabase{
    public:
    void saveToSQL(string data){
        cout<<"Executing SQL Query: Inserting into users Values ("<<data<<")"<<endl;
    }
};

class MongoDBDatabase {
    public:
    void savetoMongo(string data){
        cout<<"Executing MongoDB Function: db.users.insert({name"<<data<<"})"<<endl;
    }
};

//This is a high level Module and is tightly coupled with Low level module
class UserService {
    private:
    MySQLDatabase sqldb;
    MongoDBDatabase mongodb;

    public:
    void storeUserToSQL(string user){
        sqldb.saveToSQL(user); //MySQL specific code
    }

    void storeUserToMongo(string user){
        //MonogDB specific code
        mongodb.savetoMongo(user);
    }
};

int main(){
    UserService service;
    service.storeUserToMongo("something");
    service.storeUserToSQL("something2");
}