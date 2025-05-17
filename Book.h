#ifndef BOOK_H
#define BOOK_H
#include "Product.h"
#include <string>

class Book : public Product {
public:
    Book(const std::string& name,
         double price,
         const std::string& author,
         const std::string& isbn,
         int pageCount);

    // Product interface
    std::string getType() const override;
    void display(std::ostream& os) const override;

    // Accessors
    const std::string& getAuthor() const;
    const std::string& getISBN() const;
    int getPageCount() const;

private:
    std::string author;
    std::string isbn;
    int pageCount;
};
#endif //BOOK_H
