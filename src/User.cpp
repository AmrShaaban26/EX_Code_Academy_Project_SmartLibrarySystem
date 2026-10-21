#include "User.hpp"
#include <iostream>
#include <string>

//constructor implementation
User::User(int id, std::string name_1) : ID(id), name(name_1) {}
//destructor implementation
User::~User()
{
    std::cout << "Cleaning up RAM from User objects so you wouldn't have a memory leak. Please wait ... \n";
}
//get methods
void User::showID()
{
    std::cout << "The User ID is " << ID << ".\n";
}
void User::show_name()
{
    std::cout << "The User name is " << name << ".\n";
}
int User::showID1()
{
    return ID;
}
std::string User::show_name1()
{
    return name;
}