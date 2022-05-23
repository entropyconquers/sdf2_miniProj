#include "HTTPRequest.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include "json.hpp"
#include <algorithm>
#include "TextTable.h"
#include "helper.hpp"
using namespace std; 
using json = nlohmann::json;
class user_auth{
    private: 
    string email;
    string password;
    string auth_token;
    public:
    //check if auth_token already exists
    bool tokenExists(){
        ifstream myfile("authToken.psk");
        return myfile.is_open();
    }
    //login
    bool login(){
        //clear the console
        clearConsole();
        //delete the auth token if it exists
        if(tokenExists()){
            //remove the file
            remove("authToken.psk");
        }

        
        //get the email and password from the user
        cout << "Enter your email: ";
        getline(cin,email);
        cout << "Enter your password: ";
        getline(cin,password);
        char body_buffer[5012];
        snprintf(body_buffer, sizeof(body_buffer), "{\"email\":\"%s\",\"password\":\"%s\"}", email.c_str(), password.c_str());
        //covert body buffer to string and assign to body
        int i = 0;
        string body(body_buffer);
        //create a HTTPRequest object
        http::Request request{"http://entropyconquers.pythonanywhere.com/login"};
        const auto response = request.send("POST", body, {
                {"auth-token", "G4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ"}
            });
        
        string res = std::string{response.body.begin(), response.body.end()};
        
        //send the request
        
        
        //get the auth token from the json object
        cout<<res<<endl;
        if(res.length()==32){
            auth_token = res;
            //write the auth token to a file
            ofstream myfile;
            myfile.open("authToken.psk");
            myfile << auth_token;
            myfile.close();
            return true;
        }
        else{
            clearConsole();
            //red
            cout << "\033[1;31m";
            cout << "Invalid email or password" << endl;
            cout << "\033[0m";
            auth_token = "0";
            //write the auth token to a file
            ofstream myfile;
            myfile.open("authToken.psk");
            myfile << auth_token;
            myfile.close();
            return false;
        }
        
        
    }
    //get auth_token from file
    string getAuthToken(){
        //check if file exists
        if(!tokenExists()) return "0";
        ifstream myfile("authToken.psk");
        string line;
        getline(myfile, line);
        auth_token = line;
        return auth_token;
    }
    bool createUser(){
        try
        {
            http::Request request{"http://entropyconquers.pythonanywhere.com/register"};
            string name, address, phone_number, email, password;
            TextTable t( '-', '|', '+' );
            cout << "Enter your name: ";
            //use getline
            getline(cin, name);
            cout << "Enter your address: ";
            getline(cin, address);
            cout << "Enter your phone number: ";
            getline(cin, phone_number);
            //check if phone number is valid
            while(phone_number.length() != 10){
                cout << "Invalid phone number. Please enter a valid phone number: ";
                getline(cin, phone_number);
            }

            cout << "Enter your email: ";
            getline(cin, email);
            //check if email is valid
            while(email.find("@") == string::npos){
                cout << "Invalid email. Please enter a valid email: ";
                getline(cin, email);
            }
            cout << "Enter your password: ";
            getline(cin, password);
            //check if password is valid
            //password must be at least 8 characters long
            //password must contain at least one uppercase letter
            //password must contain at least one lowercase letter
            //password must contain at least one digit
            //password must contain at least one special character
            while(password.length() < 8 && password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos && password.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos && password.find_first_of("0123456789") == string::npos && password.find_first_of("!@#$%^&*()") == string::npos){
                cout << "Invalid password. Please enter a valid password: ";
                getline(cin, password);
            }
            
            //print user details to the console
            

            //format string
            /*body = std::format("{\"name\":\"{}\",\"address\":\"{}\",\"phone_number\":\"{}\",\"email\":\"{}\",\"password\":\"{}\"}", name, address, phone_number, email, password);
            */
            //format string body using snprintf
            char body_buffer[5012];
            snprintf(body_buffer, sizeof(body_buffer), "{\"name\":\"%s\",\"address\":\"%s\",\"phone_number\":\"%s\",\"email\":\"%s\",\"password\":\"%s\"}", name.c_str(), address.c_str(), phone_number.c_str(), email.c_str(), password.c_str());
            //covert body buffer to string and assign to body
            int i = 0;
            string body(body_buffer);
            //cout<<body;

            const auto response = request.send("POST", body, {
                {"auth-token", "G4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ"}
            });
            
            string res = std::string{response.body.begin(), response.body.end()};
            if(res=="0"){
                //change console color to red
                cout << "\033[1;31m";
                cout<<"User already exists";
                //change console color back to default
                cout << "\033[0m";
                return false;
            }
            else{
                //change console color to green
                cout << "\033[1;32m";
                //clear the console
                clearConsole();
                cout<<"User created successfully"<<endl;
                //change console color back to default
                cout << "\033[0m";
                //yellow text
                cout << "\033[1;33m";
                t.add( "Name");
                t.add( "Address");
                t.add( "Phone Number");
                t.add( "Email");
                
                t.endOfRow();
                t.add( name);
                t.add( address);
                t.add( phone_number);
                t.add( email);
                t.endOfRow();

                t.setAlignment( 2, TextTable::Alignment::RIGHT );
                std::cout << t;
                //change console color back to default
                cout << "\033[0m";
                return true;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Request failed, error: " << e.what() << '\n';
        }
        return false;

    }
};

