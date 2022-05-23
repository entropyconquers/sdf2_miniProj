#include<iostream>
#include<vector>
#include"bank_user.hpp"
#include"TextTable.h"

using namespace std;

int main(){
    
    
    clearConsole();
    //yellow
    loginFlow:
    bank_user user;
    TextTable t( '-', '|', '+' );
    t.setup();
    cout << "\033[1;33m";
    t.add("Welcome to JIIT Bank");
    t.endOfRow();
    //select option
    
    t.add("Select an option\n1. Login\n2. Create an account\n3. Exit");
    t.endOfRow();
    t.setAlignment( 2, TextTable::Alignment::RIGHT);
    std::cout << t;
    //change console color back to default
    cout << "\033[0m";
    int option = selection(3);
    
    bool loggedIn = false;
    switch(option){
        case 1:
            loggedIn = user.login();
            break;
        case 2:
            clearConsole();
            user.createUser();
            goto loginFlow;
            break;
        case 3:
            return 0;
            break;
    }
    if(loggedIn){
        clearConsole();
        if(!user.getUserInfo()){
            loggedIn = false;
            goto loginFlow;
        };

        //green
        cout << "\033[1;32m";
        cout<<"Logged in!"<<endl;
        //yellow
        user.print_user_details();
        
        //print user details to the console
        
        loggedInFlow:
        cout << "\033[1;33m";
        TextTable t1( '-', '|', '+' );
        t1.add("Select an option\n1. Deposit\n2. Withdraw\n3. Balance\n4. Previous Transactions\n5. Logout");
        t1.endOfRow();
        t1.setAlignment( 2, TextTable::Alignment::RIGHT);
        std::cout << t1;
        //change console color back to default
        cout << "\033[0m";
        int option = selection(5);
        int amount;
        switch(option){
            case 1:
                clearConsole();
                //get amount
                cout << "\033[1;33m";
                cout<<"Enter amount to deposit: ";
                cout << "\033[0m";
                amount = 0;
                cin >> amount;
                
                
                //deposit
                if(user.deposit(amount)){
                    cout<<"Deposited successfully"<<endl;
                    cout << "\033[1;32m";
                    cout<<"New Balance: "<<user.getBalance()<<endl;
                    cout << "\033[0m";
                    goto loggedInFlow;
                }
                else{
                    //red
                    cout << "\033[1;31m";
                    cout<<"Deposit failed"<<endl;
                    cout << "\033[0m";
                    goto loggedInFlow;
                }


                //user.deposit();
                break;
            case 2:
                clearConsole();
                //get amount
                cout << "\033[1;33m";
                cout<<"Enter amount to withdraw: ";
                cout << "\033[0m";
                amount = 0;
                cin >> amount;
                
                
                //deposit
                if(user.withdraw(amount)){
                    cout<<"Withdrawl successful"<<endl;
                    cout << "\033[1;32m";
                    cout<<"New Balance: "<<user.getBalance()<<endl;
                    cout << "\033[0m";
                    goto loggedInFlow;
                }
                else{
                    //red
                    cout << "\033[1;31m";
                    cout<<"Withdrawl failed"<<endl;
                    cout << "\033[0m";
                    goto loggedInFlow;
                }
                //user.withdraw();
                break;
            case 3:
                //clearConsole();
                if(!user.getBalance()){
                    //red
                    cout << "\033[1;31m";
                    cout<<"Error fetching balance"<<endl;
                    goto loggedInFlow;
                }
                else{
                    //yellow
                    clearConsole();
                    user.print_user_details();
                    cout << "\033[1;33m";
                    cout<<"Balance: "<<user.get_balance()<<endl;
                    //change console color back to default
                    cout << "\033[0m";
                    goto loggedInFlow;
                }
                //user.balance();
                break;
            case 4:
                clearConsole();
                //user.print_transactions();
                user.get_transactions();
                user.print_transactions();
                goto loggedInFlow;
                break;
            case 5:
                clearConsole();
                if(user.tokenExists()){
                    //remove the file
                    remove("authToken.psk");
                }
                goto loginFlow;
                break;
           
        }
    }
    else{
        goto loginFlow;
    } 
    


    return 0;


}