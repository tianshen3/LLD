#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<iomanip>

using namespace std;

//forward declarations
class User;
class Group;
class ExpenseManger;

enum class SplitType{
    EQUAL,
    EXACT,
    PERCENTAGE
};

//model class
class Split {
    public:
    string userId;
    double amount;

    Split(const string& userId, double amount){
        this->userId = userId;
        this->amount = amount;
    }
};

//observer Design Pattern for Notification System
class Observer {
    public:
    virtual void update(const string& message) = 0;
};

//strategy pattern for split strategies
class SplitStrategy {
    public:
    virtual vector<Split> calculateSplit(double totalAmount, const vector<string>& userIds,
                                            const vector<double>& values = {}) = 0;
};

class EqualSplit : public SplitStrategy {
public:
    vector<Split> calculateSplit(double totalAmount, const vector<string>& userIds, 
                               const vector<double>& values = {}) override {
        vector<Split> splits;
        double amountPerUser = totalAmount / userIds.size();
        
        for (const string& userId : userIds) {
            splits.push_back(Split(userId, amountPerUser));
        }
        return splits;
    }
};

class ExactSplit : public SplitStrategy {
public:
    vector<Split> calculateSplit(double totalAmount, const vector<string>& userIds, 
                               const vector<double>& values = {}) override {
        vector<Split> splits;

        //validations
        
        for (int i = 0; i < userIds.size(); i++) {
            splits.push_back(Split(userIds[i], values[i]));
        }
        return splits;
    }
};

class PercentageSplit : public SplitStrategy {
public:
    vector<Split> calculateSplit(double totalAmount, const vector<string>& userIds, 
                               const vector<double>& values = {}) override {
        vector<Split> splits;

        //validations
        
        for (int i = 0; i < userIds.size(); i++) {
            double amount = (totalAmount * values[i]) / 100.0;
            splits.push_back(Split(userIds[i], amount));
        }
        return splits;
    }
};

//factory for stratgies
class SplitFactory {
    public:
    static SplitStrategy* getSplitStrategy(SplitType type){
        switch(type){
            case SplitType::EQUAL:
                return new EqualSplit();
            case SplitType::EXACT:
                return new ExactSplit();
            case SplitType::PERCENTAGE:
                return new PercentageSplit();
            default:
                return new EqualSplit();
        }
    }
};

//user a concrete observer
class User : public Observer {
    public:
    static int nextUserId;
    string userId;
    string name;
    string email;
    map<string, double>balances;
    
    User(const string& name, const string& email){
        this->userId = "user" + to_string(++nextUserId);
        this->name = name;
        this->email = email;
    }

    void updateBalance(const string& otherUserId, double amount) {
        balances[otherUserId] += amount;
        
        // Remove if balance becomes zero
        if (abs(balances[otherUserId]) < 0.01) {
            balances.erase(otherUserId);
        }
    }

    double getTotalOwed() {
        double total = 0;
        for(const auto & balance: balances){
            if(balance.second <0){
                total += abs(balance.second);
            }
        }

        return total;
    }

    double getTotalOwing() {
        double total = 0;
        for(const auto & balance : balances){
            if(balance.second>0){
                total += balance.second;
            }
        }

        return total;
    }
};

int User::nextUserId = 0;

//Expense Model Class
class Expense {
    public:
    static int nextExpenseId;
    string expenseId;
    string description;
    double totalAmount;
    string paidByUserId;
    vector<Split> splits;
    string groupId;

    Expense(const string& desc, double amount, const string& paidBy,
            vector<Split>& splits, const string group="") {
        this->expenseId = "expense" + std::to_string(++nextExpenseId);
        this->description = desc;
        this->totalAmount = amount;
        this->paidByUserId = paidBy;
        this->splits = splits;
        this->groupId = group;
    }
};
int Expense::nextExpenseId = 0;

class Group {
private:
    User* getUserByuserId(string userId) {
        User* user = nullptr;

        for(User *member : members) {
            if(member->userId == userId) {
                user = member;
            }
        }
        return user;
    }
    
public:
    static int nextGroupId;
    string groupId;
    string name;
    vector<User*> members; //observers
    map<string, Expense*> groupExpenses; // Group's own expense book
    map<string, map<string, double>> groupBalances; // memberId -> {otherMemberId -> balance}
    
    Group(const string& name) {
        this->groupId = "group" + std::to_string(++nextGroupId);
        this->name = name;
    }
    
    ~Group() {
        // Clean up group's expenses
        for (auto& pair : groupExpenses) {
            delete pair.second;
        }
    }
    
    void addMember(User* user) {
        members.push_back(user);

        // Initialize balance map for new member
        groupBalances[user->userId] = map<string, double>();
        cout << user->name << " added to group " << name << endl;
    }
    
    bool removeMember(const string& userId) {    
        // Check if user can be removed or not
        if(!canUserLeaveGroup(userId)) {
            cout <<"\nUser not allowed to leave group without clearing expenses" << endl;
            return false;
        }
        
        // Remove from observers
        for (User *user : members) {
            if (user->userId == userId) {
                members.erase(remove(members.begin(), members.end(), user),members.end());
                break;
            }
        }
        
        // Remove from group balances
        groupBalances.erase(userId);
        
        // Remove this user from other members' balance maps
        for (auto& memberBalance : groupBalances) {
            memberBalance.second.erase(userId);
        }
        return true;
    }
    
    void notifyMembers(const string& message) {
        for (Observer* observer : members) {
            observer->update(message);
        }
    }

    bool isMember(const string& userId) {
        return groupBalances.find(userId) != groupBalances.end();
    }
    
    // Update balance within group
    void updateGroupBalance(const string& fromUserId, const string& toUserId, double amount) {
        groupBalances[fromUserId][toUserId] += amount;
        groupBalances[toUserId][fromUserId] -= amount;
        
        // Remove if balance becomes zero
        if (abs(groupBalances[fromUserId][toUserId]) < 0.01) {
            groupBalances[fromUserId].erase(toUserId);
        }
        if (abs(groupBalances[toUserId][fromUserId]) < 0.01) {
            groupBalances[toUserId].erase(fromUserId);
        }
    }
    
    // Check if user can leave group.
    bool canUserLeaveGroup(const string& userId) {
        if (!isMember(userId)) {
            throw runtime_error("user is not a part of this group");
        };
        
        // Check if user has any outstanding balance with other group members
        map<string, double> userBalanceSheet = groupBalances[userId];
        for (auto& balance : userBalanceSheet) {
            if (abs(balance.second) > 0.01) {
                return false; // Has outstanding balance
            }
        }
        return true;
    }
    
    // Get user's balance within this group
    map<string, double> getUserGroupBalances(const string& userId) {
        if (!isMember(userId)) {
            throw runtime_error("user is not a part of this group");
        };
        return groupBalances[userId];
    }
    
    // Add expense to this group
    bool addExpense(string& description, double amount, string& paidByUserId,
                   vector<string>& involvedUsers, SplitType splitType, 
                   const vector<double>& splitValues = {}) {
        
        if (!isMember(paidByUserId)) {
            throw runtime_error("user is not a part of this group");
        }
        
        // Validate that all involved users are group members
        for (const string& userId : involvedUsers) {
            if (!isMember(userId)) {
                throw runtime_error("involvedUsers are not a part of this group");
            }
        }
        
        // Generate splits using strategy pattern
        vector<Split> splits = SplitFactory::getSplitStrategy(splitType)
                                ->calculateSplit(amount, involvedUsers, splitValues);
        
        // Create expense in group's own expense book
        Expense* expense = new Expense(description, amount, paidByUserId, splits, groupId);
        groupExpenses[expense->expenseId] = expense;
        
        // Update group balances
        for (Split& split : splits) {
            if (split.userId != paidByUserId) {
                // Person who paid gets positive balance, person who owes gets negative
                updateGroupBalance(paidByUserId, split.userId, split.amount);
            }
        }
        
        cout << endl << "=========== Sending Notifications ===================="<<endl;
        string paidByName = getUserByuserId(paidByUserId)->name;
        notifyMembers("New expense added: " + description + " (Rs " + to_string(amount) + ")");
        
        // Printing console message-------
        cout << endl << "=========== Expense Message ===================="<<endl;
        cout << "Expense added to " << name << ": " << description << " (Rs " << amount 
             << ") paid by " << paidByName <<" and involved people are : "<< endl;
        if(!splitValues.empty()) {
            for(int i=0; i<splitValues.size(); i++) {
                cout << getUserByuserId(involvedUsers[i])->name << " : " << splitValues[i] << endl;
            }
        } 
        else {
            for(string user : involvedUsers) {
                cout << getUserByuserId(user)->name << ", ";
            }
            cout << endl << "Will be Paid Equally" << endl;
        }    
        //-----------------------------------
        
        return true;
    }
    
    bool settlePayment(string& fromUserId, string& toUserId, double amount) {
        // Validate that both users are group members
        if (!isMember(fromUserId) || !isMember(toUserId)) {
            cout << "user is not a part of this group" << endl;
            return false;
        }
        
        // Update group balances
        updateGroupBalance(fromUserId, toUserId, amount);
        
        // Get user names for display
        string fromName = getUserByuserId(fromUserId)->name;
        string toName = getUserByuserId(toUserId)->name;
        
        // Notify group members
        notifyMembers("Settlement: " + fromName + " paid " + toName + " Rs " + to_string(amount));
        
        cout << "Settlement in " << name << ": " << fromName << " settled Rs " 
             << amount << " with " << toName << endl;
        
        return true;
    }
    
    void showGroupBalances() {
        cout << "\n=== Group Balances for " << name << " ===" << endl;
        
        for (const auto& pair : groupBalances) {
            string memberId = pair.first;
            string memberName = getUserByuserId(memberId)->name;

            cout << memberName << "'s balances in group:" << endl;
            
            auto userBalances = pair.second;
            if (userBalances.empty()) {
                cout << "  No outstanding balances" << endl;
            } 
            else {
                for (const auto& userBalance : userBalances) {
                    string otherMemberUserId = userBalance.first;
                    string otherName = getUserByuserId(otherMemberUserId)->name;
                    
                    double balance = userBalance.second;
                    if (balance > 0) {
                        cout << "  " << otherName << " owes: Rs " << fixed << setprecision(2) << balance << endl;
                    } else {
                        cout << "  Owes " << otherName << ": Rs " << fixed << setprecision(2) << abs(balance) << endl;
                    }
                }
            }
        }
    }

    void simplifyGroupDebts() {
        map<string, map<string, double>> simplifiedBalances = DebtSimplifier::simplifyDebts(groupBalances);
        groupBalances = simplifiedBalances;
    
        cout << "\nDebts have been simplified for group: " << name << endl;
    }
};
int Group::nextGroupId = 0;
    
// Main ExpenseManager class (Singleton - Facade)
class Splitwise {
private:
    map<string, User*> users;
    map<string, Group*> groups;
    map<string, Expense*> expenses;

    static Splitwise* instance;
    Splitwise() {}
    
public:
    static Splitwise* getInstance() {
        if(instance == nullptr) {
            instance = new Splitwise();
        }
        return instance;
    }

    // User management
    User* createUser(string name, string email) {
        User* user = new User(name, email);
        users[user->userId] = user;
        cout << "User created: " << name << " (ID: " << user->userId << ")" << endl;
        return user;
    }
    
    User* getUser(const string& userId) {
        auto it = users.find(userId);
        return (it != users.end()) ? it->second : nullptr;
    }
    
    // Group management
    Group* createGroup(const string name) {
        Group* group = new Group(name);
        groups[group->groupId] = group;
        cout << "Group created: " << name << " (ID: " << group->groupId << ")" << endl;
        return group;
    }
    
    Group* getGroup(const string& groupId) {
        auto it = groups.find(groupId);
        return (it != groups.end()) ? it->second : nullptr;
    }
    
    void addUserToGroup(const string& userId, const string& groupId) {
        User* user = getUser(userId);
        Group* group = getGroup(groupId);
        
        if (user && group) {
            group->addMember(user);
        }
    }
    
    // Try to remove user from group - just delegates to group
    bool removeUserFromGroup(const string& userId, const string& groupId) {
        Group* group = getGroup(groupId);
        
        if (!group) {
            cout << "Group not found!" << endl;
            return false;
        }
        
        User* user = getUser(userId);
        if (!user) {
            cout << "User not found!" << endl;
            return false;
        }

        bool userRemoved = group->removeMember(userId);
        
        if(userRemoved) {
            cout << user->name << " successfully left " << group->name << endl;
        }
        return userRemoved;
    }
    
    // Expense management - delegate to group
    void addExpenseToGroup(string& groupId, string description, double amount, 
                          string& paidByUserId, vector<string>& involvedUsers, 
                          SplitType splitType, const vector<double>& splitValues = {}) {
        
        Group* group = getGroup(groupId);
        if (!group) {
            cout << "Group not found!" << endl;
            return;
        }
        
        group->addExpense(description, amount, paidByUserId, involvedUsers, splitType, splitValues);
    }
    
    // Settlement - delegate to group
    void settlePaymentInGroup(string& groupId, string& fromUserId, 
                              string& toUserId, double amount) {
        
        Group* group = getGroup(groupId);
        if (!group) {
            cout << "Group not found!" << endl;
            return;
        }
        
        group->settlePayment(fromUserId, toUserId, amount);
    }
    
    // Settlement
    void settleIndividualPayment(string& fromUserId, string& toUserId, double amount) {
        User* fromUser = getUser(fromUserId);
        User* toUser = getUser(toUserId);
        
        if (fromUser && toUser) {
            fromUser->updateBalance(toUserId, amount);
            toUser->updateBalance(fromUserId, -amount);
            
            cout << fromUser->name << " settled Rs" << amount << " with " << toUser->name << endl;
        }
    }
    
    void addIndividualExpense(string description, double amount, string paidByUserId,
                             string toUserId, SplitType splitType,
                            const vector<double>& splitValues = {}) {

        SplitStrategy* strategy = SplitFactory::getSplitStrategy(splitType);
        vector<Split> splits = strategy->calculateSplit(amount, {paidByUserId, toUserId}, splitValues);

        Expense* expense = new Expense(description, amount, paidByUserId, splits);
        expenses[expense->expenseId] = expense;
        
        User* paidByUser = getUser(paidByUserId);
        User* toUser = getUser(toUserId);

        paidByUser->updateBalance(toUserId, amount);
        toUser->updateBalance(paidByUserId, -amount);
        
        cout << "Individual expense added: " << description << " (Rs " << amount 
                << ") paid by " << paidByUser->name <<" for " << toUser->name << endl;
    }
    
    // Display Method
    void showUserBalance(string& userId) {
        User* user = getUser(userId);
        if (!user) return;
        
        cout << endl << "=========== Balance for " << user->name <<" ===================="<<endl; 
        cout << "Total you owe: Rs " << fixed << setprecision(2) << user->getTotalOwed() << endl;
        cout << "Total others owe you: Rs " << fixed << setprecision(2) << user->getTotalOwing() << endl;
        
        cout << "Detailed balances:" << endl;
        for (auto& balance : user->balances) {
            User* otherUser = getUser(balance.first);
            if (otherUser) {
                if (balance.second > 0) {
                    cout << "  " << otherUser->name << " owes you: Rs" << balance.second << endl;
                } else {
                    cout << "  You owe " << otherUser->name << ": Rs" << abs(balance.second) << endl;
                }
            }
        }
    }
    
    void showGroupBalances(string& groupId) {
        Group* group = getGroup(groupId);
        if (!group) return;
        
        group->showGroupBalances();
    }
    
    void simplifyGroupDebts(string& groupId) {
        Group* group = getGroup(groupId);
        if (!group) return;
                
        // Use group's balance data for debt simplification
        group->simplifyGroupDebts();
    }
};

Splitwise* Splitwise::instance = nullptr;

int main() {
    
    // add simplify group debt class;
}