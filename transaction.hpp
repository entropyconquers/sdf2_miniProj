#include<iostream>
#include"Date.cpp"
#include"time.cpp"
using namespace std;

//create a transaction class with the following attributes:
//transaction type (deposit or withdraw) (0 is credit 1 is debit)
//amount
//date
//time
class transaction{
    private:
        string transaction_type;
        double transaction_amount;
        date transaction_date;
        Time transaction_time;
        string transaction_id;
        string transaction_date_time;
    public:
        //constructor
        transaction(string transaction_type, double transaction_amount, date transaction_date, Time transaction_time){
            this->transaction_type = transaction_type;
            this->transaction_amount = transaction_amount;
            this->transaction_date = transaction_date;
            this->transaction_time = transaction_time;
        }
        transaction(int transaction_id, double transaction_amount, int transaction_type, string transaction_date_time){
            this->transaction_id = to_string(transaction_id);
            this->transaction_type = transaction_type?"WITHDRAWL":"DEPOSIT";
            this->transaction_amount = transaction_amount;
            this->transaction_date_time = transaction_date_time;
        }
        //getters
        string get_transaction_type(){
            return transaction_type;
        }
        double get_transaction_amount(){
            return transaction_amount;
        }
        date get_transaction_date(){
            return transaction_date;
        }
        string get_transaction_datetime(){
            return transaction_date_time;
        }
        string get_transaction_id(){
            return transaction_id;
        }
        Time get_transaction_time(){
            return transaction_time;
        }
        //setters
        void set_transaction_type(string transaction_type){
            this->transaction_type = transaction_type;
        }
        void set_transaction_amount(double transaction_amount){
            this->transaction_amount = transaction_amount;
        }
        void set_transaction_date(date transaction_date){
            this->transaction_date = transaction_date;
        }
        void set_transaction_time(Time transaction_time){
            this->transaction_time = transaction_time;
        }
        //print the transaction
        void print_transaction(){
            cout << "Transaction type: " << transaction_type << endl;
            cout << "Transaction amount: " << transaction_amount << endl;
            cout << "Transaction date: ";
            transaction_date.print_date();
            cout << endl;
            cout << "Transaction time: ";
            transaction_time.print_time();
            cout << endl;
        }
        
};
