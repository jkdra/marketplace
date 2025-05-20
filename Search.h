
//  Search.h
// Wrote by Astrid Shao

#ifndef SEARCH_H
#define SEARCH_H

#include "Product.h"
#include "project.h"

class Search {
public:
    
    // constructor
    Search(vector<shared_ptr<Product>>& products);
    void searchByName(const string& name) const;
    void searchByType(const string& type) const;
    void searchByRange(double min, double max) const;
    
private:
    vector<shared_ptr<Product>>& products;
    
};

#endif
