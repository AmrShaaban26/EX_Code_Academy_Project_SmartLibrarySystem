#pragma once

#include <vector>
#include "Book.hpp"
#include "User.hpp"

class Library
{
    private:
        //vector for the books
        std::vector<Book*> books;
        //pointer vector for Librarians and Members together
        std::vector<User*> users;
        // Internal lookup used to safely find pointers inside book vector
        Book* findBookByID(int book_id);

    public:
        //no constructor, using the default constructor
        //Destructor to clean up dynamically allocated User pointers
        ~Library();
        
        // System Actions
        User* findUserByID(int user_id);// Internal lookup used to safely find pointers inside user vector
        void addBook(Book* b);//to add books to the system
        void addUsertoSystem(User* u);//to add users(Librarians and Members) to the system
        void removeBook(int book_id); //to remove books from the library
        void processBorrow(int member_id, int book_id); // to borrow a book
        void processReturn(int member_id, int book_id); // to return a book
        void searchBook(std::string title); // to search for a book
        // Prints a list of all registered library members
        void printMemberList();
        // Prints all books currently sitting on shelves ready to be borrowed
        void printAvailableBooks();
        // Prints a complete list of every single book registered in the database inventory
        void printAllBooks();
        // Displays full title and author details for every book a specific member has checked out
        void viewMemberBorrowedBooks(int member_id);
        // Prints a list of all registered administrative librarians
        void printLibrarianList();
        //to remove user
        void removeUser(int user_id);
        // Searches for and displays all books written by a specific author
        void searchBookByAuthor(std::string author);
    };