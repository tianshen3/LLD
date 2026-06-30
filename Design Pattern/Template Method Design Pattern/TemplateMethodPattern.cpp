#include<iostream>
#include<string>

using namespace std;

class ModelTrainer {
    public:
    void trainPipeline(const string& dataPath){
        loadData(dataPath);
        preprocessData();
        trainModel();
        evaluateModel();
        saveModel();
    }

    protected:
    void loadData(const string& path){
        cout<<"[Common] Loading dataset from " << path << "\n";
    }

    virtual void preprocessData() {
        cout<<"[Common] Splitting into train/test and normalizing\n";
    }

    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;
    
    //provide default save button which can be overrided by the subclasses
    virtual void saveModel() {
        cout<<"[Common] Saving model to disk as default fromant\n";
    }

};

//concrete subclass : neural network
class NeuralNetworkTrainer : public ModelTrainer {
    protected:
    void trainModel() override {
        cout<<"[Neural Net] Training Neural Network for 100 epochs\n";
    }

    void evaluateModel() override {
        cout<<"[Neural Net] Evaluating accuracy and loss on validation set\n";
    }

    void saveModel() override {
        cout<<"[Neural Net] Serializing network weights to .h5 file\n";
    }
};

//concrete subclass : Decision Tree
class DecisionTreeTrainer : public ModelTrainer {
    protected :
    void trainModel() override {
        cout<<"[Decision Tree] Building decision tree with max_depth = 5\n";
    }

    void evaluateModel() override {
        cout<<"[Decision Tree] Computing classification report (precision /recall)\n";
    }

    //here using default save model
};


int main() {
    cout << "=== Neural Network Training ===\n";
    ModelTrainer* nnTrainer = new NeuralNetworkTrainer();
    nnTrainer->trainPipeline("data/images/");

    cout << "\n=== Decision Tree Training ===\n";
    ModelTrainer* dtTrainer = new DecisionTreeTrainer();
    dtTrainer->trainPipeline("data/iris.csv");

    return 0;
}