#ifndef BOOK_H
#define BOOK_H
#include "Product.h"
#include <string>

using namespace std;

class Book : public Product {
public:
    Book(const string& name,
         double price,
         const string& author,
         const string& isbn,
         int pageCount);

    // Product interface
    string getType() const override;
    void display(ostream& os) const override;

    // Accessors
    const string& getAuthor() const;
    const string& getISBN() const;
    int getPageCount() const;

    // Overloading << operator by Jawad Khadra
    friend ostream& operator<<(ostream& os, const Book& book);

private:
    string author;
    string isbn;
    int pageCount;
};
#endif //BOOK_H
