
//Search.cpp
//wrote by Astrid Shao

#include "Search.h"

// constructor
Search::Search(vector<shared_ptr<Product>>& myProducts): products(myProducts)
{}

// search by name
void Search::searchByName(const string& name) const{
    
    // creates a vector to store products that match the given name
    bool found = false;
    vector<shared_ptr<Product>> result;
    
    // Check if the product name contains the search term as a substring
    for (auto& product: products){
        //.find() returns the position (index) of the first match
        // string::npos is a special signal for "not found."
        if (product->getName().find(name) != string::npos) {
            result.push_back(product);
            found = true;
        }
    }
    if (!found) {
        cout << "No products found with name containing: " << name << endl;
    }
    else {
        cout << "Products found with name containing: " << name <<":\n";
        for (auto& p: result){
            cout << *p << endl;
        }
    }
}

//Search by type
void Search::searchByType(const string& type) const {
    vector<shared_ptr<Product>> result;
    bool found = false;

    for (auto& product : products) {
        if (product->getType() == type) {
            result.push_back(product);
            found = true;
        }
    }

    if (!found) {
        cout << "No products found with type of: " << type << endl;
    } else {
        cout << "Products found with the type of: " << type << ":\n";
        for (auto& re : result) {
            cout << *re << endl;
        }
    }
}

// Search by price range
void Search::searchByRange(double min, double max) const {
    vector<shared_ptr<Product>> result;
    bool found = false;

    for (auto& product : products) {
        double price = product->getPrice();
        if (price >= min && price <= max) {
            result.push_back(product);
            found = true;
        }
    }

    if (!found) {
        cout << "No products found with price range from " << min << " to " << max << ":\n";
    } else {
        cout << "Products found with price range from " << min << " to " << max << ":\n";
        for (auto& re : result) {
            cout << *re << endl;
        }
    }
}
