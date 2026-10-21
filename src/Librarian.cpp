#include "Librarian.hpp"
#include "Library.hpp"  // for Library's methods
#include "Member.hpp"   // for new Member object
#include <iostream>

//Constructor
Librarian::Librarian(int id, std::string n) : User(id, n) {}
//destructor
Librarian::~Librarian()
{
    std::cout << "Cleaning up RAM from Librarian objects so you wouldn't have a memory leak. Please wait ... \n";
}
//add a new book to the library system
void Librarian::addBookToSystem(Library& lib, int book_id, std::string title, std::string author) 
{
    // create a Book object
    Book* newBook = new Book(book_id, title, author, true);
    
    // Pass it to the active Library instance database
    lib.addBook(newBook);
    
    std::cout << "Librarian '" << show_name1() << "' successfully added book to system inventory.\n";
}

//add a new member to the library system database
void Librarian::addNewMemberToSystem(Library& lib, int member_id, std::string name) 
{
    // Dynamically allocate a new Member on the Heap memory loop
    User* newMember = new Member(member_id, name);
    
    // Pass the pointer directly to the library database tracking vector
    lib.addUsertoSystem(newMember);
    
    std::cout << "Librarian '" << show_name1() << "' registered new new member " << name << ".\n";
}
void Librarian::removeBookFromSystem(Library& lib, int book_id)
{
    std::cout << "Librarian '" << show_name1() << "' initiated deletion request for Book ID: " << book_id << ".\n";
    //deleting using library
    lib.removeBook(book_id);
}
void Librarian::removeMemberFromSystem(Library& lib, int member_id)
{
    std::cout << "Librarian '" << show_name1() << "' requested removal of Member ID: " << member_id << "\n";
    lib.removeUser(member_id);
}

void Librarian::removeLibrarianFromSystem(Library& lib, int librarian_id)
{
    std::cout << "Librarian '" << show_name1() << "' requested removal of Librarian ID: " << librarian_id << " who tendered his resignation.\n";
    lib.removeUser(librarian_id);
}