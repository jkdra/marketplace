#ifndef ELECTRONICS_H
#define ELECTRONICS_H
#include "Product.h"
#include "project.h"
#include <string>

class Electronics : public Product {
public:
    Electronics(const std::string& name,
                double price,
                const std::string& brand,
                const std::string& model,
                int warrantyMonths);

    // Product interface
    std::string getType() const override;
    void display(std::ostream& os) const override;

    // Accessors
    const std::string& getBrand() const;
    const std::string& getModel() const;
    int getWarrantyMonths() const;

private:
    std::string brand;
    std::string model;
    int warrantyMonths;
};

#endif //ELECTRONICS_H
