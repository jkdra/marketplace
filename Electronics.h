#ifndef ELECTRONICS_H
#define ELECTRONICS_H
#include "Product.h"
#include "project.h"
#include <string>

using namespace std;

class Electronics : public Product {
public:
    Electronics(const string& name,
                double price,
                const string& brand,
                const string& model,
                int warrantyMonths);

    // Product interface
    string getType() const override;
    void display(ostream& os) const override;

    // Accessors
    const string& getBrand() const;
    const string& getModel() const;
    int getWarrantyMonths() const;
    
    // Overloading << operator by Jawad Khadra
    friend ostream& operator<<(ostream& os, const Electronics& electronics);

private:
    string brand;
    string model;
    int warrantyMonths;
};

#endif //ELECTRONICS_H
