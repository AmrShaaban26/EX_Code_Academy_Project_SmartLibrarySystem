#pragma once

#include <string>

class User //base class
{
    protected:
        int ID;
        std::string name;
    
    public:
    //constructor
    User(int id, std::string name_1);
    //destructor
    virtual ~User(); // using virtuall for child classes that will inherit from this class
    //get methods
        //show ID
    void showID();
        //show name
    void show_name();
        //to print name in main
    std::string show_name1();
        //to rpint ID in main
    int showID1();
};