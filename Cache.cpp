// Justin Dodd

#include "Cache.h"

// init static variables
optional<map<string, shared_ptr<User>>> Cache::users = nullopt;
optional<map<size_t, shared_ptr<Product>>> Cache::products = nullopt;
optional<map<size_t, shared_ptr<Transaction>>> Cache::transactions = nullopt;
optional<string> Cache::filename = nullopt;

// self-explanatory, only append if not already in vector
template<typename T>
void push_back_unique(vector<T>& vec, const T& value) {
	if (find(vec.begin(), vec.end(), value) == vec.end()) {
		vec.push_back(value);
	}
}

// split string into parts by delimiter
vector<string> split(const string& str, char delimiter) {
	vector<string> parts = vector<string>();
	
	// append everything between delimiters, if any
	size_t idx = 0, idx_delim = str.find(delimiter);
	while (idx_delim != string::npos) {
		parts.push_back(str.substr(idx, idx_delim - idx));
		
		// move to the next possible delimiter
		idx = idx_delim + 1;
		idx_delim = str.find(delimiter, idx);
	}
	
	// add the last part
	parts.push_back(str.substr(idx, str.length() - idx));
	return parts;
}

// parse product/transaction id from string
size_t parse_id(const char& prefix, const string& str) {
	// check for valid prefix
	if (str.empty() || str[0] != prefix || str.length() < 2) {
		throw CacheException();
	}
	
	// parse id
	try {
		return stoul(str.substr(1));
	} catch (...) {
		throw CacheException();
	}
}

// self-explanatory
double parse_double(const string& str) {
	try { return stod(str); }
	catch (...) { throw CacheException(); }
}

// self-explanatory
int parse_int(const string& str) {
	try { return stoi(str); }
	catch (...) { throw CacheException(); }
}

// attempt to load cache from file
void Cache::load_cache(const string& filename = "exampledata.txt") {
	// try open file
	string fileStr = "";
	ifstream file(filename, ios::in);
	if (!file.is_open()) throw runtime_error("Could not open file");
	
	// temp storage during parsing
	vector<DummyBuyer> temp_buyers = vector<DummyBuyer>();
	vector<DummySeller> temp_sellers = vector<DummySeller>();
	vector<DummyBook> temp_books = vector<DummyBook>();
	vector<DummyClothing> temp_clothing = vector<DummyClothing>();
	vector<DummyElectronics> temp_electronics = vector<DummyElectronics>();
	vector<DummyTransaction> temp_transactions = vector<DummyTransaction>();
	
	try {
		// parse each line
		string line = "";
		while (getline(file, line)) {
			// skip empty lines
			if (line.empty()) {
				continue;
			}
			
			// require entry type
			size_t field_sep = line.find(':');
			if (field_sep == string::npos) {
				throw CacheException();
			}
			
			// parse entry type and its fields
			string type = line.substr(0, field_sep);
			vector<string> fields = split(line.substr(field_sep + 1), '|');
			if (type == "Buyer") {
				// requires `name`, `email`, `password`, `balance`, and at least one `PID`
				if (fields.size() < 5) {
					throw CacheException();
				}
				
				// check for valid product ids
				vector<size_t> product_ids = vector<size_t>();
				for (size_t i = 4; i < fields.size(); ++i) {
					size_t id_num = parse_id('P', fields[i]);
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
				vector<size_t> product_ids = vector<size_t>();
				for (size_t i = 4; i < fields.size(); ++i) {
					size_t id_num = parse_id('P', fields[i]);
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
		map<size_t, shared_ptr<Product>> products = map<size_t, shared_ptr<Product>>();
		size_t max_id = -1;
		
		for (size_t i = 0; i < temp_books.size(); ++i) {
			DummyBook& dummy = temp_books[i];
			
			// must be unique
			if (products.find(dummy.id) != products.end()) {
				throw CacheException();
			}
			
			shared_ptr<Book> book = make_shared<Book>(dummy.name, dummy.price, dummy.author, dummy.isbn, dummy.page_count);
			book->id = dummy.id;
			products.emplace(dummy.id, book);
			max_id = max(max_id, dummy.id);
		}
		
		for (size_t i = 0; i < temp_clothing.size(); ++i) {
			DummyClothing& dummy = temp_clothing[i];
			
			// must be unique
			if (products.find(dummy.id) != products.end()) {
				throw CacheException();
			}
			
			shared_ptr<Clothing> clothing = make_shared<Clothing>(dummy.name, dummy.price, dummy.size, dummy.material, dummy.brand);
			clothing->id = dummy.id;
			products.emplace(dummy.id, clothing);
			max_id = max(max_id, dummy.id);
		}
		
		for (auto & dummy : temp_electronics) {
			// must be unique
			if (products.find(dummy.id) != products.end()) throw CacheException();
			
			shared_ptr<Electronics> electronics = make_shared<Electronics>(dummy.name, dummy.price, dummy.brand, dummy.model, dummy.warranty_months);
			electronics->id = dummy.id;
			products.emplace(dummy.id, electronics);
			max_id = max(max_id, dummy.id);
		}
		
		Product::nextId = max_id + 1;
		Cache::products = products;
		
		// create users
		Cache::users = map<string, shared_ptr<User>>();
		
		for (auto & dummy : temp_buyers) {
			// must be unique
			if (Cache::users.value().find(dummy.email) != Cache::users.value().end()) throw CacheException();
			
			shared_ptr<Buyer> buyer = make_shared<Buyer>(dummy.name, dummy.email, dummy.password);
			
			// apply saved balance
			buyer->wallet.balance = dummy.balance;
			
			// apply saved orders
			for (size_t j = 0; j < dummy.orders.size(); ++j) {
				size_t id = dummy.orders[j];
				
				// must be valid
				if (products.find(id) == products.end()) throw CacheException();
				
				push_back_unique(buyer->myOrders, products.at(id));
			}
			
			Cache::users.value().emplace(dummy.email, buyer);
		}
		
		for (auto & dummy : temp_sellers) {
				// must be unique
			if (Cache::users.value().find(dummy.email) != Cache::users.value().end()) throw CacheException();
			
			shared_ptr<Seller> seller = make_shared<Seller>(dummy.name, dummy.email, dummy.password, dummy.company);
			
			// apply saved products
			for (unsigned long id : dummy.products) {
					// must be valid
				if (products.find(id) == products.end()) throw CacheException();
				
				push_back_unique(seller->myProducts, products.at(id));
			}
		}
		
		// create transactions
		Cache::transactions = map<size_t, shared_ptr<Transaction>>();
		
		for (auto & dummy : temp_transactions) {
				// must be unique
			if (Cache::transactions.value().find(dummy.id) != Cache::transactions.value().end()) throw CacheException();
			
			shared_ptr<User> buyer = Cache::users.value().at(dummy.buyer_email);
			shared_ptr<User> seller = Cache::users.value().at(dummy.seller_email);
			shared_ptr<Product> product = products.at(dummy.product_id);
			
			// must be valid
			if (buyer == nullptr || seller == nullptr || product == nullptr) throw CacheException();
			
			shared_ptr<Transaction> transaction = make_shared<Transaction>(buyer, seller, product);
			
			// apply saved timestamp
			transaction->timestamp = dummy.timestamp;
			
			Cache::transactions.value().emplace(dummy.id, transaction);
		}
	} catch (...) {
		// clean up and rethrow exception
		file.close();
		
		Cache::filename = nullopt;
		
		Cache::users = nullopt;
		Cache::products = nullopt;
		Cache::transactions = nullopt;
		
		throw;
	}
	
	// clean up and finish
	file.close();
	Cache::filename = filename;
}

// attempt to save cache to file
void Cache::save_cache(const optional<string>& filename = nullopt) {
	// check for valid cache
	if (!Cache::users.has_value()) {
		throw CacheException();
	}
	
	// overwrite cache filename if provided
	if (filename.has_value()) Cache::filename = filename;
	else if (!Cache::filename.has_value()) {
		throw runtime_error("no filename provided");
	}
	
	ofstream file(Cache::filename.value(), ios::out | ios::trunc);
	if (!file.is_open()) {
		throw runtime_error("could not open file");
	}
	
	try {
		// keep track of products
		vector<shared_ptr<Product>> products = vector<shared_ptr<Product>>();
		
		// iterate and encode user data to file
		for (map<string, shared_ptr<User>>::const_iterator iterator = Cache::users.value().begin(); iterator != Cache::users.value().end(); ++iterator) {
			const shared_ptr<User>& user = iterator->second;
			string ret = user->getType() + ":" + user->getName() + "|" + user->getEmail() + "|" + user->getPassword();
			
			// encode user type specific data
			if (user->getType() == "Buyer") {
				const Buyer& buyer = *dynamic_pointer_cast<Buyer>(user);
				ret += "|" + to_string(buyer.getWallet().getBalance());
				
				// encode orders
				for (size_t i = 0; i < buyer.myOrders.size(); ++i) {
					ret += "|" + products[i]->getId();
					
					// add product to tracking vector
					push_back_unique(products, buyer.myOrders[i]);
				}
			} else if (user->getType() == "Seller") {
				const Seller& seller = *dynamic_pointer_cast<Seller>(user);
				ret += "|" + seller.getCompany();
				
				// encode products
				for (size_t i = 0; i < seller.getProducts().size(); ++i) {
					ret += "|" + products[i]->getId();
					
					// add product to tracking vector
					push_back_unique(products, seller.getProducts()[i]);
				}
			} else { throw CacheException(); }
			
			file << ret << "\n";
		}
		
		// iterate and encode transaction data to file
		for (map<size_t, shared_ptr<Transaction>>::const_iterator iterator = Cache::transactions.value().begin(); iterator != Cache::transactions.value().end(); ++iterator) {
			const shared_ptr<Transaction>& transaction = iterator->second;
			string ret = "Transaction:" + transaction->getId() + "|" + transaction->getBuyer()->getEmail() + "|" + transaction->getSeller()->getEmail() + "|" + transaction->getProduct()->getId() + "|" + transaction->getTimestamp();
			
			// add product to tracking vector
			push_back_unique(products, transaction->getProduct());
			
			file << ret << "\n";
		}
		
		// iterate and encode product data to file
		for (size_t i = 0; i < products.size(); ++i) {
			const shared_ptr<Product>& product = products[i];
			string ret = product->getType() + ":" + product->getName() + "|" + to_string(product->getPrice());
			
			// encode product type specific data
			if (product->getType() == "Book") {
				const Book& book = *dynamic_pointer_cast<Book>(product);
				ret += "|" + book.getAuthor() + "|" + book.getISBN() + "|" + to_string(book.getPageCount());
			} else if (product->getType() == "Clothing") {
				const Clothing& clothing = *dynamic_pointer_cast<Clothing>(product);
				ret += "|" + clothing.getSize() + "|" + clothing.getMaterial() + "|" + clothing.getBrand();
			} else if (product->getType() == "Electronics") {
				const Electronics& electronics = *dynamic_pointer_cast<Electronics>(product);
				ret += "|" + electronics.getBrand() + "|" + electronics.getModel() + "|" + to_string(electronics.getWarrantyMonths());
			} else { throw CacheException(); }
			
			file << ret << "\n";
		}
	} catch (...) {
		// clean up and rethrow exception
		file.close();
		throw;
	}
	
	file << flush;
	file.close();
}

optional<map<string, shared_ptr<User>>> Cache::get_users() {
	return Cache::users;
}

optional<map<size_t, shared_ptr<Transaction>>> Cache::get_transactions() {
	return Cache::transactions;
}

shared_ptr<User> Cache::get_user(const string& email) {
	if (!Cache::users.has_value()) {
		return nullptr;
	}
	
	auto it = Cache::users.value().find(email);
	if (it != Cache::users.value().end()) {
		return it->second;
	}
	
	return nullptr;
}

void Cache::display_all_users() {
	if (!Cache::users.has_value()) {
		cout << "No users registered." << endl;
		return;
	}
	
	for (const auto& user : Cache::users.value()) {
		cout << *user.second << endl;
	}
}
