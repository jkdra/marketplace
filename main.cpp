#include "project.h"
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
using namespace std;

vector<std::shared_ptr<Product>> products;

void displayAllProducts(const std::vector<std::shared_ptr<Product>>& products) {
	for (const auto& product : products) {
		std::cout << *product << "\n";
	}
}

// Jawad Khadra
void clearInputBuffer() {
    cin.clear();
    cin.ignore();
}

void userAuthentication() {
	cout << "Enter your email: ";
}

// Jawad Khadra
void displayMenu() {
    cout
    << "Welcome to the Store" << endl
    << "1. Add Product" << endl
    << "2. Add User" << endl
    << "3. Create Order" << endl
    << "4. Display Products" << endl
    << "5. Display Users" << endl
    << "6. Display Orders" << endl
    << "0. Exit" << endl;
}

int main() {
	int menuChoice = 0;
	storeUser userStoring;
	do {
		displayMenu();
		cout << "Enter your choice: ";
		cin >> menuChoice;
		clearInputBuffer();
		switch (menuChoice) {
			default:
				cout << "Invalid choice: Please enter an integer between 0 – 6." << endl;
				break;
			case 0:
				exit(EXIT_SUCCESS);
			case 1:

				break;
			case 2: {
				cout << "Enter user type (1 for Buyer, 2 for Seller): ";
				int userType;
				cin >> userType;
				clearInputBuffer();
				if (userType == 1) {
					string name, email, password;
					cout << "Enter name: ";
					getline(cin, name);
					cout << "Enter email: ";
					getline(cin, email);
					cout << "Enter password: ";
					getline(cin, password);
					userStoring.addUser(make_shared <Buyer>(name, email, password));
				}
				else if (userType == 2) {
					string name, email, password, company;
					cout << "Enter name: ";
					getline(cin, name);
					cout << "Enter email: ";
					getline(cin, email);
					cout << "Enter password: ";
					getline(cin, password);
					cout << "Enter company: ";
					getline(cin, company);
					userStoring.addUser(make_shared <Seller>(name, email, password, company));
				}
				break;
							}
							case 3: {
				string email, password;
				cout << "Enter your email: ";
				getline(cin, email);
				cout << "Enter your password: ";
				getline(cin, password);
				clearInputBuffer();
				
				shared_ptr<User> user = userStoring.findUserByEmail(email);
				if (user && user->getPassword() == password) {
					cout << "Welcome, " << user->getName() << "!" << endl;
					// need a display products function
					// need a create order function
				}
				else {
					cout << "Invalid email or password." << endl;
				}
				break;
							}
				// Add other cases as needed
			}
	} while (menuChoice != 0);
	return 0;
}