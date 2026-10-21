#pragma once

#include <string>
#include "User.hpp"
#include <vector>

class Member : public User
{
    private:
    // a vector to track down the IDs of books borrowed by the member
        std::vector<int> borrowedIDSofBooks;
    public:
        //constructor
        Member(int id, std::string name_1);
        //destructor
        virtual ~Member() override;
        //to add books to the borrowedIDSofBooks
        void addBorrowedBooksIDstoTheVector(int book_ID);
        //to print IDs of borrowed books
        void printIDSofBorrowedBooks();
        // to check if the member is already holding this specific book ID
        bool isHoldingBook(int book_ID);
        // to erase a specific book ID from a member's borrowed books list
        void removeBorrowedBooksIDsFromTheVector(int book_ID);
        // Returns the number of books the member is currently holding
        int getBorrowedBooksCount();
};