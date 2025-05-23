// Justin Dodd

#ifndef CACHE_H
#define CACHE_H

#include "project.h"

#include "Book.h"
#include "Buyer.h"
#include "Clothing.h"
#include "Electronics.h"
#include "Exceptions.h"
#include "Seller.h"
#include "Transactions.h"

class Cache {
	public:
	
	// attempt to load cache from a file
	static void load_cache(const std::string& filename);
	
	// attempt to save cache to file
	static void save_cache(const std::optional<std::string>& filename);
	
	private:
	
	// current target file, 
	static std::optional<std::string> filename;
	
	// functional cache
	static std::optional<std::map<std::string, std::shared_ptr<User>>> users;
	static std::optional<std::map<std::size_t, std::shared_ptr<Transaction>>> transactions;
};

// dummy classes for parsing purposes
// format:
/*
	Buyer:name|email|password|balance|PID|PID...
	Seller:name|email|password|company|PID|PID...
	Book:PID,name|price|author|isbn|pagecount
	Clothing:PID|name|price|size|material|brand
	Electronics:PID|name|price|brand|model|warrantymonths
	Transaction:TID|buyeremail|selleremail|PID|timestamp
*/

struct DummyBuyer {
	std::string name;
	std::string email;
	std::string password;
	double balance;
	std::vector<std::size_t> orders;
	
	bool operator==(const DummyBuyer& other) const {
		return name == other.name &&
			   email == other.email &&
			   password == other.password &&
			   balance == other.balance &&
			   orders == other.orders;
	}
};

struct DummySeller {
	std::string name;
	std::string email;
	std::string password;
	std::string company;
	std::vector<std::size_t> products;
	
	bool operator==(const DummySeller& other) const {
		return name == other.name &&
			   email == other.email &&
			   password == other.password &&
			   company == other.company &&
			   products == other.products;
	}
};

struct DummyBook {
	std::size_t id;
	std::string name;
	double price;
	std::string author;
	std::string isbn;
	int page_count;
	
	bool operator==(const DummyBook& other) const {
		return id == other.id &&
			   name == other.name &&
			   price == other.price &&
			   author == other.author &&
			   isbn == other.isbn &&
			   page_count == other.page_count;
	}
};

struct DummyClothing {
	std::size_t id;
	std::string name;
	double price;
	std::string size;
	std::string material;
	std::string brand;
	
	bool operator==(const DummyClothing& other) const {
		return id == other.id &&
			   name == other.name &&
			   price == other.price &&
			   size == other.size &&
			   material == other.material &&
			   brand == other.brand;
	}
};

struct DummyElectronics {
	std::size_t id;
	std::string name;
	double price;
	std::string brand;
	std::string model;
	int warranty_months;
	
	bool operator==(const DummyElectronics& other) const {
		return id == other.id &&
			   name == other.name &&
			   price == other.price &&
			   brand == other.brand &&
			   model == other.model &&
			   warranty_months == other.warranty_months;
	}
};

struct DummyTransaction {
	std::size_t id;
	std::string buyer_email;
	std::string seller_email;
	std::size_t product_id;
	std::string timestamp;
	
	bool operator==(const DummyTransaction& other) const {
		return id == other.id &&
			   buyer_email == other.buyer_email &&
			   seller_email == other.seller_email &&
			   product_id == other.product_id &&
			   timestamp == other.timestamp;
	}
};

#endif
