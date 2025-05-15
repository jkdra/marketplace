#include "project.h"

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
    int menuChoice;

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
                break;
                // ... continue from here. For now we need to add more code.
        }
    } while (menuChoice != 0);

    return 0;
}