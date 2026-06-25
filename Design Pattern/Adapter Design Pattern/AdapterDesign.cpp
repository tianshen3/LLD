#include<iostream>
#include<string>

using namespace std;

//Interface expected by the client
class IReports {
    public:
    virtual string getJsonData(const string& data) = 0;
    virtual ~IReports() {}
};

//Adaptee: provides XML data from a raw input
class XmlDataProvider{
    public:
    string getXmlData(const string& data){
        size_t sep = data.find(':');
        string name = data.substr(0, sep);
        string id = data.substr(sep+1);

        //build xml representation
        return "<user>"
                "<name>" + name + "/name>"
                "<id>"+id+"</id>"
                "</user>";
    }
};

//adapter : implements IReports by converting XML to JSON
class XmlDataProviderAdapter : public IReports {
    private:
    XmlDataProvider* xmlProvider;

    public:
    XmlDataProviderAdapter(XmlDataProvider* provider){
        this->xmlProvider = provider;
    }

    string getJsonData(const string& data) override {
        string xml = xmlProvider->getXmlData(data);

        //parse out <name> and <id> values;
        size_t  startName = xml.find("<name>") + 6;
        size_t endName = xml.find("</name>");
        string name = xml.substr(startName, endName-startName);

        size_t startId = xml.find("<id>") + 4;
        size_t endId   = xml.find("</id>");
        string id      = xml.substr(startId, endId - startId);

        return "{\"name\":\""+name+ "\", \"id\":" + id + "}";
    }


};

class Client {
public:
    void getReport(IReports* report, string rawData) {
        cout << "Processed JSON: "
        << report->getJsonData(rawData)
        << endl;
    }
};

int main() {
    // 1. Create the adaptee
    XmlDataProvider* xmlProv = new XmlDataProvider();

    // 2. Make our adapter
    IReports* adapter = new XmlDataProviderAdapter(xmlProv);

    // 3. Give it some raw data
    string rawData = "Alice:42";

    // 4. Client prints the JSON
    Client* client = new Client();
    client->getReport(adapter, rawData);
    // → Processed JSON: {"name":"Alice", "id":42}

    // 5. Cleanup
    delete adapter;
    delete xmlProv;
    return 0;
}