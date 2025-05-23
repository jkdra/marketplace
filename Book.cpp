#include "Book.h"
#include <iostream>

// Constructor
Book::Book(const std::string& name,
           double price,
           const std::string& author,
           const std::string& isbn,
           int pageCount)
  : Product(name, price)
  , author(author)
  , isbn(isbn)
  , pageCount(pageCount)
{}

// Type tag
std::string Book::getType() const {
    return "Book";
}

// Print all details
void Book::display(std::ostream& os) const {
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

    // if discount has been applied
     if (hasDiscount()) {    
           os << "\n  Discounted Price: $" << getPrice()
           << "\n  You Save: $" << (price - getPrice());
        }
    os << "\n";
}

// Accessors
const std::string& Book::getAuthor() const {
    return author;
}

const std::string& Book::getISBN() const {
    return isbn;
}

int Book::getPageCount() const {
    return pageCount;
}
