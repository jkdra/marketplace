// Justin Dodd

#include "Cache.h"

// self explanatory, only append if not already in vector
template<typename T>
void push_back_unique(std::vector<T>& vec, const T& value) {
	if (std::find(vec.begin(), vec.end(), value) == vec.end()) {
		vec.push_back(value);
	}
}

// split string into parts by delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> parts = std::vector<std::string>();
	
	// append everything between delimiters, if any
	std::size_t idx = 0, idx_delim = str.find(delimiter);
	while (idx_delim != std::string::npos) {
		parts.push_back(str.substr(idx, idx_delim - idx));
		
		// move to next possible delimiter
		idx = idx_delim + 1;
		idx_delim = str.find(delimiter, idx);
	}
	
	// add the last part
	parts.push_back(str.substr(idx, str.length() - idx));
	return parts;
}

// parse product/transaction id from string
std::size_t parse_id(const char& prefix, const std::string& str) {
	// check for valid prefix
	if (str.empty() || str[0] != prefix || str.length() < 2) {
		throw CacheException();
	}
	
	// parse id
	try {
		return std::stoul(str.substr(1));
	} catch (const std::invalid_argument& e) {
		throw CacheException();
	}
}

// self explanatory
double parse_double(const std::string& str) {
	try {
		return std::stod(str);
	} catch (const std::invalid_argument& e) {
		throw CacheException();
	}
}

// self explanatory
int parse_int(const std::string& str) {
	try {
		return std::stoi(str);
	} catch (const std::invalid_argument& e) {
		throw CacheException();
	}
}

void Cache::load_cache(const std::string& filename = "exampledata.txt") {
	// try open file
	std::string fileStr = "";
	std::ifstream file(filename, std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}
	
	// temp storage during parsing
	std::vector<DummyBuyer> temp_buyers = std::vector<DummyBuyer>();
	std::vector<DummySeller> temp_sellers = std::vector<DummySeller>();
	std::vector<DummyBook> temp_books = std::vector<DummyBook>();
	std::vector<DummyClothing> temp_clothing = std::vector<DummyClothing>();
	std::vector<DummyElectronics> temp_electronics = std::vector<DummyElectronics>();
	std::vector<DummyTransaction> temp_transactions = std::vector<DummyTransaction>();
	
	try {
		// parse each line
		std::string line = "";
		while (std::getline(file, line)) {
			// skip empty lines
			if (line.empty()) {
				continue;
			}
			
			// require entry type
			std::size_t field_sep = line.find(':');
			if (field_sep == std::string::npos) {
				throw CacheException();
			}
			
			// parse entry type and its fields
			std::string type = line.substr(0, field_sep);
			std::vector<std::string> fields = split(line.substr(field_sep + 1), '|');
			if (type == "Buyer") {
				// requires `name`, `email`, `password`, `balance`, and at least one `PID`
				if (fields.size() < 5) {
					throw CacheException();
				}
				
				// check for valid product ids
				std::vector<std::size_t> product_ids = std::vector<std::size_t>();
				for (std::size_t i = 4; i < fields.size(); ++i) {
					std::size_t id_num = parse_id('P', fields[i]);
					push_back_unique(product_ids, id_num);
				}
				
				// add to temp storage
				DummyBuyer buyer;
				buyer.name = fields[0];
				buyer.email = fields[1];
				buyer.password = fields[2];
				buyer.balance = parse_double(fields[3]);
				buyer.orders = product_ids;
				push_back_unique(temp_buyers, buyer);
			} else if (type == "Seller") {
				// requires `name`, `email`, `password`, `company`, and at least one `PID`
				if (fields.size() < 5) {
					throw CacheException();
				}
				
				// check for valid product ids
				std::vector<std::size_t> product_ids = std::vector<std::size_t>();
				for (std::size_t i = 4; i < fields.size(); ++i) {
					std::size_t id_num = parse_id('P', fields[i]);
					push_back_unique(product_ids, id_num);
				}
				
				// add to temp storage
				DummySeller seller;
				seller.name = fields[0];
				seller.email = fields[1];
				seller.password = fields[2];
				seller.company = fields[3];
				seller.products = product_ids;
				push_back_unique(temp_sellers, seller);
			} else if (type == "Book") {
				// requires `PID`, `name`, `price`, `author`, `isbn`, and `pagecount`
				if (fields.size() != 6) {
					throw CacheException();
				}
				
				// add to temp storage
				DummyBook book;
				book.id = parse_id('P', fields[0]);
				book.name = fields[1];
				book.price = parse_double(fields[2]);
				book.author = fields[3];
				book.isbn = fields[4];
				book.page_count = parse_int(fields[5]);
				push_back_unique(temp_books, book);
			} else if (type == "Clothing") {
				// requires `PID`, `name`, `price`, `size`, `material`, and `brand`
				if (fields.size() != 6) {
					throw CacheException();
				}
				
				// add to temp storage
				DummyClothing clothing;
				clothing.id = parse_id('P', fields[0]);
				clothing.name = fields[1];
				clothing.price = parse_double(fields[2]);
				clothing.size = fields[3];
				clothing.material = fields[4];
				clothing.brand = fields[5];
				push_back_unique(temp_clothing, clothing);
			} else if (type == "Electronics") {
				// requires `PID`, `name`, `price`, `brand`, `model`, and `warrantymonths`
				if (fields.size() != 6) {
					throw CacheException();
				}
				
				// add to temp storage
				DummyElectronics electronics;
				electronics.id = parse_id('P', fields[0]);
				electronics.name = fields[1];
				electronics.price = parse_double(fields[2]);
				electronics.brand = fields[3];
				electronics.model = fields[4];
				electronics.warranty_months = parse_int(fields[5]);
				push_back_unique(temp_electronics, electronics);
			} else if (type == "Transaction") {
				// requires `TID`, `buyeremail`, `selleremail`, `PID`, and `timestamp`
				if (fields.size() != 5) {
					throw CacheException();
				}
				
				DummyTransaction transaction;
				transaction.id = parse_id('T', fields[0]);
				transaction.buyer_email = fields[1];
				transaction.seller_email = fields[2];
				transaction.product_id = parse_id('P', fields[3]);
				transaction.timestamp = fields[4];
				push_back_unique(temp_transactions, transaction);
			} else {
				throw CacheException();
			}
		}
		
		// create products
		std::map<std::size_t, std::shared_ptr<Product>> products = std::map<std::size_t, std::shared_ptr<Product>>();
		std::size_t max_id = -1;
		
		for (std::size_t i = 0; i < temp_books.size(); ++i) {
			DummyBook& dummy = temp_books[i];
			
			// must be unique
			if (products.find(dummy.id) != products.end()) {
				throw CacheException();
			}
			
			std::shared_ptr<Book> book = std::make_shared<Book>(dummy.name, dummy.price, dummy.author, dummy.isbn, dummy.page_count);
			book->id = dummy.id;
			products.emplace(dummy.id, book);
			max_id = std::max(max_id, dummy.id);
		}
		
		for (std::size_t i = 0; i < temp_clothing.size(); ++i) {
			DummyClothing& dummy = temp_clothing[i];
			
			// must be unique
			if (products.find(dummy.id) != products.end()) {
				throw CacheException();
			}
			
			std::shared_ptr<Clothing> clothing = std::make_shared<Clothing>(dummy.name, dummy.price, dummy.size, dummy.material, dummy.brand);
			clothing->id = dummy.id;
			products.emplace(dummy.id, clothing);
			max_id = std::max(max_id, dummy.id);
		}
		
		for (std::size_t i = 0; i < temp_electronics.size(); ++i) {
			DummyElectronics& dummy = temp_electronics[i];
			
			// must be unique
			if (products.find(dummy.id) != products.end()) {
				throw CacheException();
			}
			
			std::shared_ptr<Electronics> electronics = std::make_shared<Electronics>(dummy.name, dummy.price, dummy.brand, dummy.model, dummy.warranty_months);
			electronics->id = dummy.id;
			products.emplace(dummy.id, electronics);
			max_id = std::max(max_id, dummy.id);
		}
		
		Product::nextId = max_id + 1;
		
		// create users
		Cache::users = std::map<std::string, std::shared_ptr<User>>();
		
		for (std::size_t i = 0; i < temp_buyers.size(); ++i) {
			DummyBuyer& dummy = temp_buyers[i];
			
			// must be unique
			if (Cache::users.value().find(dummy.email) != Cache::users.value().end()) {
				throw CacheException();
			}
			
			std::shared_ptr<Buyer> buyer = std::make_shared<Buyer>(dummy.name, dummy.email, dummy.password);
			
			// apply saved balance
			buyer->myWallet.balance = dummy.balance;
			
			// apply saved orders
			for (std::size_t j = 0; j < dummy.orders.size(); ++j) {
				std::size_t id = dummy.orders[j];
				
				// must be valid
				if (products.find(id) == products.end()) {
					throw CacheException();
				}
				
				push_back_unique(buyer->myOrders, products.at(id));
			}
			
			Cache::users.value().emplace(dummy.email, buyer);
		}
		
		for (std::size_t i = 0; i < temp_sellers.size(); ++i) {
			DummySeller& dummy = temp_sellers[i];
			
			// must be unique
			if (Cache::users.value().find(dummy.email) != Cache::users.value().end()) {
				throw CacheException();
			}
			
			std::shared_ptr<Seller> seller = std::make_shared<Seller>(dummy.name, dummy.email, dummy.password, dummy.company);
			
			// apply saved products
			for (std::size_t j = 0; j < dummy.products.size(); ++j) {
				std::size_t id = dummy.products[j];
				
				// must be valid
				if (products.find(id) == products.end()) {
					throw CacheException();
				}
				
				push_back_unique(seller->myProducts, products.at(id));
			}
		}
		
		// create transactions
		Cache::transactions = std::map<std::size_t, std::shared_ptr<Transaction>>();
		
		for (std::size_t i = 0; i < temp_transactions.size(); ++i) {
			DummyTransaction& dummy = temp_transactions[i];
			
			// must be unique
			if (Cache::transactions.value().find(dummy.id) != Cache::transactions.value().end()) {
				throw CacheException();
			}
			
			std::shared_ptr<User> buyer = Cache::users.value().at(dummy.buyer_email);
			std::shared_ptr<User> seller = Cache::users.value().at(dummy.seller_email);
			std::shared_ptr<Product> product = products.at(dummy.product_id);
			
			// must be valid
			if (buyer == nullptr || seller == nullptr || product == nullptr) {
				throw CacheException();
			}
			
			std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(dummy.id, buyer, seller, product);
			
			// apply saved timestamp
			transaction->timestamp = dummy.timestamp;
			
			Cache::transactions.value().emplace(dummy.id, transaction);
		}
	} catch (...) {
		// clean up and rethrow exception
		file.close();
		
		Cache::filename = std::nullopt;
		
		Cache::users = std::nullopt;
		Cache::transactions = std::nullopt;
		
		throw;
	}
	
	// clean up and finish
	file.close();
	Cache::filename = filename;
}

void Cache::save_cache() {
	// check for valid cache
	if (!Cache::users.has_value()) {
		throw CacheException();
	} else if (!Cache::filename.has_value()) {
		throw CacheException();
	}
	
	std::ofstream file(Cache::filename.value(), std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		throw std::runtime_error("could not open file");
	}
	
	try {
		// keep track of products
		std::vector<std::shared_ptr<Product>> products = std::vector<std::shared_ptr<Product>>();
		
		// iterate and encode user data to file
		for (std::map<std::string, std::shared_ptr<User>>::const_iterator iterator = Cache::users.value().begin(); iterator != Cache::users.value().end(); ++iterator) {
			const std::shared_ptr<User>& user = iterator->second;
			std::string ret = user->getType() + ":" + user->getName() + "|" + user->getEmail() + "|" + user->getPassword();
			
			// encode user type specific data
			if (user->getType() == "Buyer") {
				const Buyer& buyer = *std::dynamic_pointer_cast<Buyer>(user);
				ret += "|" + std::to_string(buyer.getWallet().getBalance());
				
				// encode orders
				for (std::size_t i = 0; i < buyer.myOrders.size(); ++i) {
					ret += "|" + products[i]->getId();
					
					// add product to tracking vector
					push_back_unique(products, buyer.myOrders[i]);
				}
			} else if (user->getType() == "Seller") {
				const Seller& seller = *std::dynamic_pointer_cast<Seller>(user);
				ret += "|" + seller.getCompany();
				
				// encode products
				for (std::size_t i = 0; i < seller.getProducts().size(); ++i) {
					ret += "|" + products[i]->getId();
					
					// add product to tracking vector
					push_back_unique(products, seller.getProducts()[i]);
				}
			} else {
				throw CacheException();
			}
			
			file << ret << "\n";
		}
		
		// iterate and encode transaction data to file
		for (std::map<std::size_t, std::shared_ptr<Transaction>>::const_iterator iterator = Cache::transactions.value().begin(); iterator != Cache::transactions.value().end(); ++iterator) {
			const std::shared_ptr<Transaction>& transaction = iterator->second;
			std::string ret = "Transaction:" + transaction->getId() + "|" + transaction->getBuyer()->getEmail() + "|" + transaction->getSeller()->getEmail() + "|" + transaction->getProduct()->getId() + "|" + transaction->getTimestamp();
			
			// add product to tracking vector
			push_back_unique(products, transaction->getProduct());
			
			file << ret << "\n";
		}
		
		// iterate and encode product data to file
		for (std::size_t i = 0; i < products.size(); ++i) {
			const std::shared_ptr<Product>& product = products[i];
			std::string ret = product->getType() + ":" + product->getName() + "|" + std::to_string(product->getPrice());
			
			// encode product type specific data
			if (product->getType() == "Book") {
				const Book& book = *std::dynamic_pointer_cast<Book>(product);
				ret += "|" + book.getAuthor() + "|" + book.getISBN() + "|" + std::to_string(book.getPageCount());
			} else if (product->getType() == "Clothing") {
				const Clothing& clothing = *std::dynamic_pointer_cast<Clothing>(product);
				ret += "|" + clothing.getSize() + "|" + clothing.getMaterial() + "|" + clothing.getBrand();
			} else if (product->getType() == "Electronics") {
				const Electronics& electronics = *std::dynamic_pointer_cast<Electronics>(product);
				ret += "|" + electronics.getBrand() + "|" + electronics.getModel() + "|" + std::to_string(electronics.getWarrantyMonths());
			} else {
				throw CacheException();
			}
			
			file << ret << "\n";
		}
	} catch (...) {
		// clean up and rethrow exception
		file.close();
		
		throw;
	}
	
	file << std::flush;
	file.close();
}
