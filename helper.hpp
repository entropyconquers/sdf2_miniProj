#include<iostream>
using namespace std;
//clear the console
void clearConsole(){
    cout << "\033[2J\033[1;1H";
}
int selection(int range){
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    while(choice<1 || choice>range){
        
        //red
        cout << "\033[1;31m";
        cout << "Invalid choice. Enter your choice: ";
        cin >> choice;
        //reset
        cout << "\033[0m";
    }
    //clear buffer
    cin.clear();
    cin.sync();
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    return choice;
}