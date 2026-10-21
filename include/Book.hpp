#pragma once

#include <string>

class Book
{
    // class properties private Encapsulation
    int ID;
    std::string title;
    std::string author;
    bool availability_status = false;// true = available, false = unavailable

    // methods
    public:
        // Static variable shared by ALL book objects globally
        static int total_borrowed_books_count;
        //constructor
        Book(int id, std::string title_1, std::string author_1, bool status);
        //destructor
        ~Book();
        //get methods
            //to show the ID
        void showID();
            //to show the title of the book
        void show_title();
            //to show author of the book
        void show_author();
            //to show the availability of the book
        void show_availability_status();
        // get methods for variable in main()
            //to return ID
        int showID1();
            //to return title
        std::string show_title1();
            //to return author
        std::string show_author1();
            //to return availability status
        bool show_availability_status1();
            //static function to show the static variable total_borrowed_books_count
        static void showTotalBorrowedCount();
        //set methods
            //to set or change the availability status
        void set_availability_status(bool status);
};