#pragma once
#include "User.hpp"
#include "Book.hpp"

//declaration of Library class to avoid the circular include dependencies issue
class Library; 

class Librarian : public User
{
    public:
        // Constructor passes the unique ID and name up to the base User constructor
        Librarian(int id, std::string n);

        // Virtual destructor ensuring safe inheritance cleanup
        virtual ~Librarian() override;

        //add new books to the system
        void addBookToSystem(Library& lib, int book_id, std::string title, std::string author);
        //remove books from the system
        void removeBookFromSystem(Library& lib, int book_id);
        //add new members to the system
        void addNewMemberToSystem(Library& lib, int member_id, std::string name);
        //remove member from the system
        void removeMemberFromSystem(Library& lib, int member_id);
        //remove a librarian that quit his job from the system
        void removeLibrarianFromSystem(Library& lib, int librarian_id);
};