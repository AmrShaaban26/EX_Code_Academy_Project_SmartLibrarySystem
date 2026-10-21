#include "Book.hpp"
#include <iostream>
#include <string>

// Global initialization of the shared system counter
int Book::total_borrowed_books_count = 0; 
//constructor
Book::Book(int id, std::string title_1, std::string author_1, bool status) : ID(id), title(title_1), author(author_1), availability_status(status) {}
// destructor
Book::~Book()
{
    std::cout << "Cleaning up RAM from Book objects so you wouldn't have a memory leak. Please wait ... \n";
}
//get methods implementation using dot operator
void Book::showID()
{
    std::cout<< "The Book's ID is " << ID <<".\n";
}
void Book::show_title()
{
    std::cout << "The Book's title is " <<  title << ".\n";
}
void Book::show_author()
{
    std::cout << "The Book's author is " << author << ".\n";
}
void Book::show_availability_status()
{
    std::cout << "The Book is " << (availability_status ? "available" : "unavailable");
    std::cout << " to be borrowed.\n";
}
//get methods implementation for variables in main()
int Book::showID1()
{
    return ID;
}
std::string Book::show_title1()
{
    return title;
}
std::string Book::show_author1()
{
    return author;
}
bool Book::show_availability_status1()
{
    return availability_status;
}
//set method implementation
void Book::set_availability_status(bool status)
{
    availability_status = status;
}
void Book::showTotalBorrowedCount()
{
    // Because it is a static member function, it can directly read the static variable
    std::cout << "Total library assets out on loan = " << total_borrowed_books_count << " books.\n";
}