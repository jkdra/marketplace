#ifndef CLOTHING_H
#define CLOTHING_H
#include "Product.h"
#include <string>

class Clothing : public Product {
public:
    Clothing(const std::string& name,
             double price,
             const std::string& size,
             const std::string& material,
             const std::string& brand);

    // Product interface
    std::string getType() const override;
    void display(std::ostream& os) const override;

    // Accessors
    const std::string& getSize() const;
    const std::string& getMaterial() const;
    const std::string& getBrand() const;

private:
    std::string size;
    std::string material;
    std::string brand;
};
#endif //CLOTHING_H
