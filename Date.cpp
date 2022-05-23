#include<iostream>
using namespace std;
//create a date class
class date{
    private:
        int day;
        int month;
        int year;
        //day_lookup is a lookup table for the days in each month
        int day_lookup[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        //month_lookup is the name of each month
        string month_lookup[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    public:
        date(){
            
        }
        //constructor
        date(int day, int month, int year){
            this->day = day;
            this->month = month;
            this->year = year;
        }
        //getters
        int get_day(){
            return day;
        }
        int get_month(){
            return month;
        }
        int get_year(){
            return year;
        }
        //setters
        void set_day(int day){
            this->day = day;
        }
        void set_month(int month){
            this->month = month;
        }
        void set_year(int year){
            this->year = year;
        }
        //print the date
        void print_date(){
            cout << day << " " << month_lookup[month - 1] << " " << year;
        }
        //check if the date is valid
        bool is_valid_date(){
            if(month > 12 || month < 1){
                return false;
            }
            if(day > day_lookup[month - 1] || day < 1){
                return false;
            }
            if(year < 0){
                return false;
            }
            return true;
        }
        //check if the date is the same as another date
        bool is_same_date(date other_date){
            if(day == other_date.get_day() && month == other_date.get_month() && year == other_date.get_year()){
                return true;
            }
            return false;
        }
        //check if the date is after another date
        bool is_after_date(date other_date){
            if(year > other_date.get_year()){
                return true;
            }
            else if(year == other_date.get_year()){
                if(month > other_date.get_month()){
                    return true;
                }
                else if(month == other_date.get_month()){
                    if(day > other_date.get_day()){
                        return true;
                    }
                }
            }
            return false;
        }
        //get difference between two dates (in days)
        int get_difference(date other_date){
            int days_difference = 0;
            int year_difference = other_date.get_year() - year;
            int month_difference = other_date.get_month() - month;
            int day_difference = other_date.get_day() - day;
            if(year_difference > 0){
                days_difference += 365 * year_difference;
            }
            if(month_difference > 0){
                days_difference += 30 * month_difference;
            }
            if(day_difference > 0){
                days_difference += day_difference;
            }
            return days_difference;
        }
        //get the day of the week
        string get_day_of_the_week(){
            int day_of_the_week = (day + get_difference(date(1, 1, year))) % 7;
            string day_of_the_week_lookup[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
            return day_of_the_week_lookup[day_of_the_week];
        }
        //get the day of the week (in numeric format)
        int get_day_of_the_week_numeric(){
            int day_of_the_week = (day + get_difference(date(1, 1, year))) % 7;
            return day_of_the_week;
        }

};
