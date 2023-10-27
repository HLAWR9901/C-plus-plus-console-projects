#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>

using namespace std;

// Struct for Buyer
struct Buyer {
    int accountNumber;   //starts with number 600xxx
    string name;
    string password;
    double moneyDeposit;
    string phoneNumber;
    string emailAddress;
};

// Struct for Seller
struct Seller {
    int accountNumber;  //starts with 700xxx
    string name;
    string password;
    double moneyDeposit;
    string phoneNumber;
    string emailAddress;
};

// Struct for Product
struct Product {
    string name;
    double price;
    string type;
    int totalNumber;
    string sellerPhoneNumber;
};

// Function prototypes
void introduction();
void serviceOptions();
void service();
void buyerService();
void sellerService();
void adminService();
void openTermsAndConditions();
void openHowToUse();
void aboutCompany();
void displayProductTable(const vector<Product>& products);
void displayBuyerTable(const vector<Buyer>& buyers);
void displaySellerTable(const vector<Seller>& sellers);
void buyProduct(vector<Product>& products, vector<Buyer>& buyers);
int findBuyerIndex(int accountNumber);
void saveBuyerData(const vector<Buyer>& buyers);
void saveSellerData(const vector<Seller>& sellers);
void saveProductData(const vector<Product>& products);
void searchUserByAccountName();
int getNextSellerAccountNumber();
int getNextBuyerAccountNumber();
vector<Buyer> loadBuyerData();
vector<Seller> loadSellerData();
vector<Product> loadProductData();
vector<Buyer> buyers;
vector<Seller> sellers;
vector<Product> products;

int main() {
    introduction();
    buyers = loadBuyerData();
    sellers = loadSellerData();
    products = loadProductData();
    while (true) {
        serviceOptions();
    }

    return 0;
}

// Function to generate the next available account number for buyers
int getNextBuyerAccountNumber() {
    ifstream inFile("Bfile.txt");
    int lastAccountNumber = 599999; // Initialize with the starting value - 1

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string accountStr;
            getline(ss, accountStr, ',');
            int account = stoi(accountStr);
            if (account > lastAccountNumber) {
                lastAccountNumber = account;
            }
        }
        inFile.close();
    }

    return lastAccountNumber + 1;
}

// Function to generate the next available account number for sellers
int getNextSellerAccountNumber() {
    ifstream inFile("Sfile.txt");
    int lastAccountNumber = 699999; // Initialize with the starting value - 1

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string accountStr;
            getline(ss, accountStr, ',');
            int account = stoi(accountStr);
            if (account > lastAccountNumber) {
                lastAccountNumber = account;
            }
        }
        inFile.close();
    }

    return lastAccountNumber + 1;
}


void introduction() {
    cout << "Welcome to L Digital Market!" << endl;
    // L Company's introduction
    cout << "Empowering Tomorrow's Digital World Today!\n Save your valuable time and money. Trade smarter!" << endl;
    
}

void serviceOptions() {
    service:
    cout << "\nOptions:\n"
         << "1. Service\n"
         << "2. Terms and Conditions\n"
         << "3. How to use\n"
         << "4. About\n"
         << "5. Exit\n"
         << "Choose an option: ";

    int option;
    cin >> option;

    switch (option) {
        case 1:
            service();
            break;
        case 2:
            openTermsAndConditions();
            break;
        case 3:
            openHowToUse();
            break;
        case 4:
            aboutCompany();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid option. Please choose again." << endl;
    }
    goto service;
}

void service() {
    menu:
    cout << "\nAre you :\n"
         << "1. Buyer\n"
         << "2. Seller\n"
         << "3. Admin\n"
         << "Choose an option: ";

    int options;
    cin >> options;
    switch (options) {
        case 1:
            buyerService();
            break;
        case 2:
            sellerService();
            break;
        case 3:
            adminService();
            break;
        default:
            cout << "Invalid option. Please choose again." << endl;
            system("cls");
            goto menu;
    }
}

void buyerService() {
    vector<Buyer> buyers = loadBuyerData();
    preloader:
    cout << "\nBuyer Service:\n"
         << "1. Sign Up\n"
         << "2. Log In\n"
         << "Choose an option: ";
    
    int option;
    cin >> option;
    if (option == 1) {
        Buyer newBuyer;
        newBuyer.accountNumber = getNextBuyerAccountNumber();
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, newBuyer.name);
        cout << "Enter Password: ";
        getline(cin, newBuyer.password);
        cout << "Enter Money Deposit: ";
        cin >> newBuyer.moneyDeposit;
        cout << "Enter Phone Number (10 digits only): ";
        cin.ignore();
        getline(cin, newBuyer.phoneNumber);
        cout << "Enter Email Address: ";
        getline(cin, newBuyer.emailAddress);

        buyers.push_back(newBuyer);
        saveBuyerData(buyers);
        system("cls");
        cout <<"Your Account number is " << newBuyer.accountNumber<< "\nRegistration Successful!" << endl;
        goto preloader;
        // then what
    } else if (option == 2) {
        int accountNumber;
        string password;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, password);

        bool found = false;
        for (const auto& buyer : buyers) {
            if (buyer.accountNumber == accountNumber && buyer.password == password) {
                found = true;
                cout << "Login Successful!" << endl;
                buyerPage:
                displayProductTable(products);
                buyProduct(products, buyers);
                cout << "Do you want to stay in buyer page?(Y/n): 'no' means back to main page." << endl;
                char input;
                cin >> input;
                if (input == 'Y') goto buyerPage;
                break;
            }
        }

        if (!found) {
            cout << "Invalid Account Number or Password. Please try again." << endl;
        }
    } else {
        cout << "Invalid option. Please choose again." << endl;
        goto preloader;
    }
}

void sellerService() {
    vector<Seller> sellers = loadSellerData();

    cout << "\nSeller Service:\n"
         << "1. Sign Up\n"
         << "2. Log In\n"
         << "Choose an option: ";
    preloader:
    int option;
    cin >> option;
    loader:
    if (option == 1) {
        Seller newSeller;
        newSeller.accountNumber = getNextSellerAccountNumber();
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, newSeller.name);
        cout << "Enter Password: ";
        getline(cin, newSeller.password);
        cout << "Enter Money Deposit: ";
        cin >> newSeller.moneyDeposit;
        cout << "Enter Phone Number (10 digits only): ";
        cin.ignore();
        getline(cin, newSeller.phoneNumber);
        cout << "Enter Email Address: ";
        getline(cin, newSeller.emailAddress);

        sellers.push_back(newSeller);
        saveSellerData(sellers);
        system("cls");
        cout << "Your Account number is " << newSeller.accountNumber<< "\nRegistration Successful!" << endl;
        option = 2; goto loader;
        // then what
    } else if (option == 2) {
        int accountNumber;
        string password;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, password);

        bool found = false;
        for (const auto& seller : sellers) {
            if (seller.accountNumber == accountNumber && seller.password == password) {
                found = true;
                cout << "Login Successful!" << endl;
                cout << "Products listed by you:\n";
                vector<Product> sellerProducts;
                for (const auto& product : products) {
                    if (product.sellerPhoneNumber == seller.phoneNumber) {
                        sellerProducts.push_back(product);
                    }
                }
                displayProductTable(sellerProducts);
                //posting new product
                cout << "\nDo you want to post a new product? (yes/no): ";
                string postProductOption;
                cin >> postProductOption;

                if (postProductOption == "yes") {
                    Product newProduct;
                    cout << "Enter Product Name: ";
                    cin.ignore();
                    getline(cin, newProduct.name);
                    cout << "Enter Price: ";
                    cin >> newProduct.price;
                    cout << "Enter Type: ";
                    cin.ignore();
                    getline(cin, newProduct.type);
                    cout << "Enter Total Number: ";
                    cin >> newProduct.totalNumber;
                    newProduct.sellerPhoneNumber = seller.phoneNumber;

                    products.push_back(newProduct);
                    saveProductData(products);

                    cout << "Product posted successfully!" << endl;
                } else {
                    cout << "Product posting cancelled." << endl;
                }
                
                break;
            }
        }

        if (!found) {
            cout << "Invalid Account Number or Password. Please try again." << endl;
            goto preloader;
        }
    } else {
        cout << "Invalid option. Please choose again." << endl;
        goto preloader;
    }
// is it done?
}

void searchUserByAccountName() {
    string searchName;
    cout << "Enter the account name you want to search for: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;

    // Search in buyers
    for (const auto& buyer : buyers) {
        if (buyer.name == searchName) {
            cout << "User found in Buyers:\n";
            cout << "Account Number: " << buyer.accountNumber << endl;
            cout << "Name: " << buyer.name << endl;
            cout << "Password: " << buyer.password << endl;
            cout << "Money Deposit: " << buyer.moneyDeposit << endl;
            cout << "Phone Number: " << buyer.phoneNumber << endl;
            cout << "Email Address: " << buyer.emailAddress << endl;
            found = true;
        }
    }

    // Search in sellers
    for (const auto& seller : sellers) {
        if (seller.name == searchName) {
            cout << "User found in Sellers:\n";
            cout << "Account Number: " << seller.accountNumber << endl;
            cout << "Name: " << seller.name << endl;
            cout << "Password: " << seller.password << endl;
            cout << "Money Deposit: " << seller.moneyDeposit << endl;
            cout << "Phone Number: " << seller.phoneNumber << endl;
            cout << "Email Address: " << seller.emailAddress << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "User not found." << endl;
    }
}


void adminService() {
    failed:
    cout << "\nAdmin Service:\n"
         << "Enter Admin Account Number: ";
    
    int accountNumber;
    string password;
    cin >> accountNumber;
    cout << "Enter Password: ";
    cin.ignore();
    getline(cin, password);

    if (accountNumber == 0000 && password == "password") {
        cout << "Login Successful!" << endl;

        while (true) {
            failedOption:
            cout << "\nAdmin Service:\n"
         << "1. Open Buyers File\n"
         << "2. Open Sellers File\n"
         << "3. Open Products File\n"
         << "4. Search User by Account Name\n"
         << "5. Exit\n"
         << "Choose an option: ";

            int option;
            cin >> option;
            switch (option) {
                case 1:
                    displayBuyerTable(buyers);
                    break;
                case 2:
                    displaySellerTable(sellers);
                    break;
                case 3:
                    displayProductTable(products);
                    break;
                case 4:
                    searchUserByAccountName();
                    break;
                case 5:
                    cout << "Exiting Admin Service..." << endl;
                    return;
                default:
                    cout << "Invalid option. Please choose again." << endl;
                    goto failedOption;
            }
        }
    } else {
        cout << "Invalid Account Number or Password. Admin login failed." << endl;
        goto failed;
    }

}

void openTermsAndConditions() {
    system("cls");
    ifstream inFile("term.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open Terms and Conditions file." << endl;
    }
}

void openHowToUse() {
    system("cls");
    ifstream inFile("help.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open How to Use file." << endl;
    }
}

void aboutCompany() {
    system("cls");
    cout << "About L Digital Market:\n L Digital Market is a visionary technology company committed to transforming the digital landscape. We specialize in providing cutting-edge solutions and services that propel businesses and individuals into the future. With a strong focus on connecting the buyer with seller and strive to meet and exceed the evolving demands of the digital market.Founded in 2015, the company started as a humble tech startup, offering digital market platform for businesses. As the digital world continues to evolve, L Digital Market remains committed to pioneering tomorrow's technologies today, always aiming to create a brighter, smarter, and more connected future for all.\n L Digital Market, Copyright © 2015." << endl;
}

void saveBuyerData(const vector<Buyer>& buyers) {
    ofstream outFile("Bfile.txt");
    if (outFile.is_open()) {
        for (const auto& buyer : buyers) {
            outFile << buyer.accountNumber << ',' << buyer.name << ',' << buyer.password << ','
                    << buyer.moneyDeposit << ',' << buyer.phoneNumber << ',' << buyer.emailAddress << '\n';
        }
        outFile.close();
    } else {
        cerr << "Error: Unable to save buyer data to file." << endl;
    }
}

void saveSellerData(const vector<Seller>& sellers) {
    ofstream outFile("Sfile.txt");
    if (outFile.is_open()) {
        for (const auto& seller : sellers) {
            outFile << seller.accountNumber << ',' << seller.name << ',' << seller.password << ','
                    << seller.moneyDeposit << ',' << seller.phoneNumber << ',' << seller.emailAddress << '\n';
        }
        outFile.close();
        cout << "Seller data saved successfully." << endl;
    } else {
        cerr << "Error: Unable to save seller data to file." << endl;
    }
}

void saveProductData(const vector<Product>& products) {
    ofstream outFile("product.txt");
    if (outFile.is_open()) {
        for (const auto& product : products) {
            outFile << product.name << ',' << product.price << ',' << product.type << ','
                    << product.totalNumber << ',' << product.sellerPhoneNumber << '\n';
        }
        outFile.close();
        cout << "Product data saved successfully." << endl;
    } else {
        cerr << "Error: Unable to save product data to file." << endl;
    }
}

vector<Buyer> loadBuyerData() {
    vector<Buyer> buyers;
    ifstream inFile("Bfile.txt");
    if (inFile.is_open()) {
        Buyer buyer;
        char comma;
        while (inFile >> buyer.accountNumber >> comma) {
            getline(inFile, buyer.name, ',');
            getline(inFile, buyer.password, ',');
            inFile >> buyer.moneyDeposit >> comma;
            getline(inFile, buyer.phoneNumber, ',');
            getline(inFile, buyer.emailAddress);
            buyers.push_back(buyer);
        }
        inFile.close();
    } else {
        cerr << "Error: Unable to load buyer data from file." << endl;
    }
    return buyers;
}

vector<Seller> loadSellerData() {
    vector<Seller> sellers;
    ifstream inFile("Sfile.txt");
    if (inFile.is_open()) {
        Seller seller;
        char comma;
        while (inFile >> seller.accountNumber >> comma) {
            getline(inFile, seller.name, ',');
            getline(inFile, seller.password, ',');
            inFile >> seller.moneyDeposit >> comma;
            getline(inFile, seller.phoneNumber, ',');
            getline(inFile, seller.emailAddress);
            sellers.push_back(seller);
        }
        inFile.close();
    } else {
        cerr << "Error: Unable to load seller data from file." << endl;
    }
    return sellers;
}

// Function to load product data from the "product.txt" file
vector<Product> loadProductData() {
    vector<Product> products;
    ifstream inFile("product.txt");

    if (!inFile) {
        cout << "Error: Unable to open product.txt file." << endl;
        return products; // Return an empty vector if the file cannot be opened
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        Product product;

        // Assuming each line in the file follows the format: Name,Price,Type,TotalNumber,SellerPhoneNumber
        if (getline(iss, product.name, ',') &&
            (iss >> product.price) && (iss.ignore(), getline(iss, product.type, ',')) &&
            (iss >> product.totalNumber) && (iss.ignore(), getline(iss, product.sellerPhoneNumber))) {

            products.push_back(product);
        } else {
            cout << "Error: Invalid product data in the file." << endl;
        }
    }

    inFile.close();
    return products;
}

//display product
void displayProductTable(const vector<Product>& products) {
    cout << "Product Table:" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "No.  | Product Name | Price | Type   | Quantity | Seller Phone" << endl;
    cout << "----------------------------------------------" << endl;

    for (size_t i = 0; i < products.size(); ++i) {
        const Product& product = products[i];
        cout << setw(4) << i + 1 << "  | " << setw(12) << product.name << " | " << setw(5) << product.price << " | "
             << setw(6) << product.type << " | " << setw(8) << product.totalNumber << "  | " << product.sellerPhoneNumber
             << endl;
    }

    cout << "----------------------------------------------" << endl;
}

void buyProduct(vector<Product>& products, vector<Buyer>& buyers) {
    int accountNumber;
    cout << "Enter your Account Number: ";
    cin >> accountNumber;

    int buyerIndex = findBuyerIndex(accountNumber);

    if (buyerIndex != -1) {
        // Buyer with the given account number is found
        validNum:
        int productIndex;
        int quantity;
        cout << "Enter the product number you want to buy: ";
        cin >> productIndex;

        if (productIndex >= 1 && productIndex <= int(products.size())) {
            productIndex--; // Adjust for zero-based indexing
            quanta:
            cout << "Enter the quantity you want to buy: ";
            cin >> quantity;

            Product& selectedProduct = products[productIndex];
            if (quantity <= selectedProduct.totalNumber) {
                double totalPrice = quantity * selectedProduct.price;

                Buyer& loggedInBuyer = buyers[buyerIndex];

                // Update product quantity and buyer's money deposit
                selectedProduct.totalNumber -= quantity;
                loggedInBuyer.moneyDeposit -= totalPrice;

                // Update seller's money deposit
                for (Seller& seller : sellers) {
                    if (seller.phoneNumber == selectedProduct.sellerPhoneNumber) {
                        seller.moneyDeposit += totalPrice;
                        break;
                    }
                }

                // Save the updated data to files
                saveProductData(products);
                saveBuyerData(buyers);
                saveSellerData(sellers);

                cout << "Purchase successful. Total price: $" << totalPrice << endl;
            } else {
                cout << "Insufficient quantity. Please choose a smaller quantity." << endl;
		goto quanta;
            }
        } else {
            cout << "Invalid product number. Please choose a valid product number." << endl;
	    goto validNum;
        }
    } else {
        cout << "Buyer with the given account number not found." << endl;
        exit(7);
    }
}


int findBuyerIndex(int accountNumber){
    for (size_t i = 0; i < buyers.size(); ++i){
        if (buyers[i].accountNumber == accountNumber){
            return i;
        }
    }
    return -1;
}
//display buyers table
void displayBuyerTable(const vector<Buyer>& buyers) {
    cout << "Buyer Table:" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "No.  | Account No. | Name         | Money Deposit | Phone         | Email" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (size_t i = 0; i < buyers.size(); ++i) {
        const Buyer& buyer = buyers[i];
        cout << setw(4) << i + 1 << "  | " << setw(12) << buyer.accountNumber << " | " << setw(12) << buyer.name << " | "
             << setw(13) << buyer.moneyDeposit << " | " << setw(12) << buyer.phoneNumber << " | " << buyer.emailAddress
             << endl;
    }

    cout << "-----------------------------------------------------" << endl;
}
//display sellers table
void displaySellerTable(const vector<Seller>& sellers) {
    cout << "Seller Table:" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "No.  | Account No. | Name         | Money Deposit | Phone         | Email" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (size_t i = 0; i < sellers.size(); ++i) {
        const Seller& seller = sellers[i];
        cout << setw(4) << i + 1 << "  | " << setw(12) << seller.accountNumber << " | " << setw(12) << seller.name << " | "
             << setw(13) << seller.moneyDeposit << " | " << setw(12) << seller.phoneNumber << " | " << seller.emailAddress
             << endl;
    }

    cout << "-----------------------------------------------------" << endl;
}
