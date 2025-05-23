#ifndef CLOTHING_H
#define CLOTHING_H
#include "Product.h"
#include <string>

using namespace std;

class Clothing : public Product {
public:
    Clothing(const string& name,
             double price,
             const string& size,
             const string& material,
             const string& brand);

    // Product interface
    string getType() const override;
    void display(ostream& os) const override;

    // Accessors
    const string& getSize() const;
    const string& getMaterial() const;
    const string& getBrand() const;

    // Overloading << operator by Jawad Khadra
    friend ostream& operator<<(ostream& os, const Clothing& clothing);

private:
    string size;
    string material;
    string brand;
};
#endif //CLOTHING_H
