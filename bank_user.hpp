#include<iostream>
#include<vector>
#include"transaction.hpp"
#include"user_auth.cpp"

using namespace std;
//create a bank user account class with the following attributes:
//name, address, phone number, account number, balance, transaction history, and a deposit and withdraw function.
class bank_user:public user_auth{
    private:
        string name;
        string address;
        string phone_number;
        string account_number;
        double balance;
        //transaction history is an vector of transaction class objects
        vector<transaction> transaction_history;
    public:
        bank_user(){}
        //constructor
        bank_user(string name, string address, string phone_number, int account_number, double balance){
            this->name = name;
            this->address = address;
            this->phone_number = phone_number;
            this->account_number = account_number;
            this->balance = balance;
        }
        //getters
        string get_name(){
            return name;
        }
        string get_address(){
            return address;
        }
        string get_phone_number(){
            return phone_number;
        }
        string get_account_number(){
            return account_number;
        }
        double get_balance(){
            return balance;
        }
        vector<transaction> get_transaction_history(){
            return transaction_history;
        }
        //setters
        void set_name(string name){
            this->name = name;
        }
        void set_address(string address){
            this->address = address;
        }
        void set_phone_number(string phone_number){
            this->phone_number = phone_number;
        }
        void set_account_number(int account_number){
            this->account_number = account_number;
        }
        void set_balance(double balance){
            this->balance = balance;
        }
        void set_transaction_history(vector<transaction> transaction_history){
            this->transaction_history = transaction_history;
        }
        //deposit money into the account

        
        
        bool getUserInfo(){
            try{
                if(getAuthToken()!="0"){
                //fetch and assign user info from server
                //fetch user info from server
                //assign user info to the user object

                http::Request request{"http://entropyconquers.pythonanywhere.com/userinfo?token="+getAuthToken()};
                
                const auto response = request.send("POST");
                
                string res = std::string{response.body.begin(), response.body.end()};
                //cout<<res<<endl;
                //parse into json
                json j = json::parse(res);
                //assign user info to the user object
                name = j["name"];
                address = j["address"];
                phone_number = j["phone_number"];
                account_number = j["account_number"];
                return true;
                }
            }
            catch(exception e){
                return false;
            }
            return false;
            
        }
        bool getBalance(){
            try{
                if(getAuthToken()!="0"){
                //fetch and assign user info from server
                //fetch user info from server
                //assign user info to the user object

                http::Request request{"http://entropyconquers.pythonanywhere.com/balance?token="+getAuthToken()};
                
                const auto response = request.send("POST");
                
                string res = std::string{response.body.begin(), response.body.end()};
                //cout<<res<<endl;
                //parse into json
                json j = json::parse(res);
                //assign user info to the user object
                balance = j["balance"];
                cout<<"Your balance is: "<<balance<<endl;
                return true;
                }
            }
            catch(exception e){
                return false;
            }
            return false;
            
        }
        bool deposit(double amount){
            if(amount<=0){
                //red console output
                cout << "\033[1;31m";
                cout<<"Invalid amount."<<endl;
                cout << "\033[0m";
                return false;
            }
            if(amount>100000){
                //red console output
                cout << "\033[1;31m";
                cout<<"Invalid amount. Maximum amount is 1,00,000."<<endl;
                cout << "\033[0m";
                return false;
            }
            //fetch balance from the server
            bool a = getBalance();
            if(!a) return false;
            //add the amount to the balance
            balance += amount;
            //update the balance on the server
            return updateBalance();
        }
        //withdraw money from the account
        bool withdraw(double amount){
            if(amount<=0){
                //red console output
                cout << "\033[1;31m";
                cout<<"Invalid amount."<<endl;
                cout << "\033[0m";
                return false;
            }
            bool a = getBalance();
            if(amount>balance){
                //red console output
                cout << "\033[1;31m";
                cout<<"Invalid amount. Insufficient balance."<<endl;
                cout << "\033[0m";
                return false;
            }
            if(!a) return false;
            //remove the amount to the balance
            balance -= amount;
            //update the balance on the server
            return updateBalance();
        }
        bool get_transactions(){
            try{
                if(getAuthToken()!="0"){
                //fetch and assign user info from server
                //fetch user info from server
                //assign user info to the user object

                http::Request request{"http://entropyconquers.pythonanywhere.com/transactions?token="+getAuthToken()};
                
                const auto response = request.send("POST");
                
                string res = std::string{response.body.begin(), response.body.end()};
                //cout<<res<<endl;
                //parse into json
                json j = json::parse(res);
                //assign user info to the user object
                json transaction_array = json::array();
                transaction_array = j;
                transaction_history.clear();
                for(int i=0;i<transaction_array.size();i++){
                    transaction_history.push_back(transaction(transaction_array[i]["id"],transaction_array[i]["amount"],transaction_array[i]["type"],transaction_array[i]["time"]));
                }
                return true;
                }
            }
            catch(exception e){
                return false;
            }
            return false;
            
        }
        void print_transactions(){
            //print in table format
            cout<<"\033[1;31m";
            cout<<"Transaction History"<<endl;
            cout<<"\033[0m";
            TextTable t( '-', '|', '+' );
            t.add("Transaction ID");
            t.add("Amount");
            t.add("Type");
            t.add("Time");
            t.endOfRow();
            for(int i=0;i<transaction_history.size();i++){
                t.add(transaction_history[i].get_transaction_id());
                t.add(to_string(transaction_history[i].get_transaction_amount()));
                t.add(transaction_history[i].get_transaction_type());
                t.add(transaction_history[i].get_transaction_datetime());
                t.endOfRow();
            }
            cout << t;


        }

        bool updateBalance(){
            //update the balance on the server
            try{
                if(getAuthToken()!="0"){
                string req = "http://entropyconquers.pythonanywhere.com/updatebalance?token="+getAuthToken()+"&balance="+to_string(balance);
                //cout<<req<<endl;
                http::Request request{req};
                
                const auto response = request.send("POST");
                
                string res = std::string{response.body.begin(), response.body.end()};
                //cout<<res<<endl;
                //parse into json
                json j = json::parse(res);
                //assign user info to the user object
                balance = j["balance"];
                
                return true;
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Request failed, error: " << e.what() << '\n';
            }
            return false;
        }
        //print the account information
        void print_account_info(){
            cout << "Name: " << name << endl;
            cout << "Address: " << address << endl;
            cout << "Phone number: " << phone_number << endl;
            cout << "Account number: " << account_number << endl;
            cout << "Balance: " << balance << endl;
        }
        //print the transaction history
        void print_transaction_history(){
            for(int i = 0; i < transaction_history.size(); i++){
                transaction_history[i].print_transaction();

            }
        }
        //add a transaction to the transaction history
        void add_transaction(transaction new_transaction){
            transaction_history.push_back(new_transaction);
        }
        void print_user_details(){
            TextTable tUser( '-', '|', '+' );
            tUser.add( "Name");
            tUser.add( "Address");
            tUser.add( "Phone Number");
            tUser.add( "Account Number");
            tUser.endOfRow();
            tUser.add( get_name());
            tUser.add( get_address());
            tUser.add( get_phone_number());
            tUser.add( get_account_number());
            tUser.endOfRow();
            tUser.setAlignment( 2, TextTable::Alignment::RIGHT );
            std::cout << tUser;
            cout << "\033[1;33m";
        }
        

};
