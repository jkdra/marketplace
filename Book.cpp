#include "Book.h"
#include <iostream>

using namespace std;

// Constructor
Book::Book(const string& name,
           double price,
           const string& author,
           const string& isbn,
           int pageCount)
  : Product(name, price)
  , author(author)
  , isbn(isbn)
  , pageCount(pageCount)
{}

// Type tag
string Book::getType() const {
    return "Book";
}

// Print all details
void Book::display(ostream& os) const {
    os  << "[Book] "
        << name
        << " by "
        << author
        << " (ISBN: "
        << isbn
        << ", "
        << pageCount
        << " pp.) - $"
        << price;

    // if a discount has been applied
     if (hasDiscount()) {    
           os << "\n  Discounted Price: $" << getPrice()
           << "\n  You Save: $" << (price - getPrice());
        }
    os << "\n";
}

// Overloading << operator by Jawad Khadra
ostream& operator<<(ostream& os, const Book& book) {
    book.display(os);
    return os;
}

// Accessors
const string& Book::getAuthor() const {
    return author;
}

const string& Book::getISBN() const {
    return isbn;
}

int Book::getPageCount() const {
    return pageCount;
}
