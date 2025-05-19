#include "project.h"
#include "User.h"
using namespace std;

// Jawad Khadra
void clearInputBuffer() {
    cin.clear();
    cin.ignore();
}

// Jawad Khadra
void displayMenu() {
    cout
    << "Welcome to the Store" << endl
    << "1. Add Product" << endl
    << "2. Add User" << endl
    << "3. Add Order" << endl
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

        switch (menuChoice) {
            default:
                cout << "Invalid choice: Please enter an integer between 0 – 6." << endl;
            break;
            case 0:
                exit(EXIT_SUCCESS);
            case 1:

                break;
            case 2:
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
                userStoring.addUser(new Buyer(name, email, password));
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
                userStoring.addUser(new Seller(name, email, password, company));

                break;
                // ... continue from here. For now we need to add more code.
            }
        } while (menuChoice != 0);

        return 0;
    } while (menuChoice != 0);
}