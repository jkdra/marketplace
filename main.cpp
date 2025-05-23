#include "project.h"
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include "Book.h"
#include "Clothing.h"
#include "Electronics.h"
#include "PercentageDiscount.h"
#include "BundleDiscount.h"
#include "Search.h"
#include <iomanip>
#include <sstream>
using namespace std;

vector<std::shared_ptr<Product>> products;

// Needed for run-time
//Product::Product(const std::string &name, double price) { }


void displayAllProducts(const std::vector<std::shared_ptr<Product>>& products) {
	for (const auto& product : products) {
		std::cout << *product << "\n";
	}
}

// Jawad Khadra
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Astird Shao
void searchProducts() {
    if (products.empty()) {
        cout << "No products available to search.\n";
        return;
    }
    
    Search searcher(products);
    int searchChoice;
    
    cout << "\n===== SEARCH OPTIONS =====\n"
         << "1. Search by Name\n"
         << "2. Search by Type\n"
         << "3. Search by Price Range\n"
         << "4. Back to Main Menu\n"
         << "=======================\n"
         << "Enter your choice: ";
    cin >> searchChoice;
    clearInputBuffer();

    switch(searchChoice) {
        case 1: {
            string name;
            cout << "Enter product name to search: ";
            getline(cin, name);
            searcher.searchByName(name);
            break;
        }
        case 2: {
            string type;
            cout << "Enter product type to search: ";
            getline(cin, type);
            searcher.searchByType(type);
            break;
        }
        case 3: {
            double minPrice, maxPrice;
            cout << "Enter minimum price: ";
            cin >> minPrice;
            cout << "Enter maximum price: ";
            cin >> maxPrice;
            clearInputBuffer();
            searcher.searchByRange(minPrice, maxPrice);
            break;
        }
        case 4:
            return; // Back to main menu
        default:
            cout << "Invalid search option.\n";
    }
}

// Jawad Khadra
void displayMenu(const std::string& userName) {
    cout << "\n====================================\n";
    cout << "Welcome to the Store, " << userName << "!" << endl;
    cout << "====================================\n";
    cout << "1. Add Product" << endl
         << "2. Add User" << endl
         << "3. Create Order" << endl
         << "4. Display Products" << endl
         << "5. Display Users" << endl
         << "6. Display Orders" << endl
         << "7, Search Products" << endl
         << "8. Logout" << endl
	 << "9. Remove Product" << endl
         << "0. Exit" << endl;
    cout << "====================================\n";
}

// Jawad Khadra
shared_ptr<User> createAccount() {
    cout << "Create a new account\n";
    cout << "Enter user type (1 for Buyer, 2 for Seller): ";
    int userType;
    cin >> userType;
    clearInputBuffer();
    
    string name, email, password;
    
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter password: ";
    getline(cin, password);
    
    shared_ptr<User> newUser;
    
    if (userType == 1) {
        double startingBalance;
        cout << "Enter initial wallet balance: ";
        cin >> startingBalance;
        clearInputBuffer();
        newUser = make_shared<Buyer>(name, email, password);
        dynamic_pointer_cast<Buyer>(newUser)->depositToWallet(startingBalance);

    }
    else if (userType == 2) {
        string company;
        cout << "Enter company: ";
        getline(cin, company);
        newUser = make_shared<Seller>(name, email, password, company);
    }
    else {
        cout << "Invalid user type. Account creation failed.\n";
        return nullptr;
    }
    
    Cache::get_users().value().emplace(email, newUser);
	
    cout << "Account created successfully!\n";
    return newUser;
}

shared_ptr<User> userAuthentication() {
    shared_ptr<User> currentUser = nullptr;
    bool authenticated = false;
    
    while (!authenticated) {
        string email;
        cout << "Enter your email (or 'exit' to quit): ";
        getline(cin, email);
        
        if (email == "exit") exit(EXIT_SUCCESS);

        shared_ptr<User> user = Cache::get_user(email);

        if (user) {
            // User exists, ask for password
            bool passwordLoop = true;
            while (passwordLoop) {
                string password;
                cout << "Enter your password (or 'BACK' to return): ";
                getline(cin, password);
                
                if (password == "BACK") break; // Go back to email prompt
                
                if (user->getPassword() == password) {
                    cout << "Login successful!\n";
                    currentUser = user;
                    authenticated = true;
                    passwordLoop = false;
                } else cout << "Incorrect password. Please try again.\n";
            }
        } else {
            // User doesn't exist, offer to create account
            cout << "Email not found. Would you like to create a new account? (y/n): ";
            string response;
            getline(cin, response);
            
            if (response == "y" || response == "Y") {
                currentUser = createAccount();
                if (currentUser) authenticated = true;
            }
        }
    }
    
    return currentUser;
}

int main() {
    shared_ptr<User> currentUser = nullptr;
    
    // Handle user authentication before showing the main menu
    currentUser = userAuthentication();
    
    if (!currentUser) {
        cout << "Authentication failed. Exiting program.\n";
        return 1;
    }
    
    int menuChoice = 0;
    bool loggedIn = true;
    
    do {
        if (!loggedIn) {
            currentUser = userAuthentication();
            loggedIn = (currentUser != nullptr);
            if (!loggedIn) {
                cout << "Authentication failed. Exiting program.\n";
                return 1;
            }
        }
        
        displayMenu(currentUser->getName());
        cout << "Enter your choice: ";
        cin >> menuChoice;
        clearInputBuffer();
        
        switch (menuChoice) {
            default:
                cout << "Invalid choice: Please enter an integer between 0 – 7." << endl;
                break;
            case 0:
                cout << "Thank you for using our marketplace. Goodbye!\n";
                exit(EXIT_SUCCESS);
            case 1: {
                // Add product implementation
                if (auto seller = dynamic_pointer_cast<Seller>(currentUser)) {
                    int productType;
                    cout << "Select product type:\n";
                    cout << "1. Book\n";
                    cout << "2. Clothing\n";
                    cout << "3. Electronics\n";
                    cout << "Enter choice (1-3): ";
                    cin >> productType;
                    clearInputBuffer();
                    
                    string name;
                    double price;
                    
                    cout << "Enter product name: ";
                    getline(cin, name);
                    cout << "Enter price: ";
                    cin >> price;
                    clearInputBuffer();
                    
                    shared_ptr<Product> newProduct;
                    
                    switch (productType) {
                        case 1: { // Book
                            string author, isbn, genre;
                            int pages;
                            
                            cout << "Enter author: ";
                            getline(cin, author);
                            cout << "Enter ISBN: ";
                            getline(cin, isbn);
                            cout << "Enter genre: ";
                            getline(cin, genre);
                            cout << "Enter number of pages: ";
                            cin >> pages;
                            clearInputBuffer();
                            
                            newProduct = make_shared<Book>(name, price, author, isbn, pages);
                            break;
                        }
                        case 2: { // Clothing
                            string size, color, material;
                            
                            cout << "Enter size: ";
                            getline(cin, size);
                            cout << "Enter color: ";
                            getline(cin, color);
                            cout << "Enter material: ";
                            getline(cin, material);
                            
                            newProduct = make_shared<Clothing>(name, price, size, color, material);
                            break;
                        }
                        case 3: { // Electronics
                            string brand, model;
                            int warrantyMonths;
                            
                            cout << "Enter brand: ";
                            getline(cin, brand);
                            cout << "Enter model: ";
                            getline(cin, model);
                            cout << "Enter warranty period (months): ";
                            cin >> warrantyMonths;
                            clearInputBuffer();
                            
                            newProduct = make_shared<Electronics>(name, price, brand, model, warrantyMonths);
                            break;
                        }
                        default:
                            cout << "Invalid product type selected.\n";
                            break;
                    }
                    
                    if (newProduct) {
                        // Add discount option
                        cout << "Add discount? (y/n): ";
                        string response;
                        getline(cin, response);
                        
                        if (response == "y" || response == "Y") {
                            int discountType;
                            cout << "Select discount type:\n";
                            cout << "1. Percentage Discount\n";
                            cout << "2. Bundle Discount\n";
                            cout << "Enter choice (1-2): ";
                            cin >> discountType;
                            clearInputBuffer();
                            
                            if (discountType == 1) {
                                double percentage;
                                cout << "Enter discount percentage (1-100): ";
                                cin >> percentage;
                                clearInputBuffer();
                                
                                newProduct->setDiscount(make_unique<PercentageDiscount>(percentage));
                            } else if (discountType == 2) {
                                int buyX, getYFree;
                                cout << "Enter buy X amount: ";
                                cin >> buyX;
                                cout << "Enter get Y free amount: ";
                                cin >> getYFree;
                                clearInputBuffer();
                                
                                newProduct->setDiscount(make_unique<BundleDiscount>(buyX, getYFree));
                            }
                        }
                        
                        products.push_back(newProduct);
                        seller->addProduct(newProduct);
                        cout << "Product added successfully.\n";
                        cout << "Product added successfully.\n";
                    }
                } else {
                    cout << "Only sellers can add products.\n";
                }
                break;
            }
            case 2: {
                shared_ptr<User> newUser = createAccount();
                break;
            }
            case 3: {
                // Create order implementation
                if (auto buyer = dynamic_pointer_cast<Buyer>(currentUser)) {
                    if (products.empty()) {
                        cout << "No products available for ordering.\n";
                        break;
                    }
                    
                    cout << "\n===== Available Products =====\n";
                    for (size_t i = 0; i < products.size(); ++i) {
                        cout << i + 1 << ". " << *products[i] << "\n";
                    }
                    
                    int productChoice;
                    cout << "\nEnter product number to order (1-" << products.size() << "): ";
                    cin >> productChoice;
                    clearInputBuffer();
                    
                    if (productChoice < 1 || productChoice > static_cast<int>(products.size())) {
                        cout << "Invalid product selection.\n";
                        break;
                    }
                    
                    int quantity;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    clearInputBuffer();
                    
                    if (quantity <= 0) {
                        cout << "Invalid quantity.\n";
                        break;
                    }
                    
                    shared_ptr<Product> selectedProduct = products[productChoice - 1];
                    double totalPrice = selectedProduct->getPrice(quantity);
                    
                    cout << "\nOrder Summary:\n";
                    cout << "Product: " << selectedProduct->getName() << "\n";
                    cout << "Quantity: " << quantity << "\n";
                    cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << "\n";
                    cout << "Wallet Balance: $" << buyer->getWallet().getBalance() << "\n";
                    cout << "Confirm order? (y/n): ";
                    string confirm;
                    getline(cin, confirm);
                    
                    if (confirm == "y" || confirm == "Y") {
                        // Create order string
                        ostringstream orderDetails;
                        orderDetails << selectedProduct->getName() 
                                    << " (x" << quantity << ") - $" 
                                    << fixed << setprecision(2) << totalPrice;
                        
                        try {
                            buyer->addOrder(selectedProduct);
                            cout << "Order placed successfully!\n";
                        }
                        catch (const InsufficientFundsException& e) {
                            cout << "Order failed: " << e.what() << "\n";
                        }
                        
                    } else {
                        cout << "Order cancelled.\n";
                    }
                } else {
                    cout << "Only buyers can create orders.\n";
                }
                break;
            }
            case 4:
                // Display products
                if (products.empty()) {
                    cout << "No products available.\n";
                } else {
                    cout << "\n===== Available Products =====\n";
                    displayAllProducts(products);
                }
                break;
            case 5:
                // Display users
                if (Cache::get_user(currentUser->getEmail())) {
                    cout << "\n===== Registered Users =====\n";
                    Cache::display_all_users();
                } else {
                    cout << "No users found.\n";
                }
                break;
            case 6:
                // Display orders
                if (auto buyer = dynamic_pointer_cast<Buyer>(currentUser)) {
                    cout << "\n===== Your Orders =====\n";
                    const auto& orders = buyer->getOrders();  // We'll define this getter next
                    if (orders.empty()) {
                        cout << "You have no orders.\n";
                    }
                    else {
                        for (const auto& order : orders) {
                            cout << *order << "\n";
                        }
                    }
                }
                else {
                    cout << "Only buyers can view orders.\n";
                }
                break;

            case 7: // search products/ filter system
                searchProducts();
		    break;
            case 8:
                // Logout
                cout << "Logging out...\n";
                loggedIn = false;
                break;
	    case 9: {
    if (auto seller = dynamic_pointer_cast<Seller>(currentUser)) {
        const auto& sellerProducts = seller->getProducts();
        if (sellerProducts.empty()) {
            cout << "You have no products to remove.\n";
            break;
        }

        // Display current products
        cout << "\n===== Your Products =====\n";
        for (size_t i = 0; i < sellerProducts.size(); ++i) {
            cout << i + 1 << ". " << *sellerProducts[i] << "\n";
        }

        // Ask for product name to remove
        cout << "\nEnter the name of the product you want to remove: ";
        string name;
        getline(cin, name);

        seller->removeProduct(name);
        cout << "Product(s) removed if matched.\n";
    } else {
        cout << "Only sellers can remove products.\n";
    }
    break;
}

        }
    } while (true);
    
    return 0;
}
