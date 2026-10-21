#include <iostream>
#include "Member.hpp"
#include <vector>
#include <string>

//consrructor
Member::Member(int id, std::string name_1) : User(id, name_1) {}
//destructor
Member::~Member()
{
    std::cout << "Cleaning up RAM from Member objects so you wouldn't have a memory leak. Please wait ... \n";
}
void Member::addBorrowedBooksIDstoTheVector(int book_ID)
{
    borrowedIDSofBooks.push_back(book_ID);
}
void Member::printIDSofBorrowedBooks()
{
    for(auto it = borrowedIDSofBooks.begin(); it != borrowedIDSofBooks.end(); it++)
    {
    std::cout << *it << "\n";
    }
}
bool Member::isHoldingBook(int book_ID)
{
    for (int id : borrowedIDSofBooks)
    {
        if (id == book_ID)
        {
            return true; // Member is already holding this book
        }
    }
    return false; // not found
}

void Member::removeBorrowedBooksIDsFromTheVector(int book_ID)
{
    for (auto it = borrowedIDSofBooks.begin(); it != borrowedIDSofBooks.end(); ++it)
    {
        if (*it == book_ID)
        {
            borrowedIDSofBooks.erase(it); // Erase from member history ledger
            return; 
        }
    }
}

int Member::getBorrowedBooksCount()
{
    return borrowedIDSofBooks.size(); // Returns how many elements are in the list
}