#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//in cpp, an interface is implemented as an abstract class containing only pure virtaul functions
//to denote this the first letter is "I"
class ISubscriber {
    public:
    virtual void update() = 0;
    virtual ~ISubscriber() {}
};

//an abstract observable interface
class IChannel {
    public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) =0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};

//Concrete Obervable
class Channel : public IChannel {
    private:
    vector<ISubscriber*> subscribers; //list of subscribers
    string name;  // the name of a current channel
    string latestVideo; // the name of the latest uploaded video;
    
    public:
    Channel(const string &name){
        this->name = name;
    }

    //adding a subscriber and avoid duplication
    void subscribe(ISubscriber* subscriber) override {
        if(find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()){
            subscribers.push_back(subscriber);
        }
    }

    //removing a subscriber if present
    void unsubscribe(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if(it != subscribers.end()){
            subscribers.erase(it);
        }
    }

    //notify all subscriber of the currently newly added video
    void notifySubscribers() override {
        for(ISubscriber* sub : subscribers){
            sub->update();
        }
    }

    //upload a new video and notify subscribers;
    void uploadVideo(const string& title){
        latestVideo = title;
        cout<<"\n[" << name << "uploaded\"" <<title << "\"]\n";
        notifySubscribers();
    }

    //read the video the data
    string getVideoData() {
        return "\nCheckout our new Video : "+ latestVideo + "\n";
    }
}; 

//Concrete Observer: represents a subscriber to the channel
class Subscriber : public ISubscriber {
    private: 
    string name;
    Channel* channel;

    public:
    Subscriber(const string& name, Channel* channel){
        this->name = name;
        this->channel = channel;
    }

    void update() override {
        cout<<"Hey "<<name<<","<<this->channel->getVideoData();
    }
};

int main(){
    // Create a channel and subscribers
    Channel* channel = new Channel("HellHole");

    Subscriber* subs1 = new Subscriber("Van", channel);
    Subscriber* subs2 = new Subscriber("Max", channel);

    // Varun and Tarun subscribe to CoderArmy
    channel->subscribe(subs1);
    channel->subscribe(subs2);

    // Upload a video: both Varun and Tarun are notified
    channel->uploadVideo("Observer Pattern Tutorial");

    // Varun unsubscribes; Tarun remains subscribed
    channel->unsubscribe(subs1);

    // Upload another video: only Tarun is notified
    channel->uploadVideo("Decorator Pattern Tutorial"); 
}