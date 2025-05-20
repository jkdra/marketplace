#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include <memory>
#include "User.h"
#include "Product.h"

class Transaction {
public:
    Transaction(std::shared_ptr<User> buyer,
                std::shared_ptr<User> seller,
                std::shared_ptr<Product> product);

    // ID access
    const std::string& getId() const;

    std::shared_ptr<User> getBuyer() const;
    std::shared_ptr<User> getSeller() const;
    std::shared_ptr<Product> getProduct() const;
    std::string getTimestamp() const;

    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);

private:
    std::string id;
    std::shared_ptr<User> buyer;
    std::shared_ptr<User> seller;
    std::shared_ptr<Product> product;
    std::string timestamp;

    void setTimestamp();

    static std::size_t nextTxId;
    static std::string makeTxId();
};

#endif //TRANSACTIONS_H
