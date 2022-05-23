#include<iostream>
using namespace std;
//create a time class
class Time{
    private:
        int hour;
        int minute;
        int second;
    public:
        //constructor
        Time(){}
        Time(int hour, int minute, int second){
            this->hour = hour;
            this->minute = minute;
            this->second = second;
        }
        //getters
        int get_hour(){
            return hour;
        }
        int get_minute(){
            return minute;
        }
        int get_second(){
            return second;
        }
        //setters
        void set_hour(int hour){
            this->hour = hour;
        }
        void set_minute(int minute){
            this->minute = minute;
        }
        void set_second(int second){
            this->second = second;
        }
        //print the time
        void print_time(){
            cout << hour << ":" << minute << ":" << second;
        }
        //check if the time is valid
        bool is_valid_time(){
            if(hour > 23 || hour < 0){
                return false;
            }
            if(minute > 59 || minute < 0){
                return false;
            }
            if(second > 59 || second < 0){
                return false;
            }
            return true;
        }
        //check if the time is the same as another time
        bool is_same_time(Time other_time){
            if(hour == other_time.get_hour() && minute == other_time.get_minute() && second == other_time.get_second()){
                return true;
            }
            return false;
        }
        //check if the time is after another time
        bool is_after_time(Time other_time){
            if(hour > other_time.get_hour()){
                return true;
            }
            else if(hour == other_time.get_hour()){
                if(minute > other_time.get_minute()){
                    return true;
                }
                else if(minute == other_time.get_minute()){
                    if(second > other_time.get_second()){
                        return true;
                    }
                }
            }
            return false;
        }
        // find the difference between two times (in seconds)
        int get_difference(Time other_time){
            int difference = 0;
            if(is_after_time(other_time)){
                difference = (hour - other_time.get_hour()) * 3600 + (minute - other_time.get_minute()) * 60 + (second - other_time.get_second());
            }
            else if(is_same_time(other_time)){
                difference = 0;
            }
            else{
                difference = -1;
            }
            return difference;
        }
        
        
};