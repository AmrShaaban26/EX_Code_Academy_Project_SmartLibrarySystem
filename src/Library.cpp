#include "Library.hpp"
#include "User.hpp"
#include <iostream>
#include <Member.hpp>
#include <algorithm>
#include "Librarian.hpp"

//destructor implementation
Library::~Library()
{
    std::cout << "Cleaning up RAM from User and Book pointers so you wouldn't have any rouge memory pointer. Please wait ... \n";
    // Clean up dynamic user allocations
    for (size_t i = 0; i < users.size(); ++i)
    {
        delete users[i];
    }
    //Clean up dynamic book allocations
    for (size_t i = 0; i < books.size(); ++i)
    {
        delete books[i];
    }
}

void Library::addBook(Book* b)
{
    // to Make sure no addition of a null pointer
    if (b == nullptr)
    {
        std::cout << "no adding a null book pointer to the system.\n";
        return;
    }

    // unique id guard check
    // Scan the inventory catalog to prevent duplicate book IDs
    if (findBookByID(b->showID1()) != nullptr)
    {
        std::cout << "Book ID " << b->showID1() << " already exists! Addition rejected for \"";
        b->show_title();
        std::cout << "\".\n";
        delete b; // Clean up memory immediately
        return;
    }

    //adding the book to the books vector
    books.push_back(b);
    //saying that the book is added
    std::cout << "Success. \"";
    b->show_title();
    std::cout << "\" is added to the Library.\n";
}
void Library::addUsertoSystem(User* u) 
{
    // to Make sure we aren't adding a null pointer
    if (u == nullptr) {
        std::cout << "no addition of null user pointer to the system.\n";
        return;
    }

    // unique id guard check
    // Scan the existing list to ensure this user ID isn't already taken
    if (findUserByID(u->showID1()) != nullptr)
    {
        std::cout << "User ID " << u->showID1() << " is already taken! Registration rejected for '" << u->show_name1() << "'.\n";
        delete u; // Clean up memory immediately
        return;
    }

    //adding the user pointer to the users vector
    users.push_back(u);
    
    //confirmation message
    std::cout << "User '"<< u->show_name1() << "' (ID: " << u->showID1() << ") added to the library.\n";
}
void Library::removeBook(int book_id)
{
    // Search the vector loop for the matching Book pointer ID
    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if ((*it) != nullptr && (*it)->showID1() == book_id)
        {
            std::cout << "Success: \"";
            (*it)->show_title(); // Prints the title of the book being deleted
            std::cout << "\" has been identified for system removal.\n";

            //clean up memory allocation to prevent memory leaks
            delete *it; 

            // erase pointer slot from vector array database
            books.erase(it); 
            return; // Exit after successful deletion
        }
    }
    std::cout << "book with ID " << book_id << " was not found in the library database.\n";
}

//internal helper to scan the library's entire inventory array to locate the memory address of a specific book using its ID number
Book* Library::findBookByID(int book_id)
{
    for (Book* b : books)
    {
        if (b != nullptr && b->showID1() == book_id) {
            return b;
        }
    }
    return nullptr;
}
//internal helper to scan the library's entire user registry to locate the exact memory address of a specific person using their ID card number
User* Library::findUserByID(int user_id)
{
    for (User* u : users)
    {
        if (u != nullptr && u->showID1() == user_id) {
            return u;
        }
    }
    return nullptr;
}
//the borrow process
void Library::processBorrow(int member_id, int book_id)
{
    //local pointer variables by capturing the memory addresses returned from internal helper lookup functions
    User* baseUser = findUserByID(member_id);
    Book* book = findBookByID(book_id);

    //check if the Member exists
    if (baseUser == nullptr)
    {
        std::cout << "Member Card ID " << member_id << " does not exist in the database.\n";
        return;
    }

    //check if the Book exists before proceeding to secondary rules
    if (book == nullptr)
    {
        std::cout << "Book ID " << book_id << " does not exist in the library inventory.\n";
        return;
    }
    //check to verify that a the user is a member not librarian
    Member* member = dynamic_cast<Member*>(baseUser);
    if (member == nullptr)
    {
        std::cout << "This User ID does not belong to a Member account.\n";
        return;
    }

    //Check if the targeted book is available
    if (!book->show_availability_status1())
    {
        std::cout << "This book is already checked out by someone else.\n";
        return;
    }

    // calling  member vector scanner to block duplicate history checkouts
    if (member->isHoldingBook(book_id))
    {
        std::cout << "The Member whose name is '" << member->show_name1() << "' is already holding Book ID " << book_id << " and cannot borrow it again!\n";
        return;
    }
    // Define the threshold constraint limit
    const int MAX_BORROW_LIMIT = 3; // generic limit
    if (member->getBorrowedBooksCount() >= MAX_BORROW_LIMIT)
    {
        std::cout << "The Member whose name is '" << member->show_name1() << "' has reached the maximum borrowing limit of " << MAX_BORROW_LIMIT << " books!\n";
        std::cout << "Please return a book before attempting to borrow another one.\n";
        return; // Halts the transaction loop immediately before checking out
    }

    // safe to check out book now
    book->set_availability_status(false);
    member->addBorrowedBooksIDstoTheVector(book_id); // Log into user ledger history
    // increment the static counter
    Book::total_borrowed_books_count++; 
    std::cout << "Total library assets out on loan: " << Book::total_borrowed_books_count << "\n";
    std::cout << "The Member whose name is '" << member->show_name1() << "' has borrowed Book ID " << book_id << ".\n";
}

void Library::processReturn(int member_id, int book_id)
{
    //local pointer variables by capturing the memory addresses returned from internal helper lookup functions
    User* baseUser = findUserByID(member_id);
    Book* book = findBookByID(book_id);

    //to verify whether either the member or the book are there inside the library system
    if (baseUser == nullptr || book == nullptr)
    {
        std::cout << "Either the User or the Book are not in the Library's database.\n";
        return;
    }
    //check to verify that a the user is a member not librarian
    Member* member = dynamic_cast<Member*>(baseUser);
    if (member == nullptr)
    {
        std::cout << "This User ID does not belong to a Member account.\n";
        return;
    }

    // verify the member actually possesses this item before updating logs
    if (!member->isHoldingBook(book_id))
    {
        std::cout << "System records show " << member->show_name1() << " does not hold Book ID: " << book_id << ".\n";
        return;
    }

    book->set_availability_status(true); // Return item back to inventory
    member->removeBorrowedBooksIDsFromTheVector(book_id); // Drop ledger tracking reference
    // decrement the static counter
    Book::total_borrowed_books_count--;
    std::cout << "Total library assets out on loan: " << Book::total_borrowed_books_count << "\n";
    std::cout << "The Book whose title is \"";
    book->show_title();
    std::cout << "\" returned by " << member->show_name1() << " is verified and available again.\n";
}

void Library::searchBook(std::string title)
{
    //function to search for a book using title
    std::cout << "--- Search Results for: \"" << title << "\" ---\n";
    bool foundAny = false;
    //scan the books and print the details of every book that matches the targeted search title
    for (Book* b : books)
    {
        if (b != nullptr && b->show_title1() == title)
        {
            b->showID();
            b->show_title();
            b->show_author();
            b->show_availability_status();
            foundAny = true;
        }
    }
    if (!foundAny) {
        std::cout << "No book matching that title is found in the system registry.\n";
    }
}

void Library::printMemberList()
{
    std::cout << "REGISTERED LIBRARY MEMBERS\n";
    
    bool foundMembers = false;

    // Loop through users pointer vector
    for (User* u : users)
    {
        if (u != nullptr)
        {
            // Safely verify if the User* pointer points specifically to a Member child object
            Member* member = dynamic_cast<Member*>(u);
            if (member != nullptr)
            {
                // printing member data to the screen
                std::cout << "Member Name: " << member->show_name1() << " | Card ID: " << member->showID1() << "\n";
                
                // printing books they are holding
                std::cout << "  Borrowed Book IDs: ";
                member->printIDSofBorrowedBooks();
                
                foundMembers = true;
            }
        }
    }

    if (!foundMembers)
    {
        std::cout << "No active library member accounts found in the database directory.\n";
    }
    std::cout << "========================================\n";
}

void Library::printAvailableBooks()
{
    std::cout << "\n========================================\n";
    std::cout << "       BOOKS AVAILABLE TO BORROW        \n";
    std::cout << "========================================\n";
    
    bool foundAny = false;

    // Loop through your internal books tracking pointer vector
    for (Book* b : books)
    {
        //check against nullpointers , and check if status is true (available)
        if (b != nullptr && b->show_availability_status1() == true)
        {
            // Call the book built-in print tools to display its info card
            std::cout << "Book ID: " << b->showID1() << "\n";
            std::cout << "Title: "; b->show_title();
            std::cout << "Author: "; b->show_author();
            std::cout << "----------------------------------------\n";
            
            foundAny = true;
        }
    }

    if (!foundAny)
    {
        std::cout << "Sorry, all books are currently checked out or the inventory is empty.\n";
    }
    std::cout << "========================================\n";
}

void Library::printAllBooks()
{
    std::cout << "\n========================================\n";
    std::cout << "         COMPLETE LIBRARY CATALOG       \n";
    std::cout << "========================================\n";
    
    if (books.empty())
    {
        std::cout << "The library inventory database registry is currently empty.\n";
        std::cout << "========================================\n";
        return;
    }

    //for loop to go through the book tracking pointer array
    for (Book* b : books)
    {
        if (b != nullptr)
        {
            // print all properties of the current book 
            std::cout << "Book ID: " << b->showID1() << "\n";
            std::cout << "Title:   "; b->show_title();
            std::cout << "Author:  "; b->show_author();
            std::cout << "Status:  "; b->show_availability_status();
            std::cout << "----------------------------------------\n";
        }
    }
    std::cout << "========================================\n";
}

void Library::viewMemberBorrowedBooks(int member_id)
{
    //local pointer variables by capturing the memory addresses returned from internal helper lookup functions
    User* baseUser = findUserByID(member_id);
    if (baseUser == nullptr)
    {
        std::cout << "Member ID " << member_id << " not found.\n";
        return;
    }
    //to transofrm the baseUser to a Member class rather than keeping it in the User class
    Member* member = dynamic_cast<Member*>(baseUser);
    if (member == nullptr)
    {
        std::cout << "User ID " << member_id << " is not a valid Member account.\n";
        return;
    }

    std::cout << "\n========================================\n";
    std::cout << "  BOOKS BORROWED BY: " << member->show_name1() << "\n";
    std::cout << "========================================\n";

    bool holdingAny = false;
    
    //looping through the master books vector
    for (Book* b : books)
    {
        if (b != nullptr)
        {
            // If the member's internal checker confirms they are holding this book ID
            if (member->isHoldingBook(b->showID1()))
            {
                std::cout << "Book ID: " << b->showID1() << "\n";
                std::cout << "Title:   "; b->show_title();
                std::cout << "Author:  "; b->show_author();
                std::cout << "----------------------------------------\n";
                holdingAny = true;
            }
        }
    }

    if (!holdingAny)
    {
        std::cout << "This member has not borrowed any books currently.\n";
    }
    std::cout << "========================================\n";
}
void Library::printLibrarianList()
{
    std::cout << "\n========================================\n";
    std::cout << "      REGISTERED SYSTEM LIBRARIANS      \n";
    std::cout << "========================================\n";
    
    bool foundLibrarians = false;

    // Looping through the users pointer vector
    for (User* u : users)
    {
        if (u != nullptr)
        {
            // Safely verify if the User* pointer points specifically to a Librarian child object
            Librarian* librarian = dynamic_cast<Librarian*>(u);
            if (librarian != nullptr)
            {
                // print librarian data to the screen
                std::cout << "Librarian Name: " << librarian->show_name1() << " | Staff ID: " << librarian->showID1() << "\n";
                std::cout << "----------------------------------------\n";
                
                foundLibrarians = true;
            }
        }
    }

    if (!foundLibrarians)
    {
        std::cout << "No active librarian accounts found in the system registry.\n";
    }
    std::cout << "========================================\n";
}
void Library::removeUser(int user_id)
{
    //searching for a specific person by their ID number and delete their data
    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if ((*it) != nullptr && (*it)->showID1() == user_id)
        {
            std::cout << "User '" << (*it)->show_name1() << "' has been identified for system removal.\n";
            
            // freeing memory to prevent memory leaks
            delete *it; 
            
            // removing the empty pointer tracking slot from the array
            users.erase(it);
            return;
        }
    }
    std::cout << "User ID " << user_id << " was not found in the database directory.\n";
}
void Library::searchBookByAuthor(std::string author)
{
    std::cout << "\n--- Search Results for Author: \"" << author << "\" ---\n";
    bool foundAny = false;
    
    //going through the books vector tracking array
    for (Book* b : books)
    {
        //check against nullpointers, and compare the author strings
        if (b != nullptr && b->show_author1() == author)
        {
            b->showID();
            b->show_title();
            b->show_author();
            b->show_availability_status();
            std::cout << "--------------------------------\n";
            foundAny = true;
        }
    }
    
    if (!foundAny) {
        std::cout << "No books by author \"" << author << "\" were found in the system registry.\n";
    }
}