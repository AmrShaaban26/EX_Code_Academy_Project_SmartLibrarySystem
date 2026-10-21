#include <iostream>
#include <string>
#include "Book.hpp"
#include "User.hpp"
#include "Member.hpp"
#include "Library.hpp"
#include "Librarian.hpp"

using namespace std;

int main()
{
    Library libraryHub;
    
    // Trigger static method
    Book::showTotalBorrowedCount();
    
    // Create an active librarian
    Librarian mainLibrarian(2001, "Amr Basyouni");
    
    // Add the librarian object address to the system directory
    libraryHub.addUsertoSystem(&mainLibrarian);

    mainLibrarian.addNewMemberToSystem(libraryHub, 3001, "Ahmed Hafez"); // Valid member
    mainLibrarian.addNewMemberToSystem(libraryHub, 3002, "Saif Ahmed");   // Valid member

    // Attempting to register an duplicate user ID to test the guard logic
    User* duplicateUser = new Member(3001, "Fraudulent Account");
    libraryHub.addUsertoSystem(duplicateUser);

    mainLibrarian.addBookToSystem(libraryHub, 101, "C++ Programming", "Bjarne Stroustrup"); // Book A
    mainLibrarian.addBookToSystem(libraryHub, 102, "Introduction to Physics", "Isaac Newton"); // Book B
    mainLibrarian.addBookToSystem(libraryHub, 103, "Design Patterns", "Gang of Four");       // Book C
    mainLibrarian.addBookToSystem(libraryHub, 104, "Advanced Calculus", "Isaac Newton");    // Book D

    // Attempting to add an identical book ID to verify internal error pathways
    Book* duplicateBook = new Book(101, "Fake Duplicate Book Title", "Ghost Writer", true);
    libraryHub.addBook(duplicateBook);

    // Display all book inventory entries
    libraryHub.printAllBooks();
    
    // Display all active librarians registered
    libraryHub.printLibrarianList();
    
    // Display all member registered
    libraryHub.printMemberList();
    //searching for a book by title
    libraryHub.searchBook("C++ Programming");

    //failed search attempt
    libraryHub.searchBook("Unknown Science Fiction Novel");

    //search for books by author
    libraryHub.searchBookByAuthor("Isaac Newton");

    //failed search books by author
    libraryHub.searchBookByAuthor("William Shakespeare");
    //borrow process trigger
    libraryHub.processBorrow(3001, 101); // Ahmed (3001) borrows C++ (101)

    // Saif tries to rent book id 101 (Should fail, already out on loan)
    libraryHub.processBorrow(3002, 101); 

    libraryHub.processBorrow(99999, 102); // Missing member check
    libraryHub.processBorrow(3001, 88888); // Missing book check

    libraryHub.processBorrow(2001, 102); // Librarian tries to borrow a book (Should reject account type)

    libraryHub.processBorrow(3001, 101); // Ahmed tries to borrow C++ again (Should fail)

    libraryHub.processBorrow(3001, 102); // Ahmed checks out 2nd book (Physics - 102)
    libraryHub.processBorrow(3001, 103); // Ahmed checks out 3rd book (Patterns - 103)
    libraryHub.processBorrow(3001, 104); // Ahmed tries to checkout 4th book (Calculus - 104) should be blocked

    Book::showTotalBorrowedCount();
    
    // list of books Ahmed borrowed
    libraryHub.viewMemberBorrowedBooks(3001); 

    // list of books available to borrow
    libraryHub.printAvailableBooks(); 

    libraryHub.processReturn(3002, 101); // Saif tries to return C++ which he never borrowed //an error

    libraryHub.processReturn(3001, 101); // Ahmed returns C++ (Should succeed seamlessly)

    libraryHub.printAvailableBooks(); // C++ (101) must be on shelves automatically
    Book::showTotalBorrowedCount(); // Shared counter must automatically increment to 2
    
    // Librarian deletes a book
    mainLibrarian.removeBookFromSystem(libraryHub, 103); 
    
    // Librarian removes a member account
    mainLibrarian.removeMemberFromSystem(libraryHub, 3002); 

    libraryHub.printAllBooks();   // Book 103 must be missing entirely from the master catalog listings
    libraryHub.printMemberList(); // Member Saif (3002) must be missing completely from lists

    return 0;
}