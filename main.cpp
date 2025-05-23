#include "project.h"
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include "Book.h"
#include "Clothing.h"
#include "Electronics.h"
#include "PercentageDiscount.h"
#include "BundleDiscount.h"
#include <iomanip>
#include <sstream>
using namespace std;

vector<std::shared_ptr<Product>> products;

// Needed for run-time
User::User(const string &name, const string &email, const string &password) { }
Product::Product(const std::string &name, double price) { }


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
         << "7. Logout" << endl
         << "0. Exit" << endl;
    cout << "====================================\n";
}

// Jawad Khadra
shared_ptr<User> createAccount(storeUser& userStoring) {
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
        newUser = make_shared<Buyer>(name, email, password);
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
    
    userStoring.addUser(newUser);
    cout << "Account created successfully!\n";
    return newUser;
}

shared_ptr<User> userAuthentication(storeUser& userStoring) {
    shared_ptr<User> currentUser = nullptr;
    bool authenticated = false;
    
    while (!authenticated) {
        string email;
        cout << "Enter your email (or 'exit' to quit): ";
        getline(cin, email);
        
        if (email == "exit") exit(EXIT_SUCCESS);
        
        shared_ptr<User> user = userStoring.findUserByEmail(email);
        
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
                currentUser = createAccount(userStoring);
                if (currentUser) authenticated = true;
            }
        }
    }
    
    return currentUser;
}

int main() {
    storeUser userStoring;
    shared_ptr<User> currentUser = nullptr;
    
    // Handle user authentication before showing the main menu
    currentUser = userAuthentication(userStoring);
    
    if (!currentUser) {
        cout << "Authentication failed. Exiting program.\n";
        return 1;
    }
    
    int menuChoice = 0;
    bool loggedIn = true;
    
    do {
        if (!loggedIn) {
            currentUser = userAuthentication(userStoring);
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
                        cout << "Product added successfully.\n";
                    }
                } else {
                    cout << "Only sellers can add products.\n";
                }
                break;
            }
            case 2: {
                shared_ptr<User> newUser = createAccount(userStoring);
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
                    
                    cout << "Confirm order? (y/n): ";
                    string confirm;
                    getline(cin, confirm);
                    
                    if (confirm == "y" || confirm == "Y") {
                        // Create order string
                        ostringstream orderDetails;
                        orderDetails << selectedProduct->getName() 
                                    << " (x" << quantity << ") - $" 
                                    << fixed << setprecision(2) << totalPrice;
                        
                        buyer->addOrder(selectedProduct);
                        cout << "Order placed successfully!\n";
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
                if (userStoring.findUserByEmail(currentUser->getEmail())) {
                    cout << "\n===== Registered Users =====\n";
                    userStoring.displayAllUsers();
                } else {
                    cout << "No users found.\n";
                }
                break;
            case 6:
                // Display orders
                if (auto buyer = dynamic_pointer_cast<Buyer>(currentUser)) {
                    cout << "\n===== Your Orders =====\n";
                } else cout << "Only buyers can view orders.\n";
                break;
            case 7:
                // Logout
                cout << "Logging out...\n";
                loggedIn = false;
                break;
        }
    } while (true);
    
    return 0;
}