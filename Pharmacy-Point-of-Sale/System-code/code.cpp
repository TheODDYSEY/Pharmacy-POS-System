#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

string getCurrentDate() {
    time_t now = time(0);
    tm* currentTime = localtime(&now);

    // Format the date as YYYY-MM-DD
    stringstream ss;
    ss << setw(4) << setfill('0') << currentTime->tm_year + 1900 << "-";
    ss << setw(2) << setfill('0') << currentTime->tm_mon + 1 << "-";
    ss << setw(2) << setfill('0') << currentTime->tm_mday;

    return ss.str();
}

class Product {
    private:
        int id;
        string name;
        string category;
        double price;
        int quantity;

    public:
        Product(int id, string name, string category, double price, int quantity) {
            this->id = id;
            this->name = name;
            this->category = category;
            this->price = price;
            this->quantity = quantity;
        }

        int getId() const {
            return id;
        }

        void setId(int id) {
            this->id = id;
        }

        string getName() const {
            return name;
        }

        void setName(string name) {
            this->name = name;
        }

        string getCategory() const {
            return category;
        }

        void setCategory(string category) {
            this->category = category;
        }

        double getPrice() const {
            return price;
        }

        void setPrice(double price) {
            this->price = price;
        }

        int getQuantity() const {
            return quantity;
        }

        void setQuantity(int quantity) {
            this->quantity = quantity;
        }
};

class Inventory {
    private:
        vector<Product> products;

    public:
        void addProduct(Product product) {
            bool found = false;
            for (auto& p : products) {
                if (p.getId() == product.getId()) {
                    cout << "Id already Exists." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                products.push_back(product);
            //     cout << "Product added successfully." << endl;
            //     cout << "-----------------------------------------------------------" << endl;
            }
        }

        void removeProduct(int id) {
            bool found = false;
            for (auto i = products.begin(); i != products.end(); i++) {
                if (i->getId() == id) {
                    products.erase(i);
                    found = true;
                    cout << "Product removed successfully." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                    break;
                }
            }
            if (!found) {
                cout << "Id does not exist." << endl;
            }
        }

        Product* findProduct(int id) {
            for (auto i = products.begin(); i != products.end(); i++) {
                if (i->getId() == id) {
                    return &(*i);
                }
            }
            return nullptr;
        }

        void updateProduct(int id, string name, string category, double price, int quantity) {
            bool found = false;
            for (auto i = products.begin(); i != products.end(); i++) {
                if (i->getId() == id) {
                    i->setName(name);
                    i->setCategory(category);
                    i->setPrice(price);
                    i->setQuantity(quantity);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "ID does not exist." << endl;
            }
        }

        void printProduct() const {
            if (products.empty()) {
                cout << "No products available." << endl;
                cout << "-----------------------------------------------------------" << endl;
                return;
            }

            cout << "-----------------------------------------------------------" << endl;
            cout << "| ID   | Name             | Category         | Price    | Quantity |" << endl;
            cout << "-----------------------------------------------------------" << endl;

            for (const auto& product : products) {
                cout << "| " << setw(4) << product.getId() << " | ";
                cout << setw(16) << product.getName() << " | ";
                cout << setw(16) << product.getCategory() << " | ";
                cout << setw(8) << fixed << setprecision(2) << product.getPrice() << " | ";
                cout << setw(8) << product.getQuantity() << " |" << endl;
            }

            cout << "-----------------------------------------------------------" << endl;
        }

        void saveInventoryToFile(const string& filename) {
            // Append ".txt" extension to the filename
            string fullFilename = filename + ".txt";

            ofstream file;
            file.open(fullFilename);
            if (file.is_open()) {
                for (const auto& product : products) {
                    file << product.getId() << "," << product.getName() << "," << product.getCategory() << "," << product.getPrice() << "," << product.getQuantity() << endl;
                }
                file.close();
                cout << "Inventory saved to " << fullFilename << " successfully." << endl;
                cout << "-----------------------------------------------------------" << endl;
            } else {
                cout << "Error: Could not open file " << fullFilename << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
        }
    void loadInventoryFromFile(const string& filename) {
        // Clear existing products
        products.clear();
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string idStr, name, category, priceStr, quantityStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, category, ',');
                getline(ss, priceStr, ',');
                getline(ss, quantityStr, ',');
                int id = stoi(idStr);
                double price = stod(priceStr);
                int quantity = stoi(quantityStr);
                Product p(id, name, category, price, quantity);
                products.push_back(p);
            }
            file.close();
        } else {
            cout << "Error: Could not open file " << filename << endl;
        }
    }

        const vector<Product>& getProducts() const{
            return products;
        }
};

class User {
    protected:
        string username;
        string password;

    public:
        User(string username, string password) : username(username), password(password) {}

        bool login(string username, string password) {
            return (this->username == username && this->password == password);
        }
};

class Client : public User {
    private:
        string name;
        string address;
        vector<Product> clientCart;

    public:
        Client(string username, string password, string name, string address)
            : User(username, password), name(name), address(address) {}


    void printReceipt(double totalPrice) {
        cout << "===========================================================" << endl;
        cout << "                      Pharmatrix 2000                      " << endl;
        cout << "                 ** Your Ultimate Pharmacy **              " << endl;
        cout << "===========================================================" << endl;
        cout << "Receipt Date: " << getCurrentDate() << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Client Name: " << name << endl;
        cout << "Client Address: " << address << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "                     Receipt Details                        " << endl;
        cout << "-----------------------------------------------------------" << endl;

        // Print individual items in the cart with details
        for (const auto& product : clientCart) {
            cout << setw(20) << left << product.getName() << setw(10) << right << fixed << setprecision(2) << "$ " << product.getPrice() << endl;
        }

        cout << "-----------------------------------------------------------" << endl;
        cout << "Total Price: " << setw(27) << right << fixed << setprecision(2) << "$ " << totalPrice << endl;
        cout << "Payment Details:" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Payment Method: Credit Card" << endl;
        cout << "Card Type: Visa" << endl;
        cout << "Card Number: **** **** **** 1234" << endl;
        cout << "Expiry Date: 12/25" << endl;
        cout << "Cardholder Name : "<<name<< endl;
        cout << "---------------------------------------" << endl;

    }
};

class Admin : public User {
    public:
        Admin(string username, string password) : User(username, password) {}
};

class SalesTable {
    private:
        struct DailySale {
            string date;
            double totalSales;

            DailySale(string date, double totalSales) : date(date), totalSales(totalSales) {}
        };

        vector<DailySale> sales;

    public:
        void addSale(string date, double totalSales) {
            DailySale sale(date, totalSales);
            sales.push_back(sale);
        }

        void printSales() const {
            cout << "Daily Sales Table:" << endl;
            for (const auto& sale : sales) {
                cout << "Date: " << sale.date << ", Total Sales: $ " << sale.totalSales << endl;
            }
        }
};

int main() {
    Inventory inventory;
    SalesTable salesTable;

    cout << "===========================================================" << endl;
    cout << "                    Pharmatrix 2000                        " << endl;
    cout << "           ** Your Ultimate Pharmacy Solution **           " << endl;
    cout << "===========================================================" << endl;
    cout << "          Welcome to the Future of Pharmacy Management      " << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;

    char userType;
    cout << "Are you a client or an admin? (C/A): ";
    cin >> userType;

    // Rest of the code for the main function continues here...


    if (userType == 'C' || userType == 'c') {
        string username, password, name, address;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your address: ";
        getline(cin, address);

        Client client(username, password, name, address);

        if (!client.login(username, password)) {
            cout << "Invalid credentials. Exiting..." << endl;
            return 0;
        }

        cout << "-----------------------------------------------------------" <<endl;
        cout << "Welcome, " << name << "!" << endl;

        Inventory clientInventory;
    // Assuming you have already declared and initialized the clientInventory object

// Adding the products to the clientInventory using the provided format
        clientInventory.addProduct(Product(1, "Paracetamol", "Painkiller", 100, 12));
        clientInventory.addProduct(Product(2, "Ibuprofen", "Painkiller", 75, 8));
        clientInventory.addProduct(Product(3, "Aspirin", "Painkiller", 50, 10));
        clientInventory.addProduct(Product(4, "Morphine", "Painkiller", 25, 5));
        clientInventory.addProduct(Product(5, "Codeine", "Painkiller", 60, 7));
        clientInventory.addProduct(Product(6, "Oxycodone", "Painkiller", 40, 3));
        clientInventory.addProduct(Product(7, "Tramadol", "Painkiller", 80, 9));
        clientInventory.addProduct(Product(8, "Naproxen", "Painkiller", 65, 11));
        clientInventory.addProduct(Product(9, "Acetaminophen", "Painkiller", 90, 6));
        clientInventory.addProduct(Product(10, "Diclofenac", "Painkiller", 70, 4));
        clientInventory.addProduct(Product(11, "Amoxicillin", "Antibiotic", 110, 15));
        clientInventory.addProduct(Product(12, "Azithromycin", "Antibiotic", 95, 19));
        clientInventory.addProduct(Product(13, "Cefuroxime", "Antibiotic", 120, 16));
        clientInventory.addProduct(Product(14, "Clindamycin", "Antibiotic", 85, 13));
        clientInventory.addProduct(Product(15, "Ciprofloxacin", "Antibiotic", 105, 14));
        clientInventory.addProduct(Product(16, "Doxycycline", "Antibiotic", 100, 18));
        clientInventory.addProduct(Product(17, "Erythromycin", "Antibiotic", 80, 17));
        clientInventory.addProduct(Product(18, "Levofloxacin", "Antibiotic", 90, 20));
        clientInventory.addProduct(Product(19, "Linezolid", "Antibiotic", 75, 22));
        clientInventory.addProduct(Product(20, "Metronidazole", "Antibiotic", 65, 23));
        clientInventory.addProduct(Product(21, "Penicillin", "Antibiotic", 55, 21));
        clientInventory.addProduct(Product(22, "Rifampicin", "Antibiotic", 50, 24));
        clientInventory.addProduct(Product(23, "Sulfamethoxazole", "Antibiotic", 70, 25));
        clientInventory.addProduct(Product(24, "Tetracycline", "Antibiotic", 45, 26));
        clientInventory.addProduct(Product(25, "Fluoxetine", "Antidepressant", 80, 7));
        clientInventory.addProduct(Product(26, "Escitalopram", "Antidepressant", 65, 5));
        clientInventory.addProduct(Product(27, "Sertraline", "Antidepressant", 90, 9));
        clientInventory.addProduct(Product(28, "Paroxetine", "Antidepressant", 75, 6));
        clientInventory.addProduct(Product(29, "Citalopram", "Antidepressant", 60, 8));
        clientInventory.addProduct(Product(30, "Amitriptyline", "Antidepressant", 50, 4));
        clientInventory.addProduct(Product(31, "Clomipramine", "Antidepressant", 55, 3));
        clientInventory.addProduct(Product(32, "Fluvoxamine", "Antidepressant", 70, 2));
        clientInventory.addProduct(Product(33, "Imipramine", "Antidepressant", 45, 1));
        clientInventory.addProduct(Product(34, "Duloxetine", "Antidepressant", 85, 10));
        clientInventory.addProduct(Product(35, "Mirtazapine", "Antidepressant", 95, 11));
        clientInventory.addProduct(Product(36, "Bupropion", "Antidepressant", 80, 12));
        clientInventory.addProduct(Product(37, "Venlafaxine", "Antidepressant", 65, 13));
        clientInventory.addProduct(Product(38, "Desvenlafaxine", "Antidepressant", 75, 14));
        clientInventory.addProduct(Product(39, "Trazodone", "Antidepressant", 70, 15));
        clientInventory.addProduct(Product(40, "Maprotiline", "Antidepressant", 50, 16));


        vector<Product> clientCart;

        char choice;
        do {
            cout << "Please choose an option:" << endl;
            cout << "1. View available products" << endl;  // Option to view available products
            cout << "2. Add a product to the cart" << endl;
            cout << "3. Remove a product from the cart" << endl;
            cout << "4. View products in the cart" << endl;
            cout << "5. Checkout" << endl;
            cout << "Q. Quit" << endl;
            cin >> choice;

 switch (choice) {
                    case '1': {
                    // View available products in client's inventory (clientInventory)
                    cout << "-----------------------------------------------------------" << endl;
                    cout << "| ID   | Name             | Category         | Price    | Quantity |" << endl;
                    cout << "-----------------------------------------------------------" << endl;

                    for (const auto& product : clientInventory.getProducts()) {
                        cout << "| " << setw(4) << product.getId() << " | ";
                        cout << setw(16) << product.getName() << " | ";
                        cout << setw(16) << product.getCategory() << " | ";
                        cout << setw(8) << fixed << setprecision(2) << product.getPrice() << " | ";
                        cout << setw(8) << product.getQuantity() << " |" << endl;
                    }

                    cout << "-----------------------------------------------------------" << endl;
                    break;
                }
                            case '2': {
                    // Add a product to the cart
                    int id;
                    cout << "Enter product id: ";
                    cin >> id;

                    // Find the product in the inventory based on the entered ID
                    Product* product = clientInventory.findProduct(id);
                    if (product) {
                        // Add the product to the client's cart
                        clientCart.push_back(*product);
                        cout << "Product added to cart." << endl;
                        cout << "-----------------------------------------------------------" << endl;
                    } else {
                        cout << "Product not found." << endl;
                        cout << "-----------------------------------------------------------" << endl;
                    }
                    break;
                }


                case '3': {
                    // Remove a product from the cart
                    int id;
                    cout << "Enter product id: ";
                    cin >> id;
                    // Remove product from cart
                    // ...
                    cout << "Product removed from cart." << endl;
                    cout << "-----------------------------------------------------------" <<endl;
                    break;
                }
                case '4': {
                    // View products in cart
                    if (clientCart.empty()) {
                        cout << "No products in the cart." << endl;
                    } else {
                            cout << "===================================================================" << endl;
                            cout << "                             Cart Summary                           " << endl;
                            cout << "===================================================================" << endl;
                            cout << "| ID   | Name             | Category         | Price    | Quantity |" << endl;
                            cout << "===================================================================" << endl;
                        for (const auto& product : clientCart) {
                            cout << "| " << setw(4) << product.getId() << " | ";
                            cout << setw(16) << product.getName() << " | ";
                            cout << setw(16) << product.getCategory() << " | ";
                            cout << setw(8) << fixed << setprecision(2) << product.getPrice() << " | ";
                            cout << setw(8) << product.getQuantity() << " |" << endl;
                        }
                        cout << "-----------------------------------------------------------" << endl;
                    }
                    break;
                }
            case '5': {
                    // Checkout
                    double totalPrice = 0.0;

                    // Calculate the total price based on the products in the cart
                    for (const auto& product : clientCart) {
                        totalPrice += product.getPrice();
                    }

                    // Print receipt
                    client.printReceipt(totalPrice);

                    // Update sales table
                    salesTable.addSale(getCurrentDate(), totalPrice);
                    cout << "Checkout successful." << endl;
                    cout << "-----------------------------------------------------------" << endl;

                    // Clear the cart after checkout
                    clientCart.clear();

                    break;
                }



                case 'q':
                case 'Q':
                    cout << "Goodbye, "<<name << "!"<< endl;
                    cout << "-----------------------------------------------------------" <<endl;
                    return 0;

                default:
                    cout << "Invalid Choice. Please Try again" << endl;
                    cout << "-----------------------------------------------------------" <<endl;
                    break;
            }
        } while (true);
    } else if (userType == 'A' || userType == 'a') {
        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        Admin admin(username, password);

        if (!admin.login(username, password)) {
            cout << "Invalid credentials. Exiting..." << endl;
            return 0;
        }

        cout << "-----------------------------------------------------------" <<endl;
        cout << "Welcome, Admin!" << endl;

        char choice;
        do {
            cout << "Please choose an option:" << endl;
            cout << "1. Add a product" << endl;
            cout << "2. Remove a product" << endl;
            cout << "3. Update a product" << endl;
            cout << "4. View all products" << endl;
            cout << "5. Save inventory to file" << endl;
            cout << "6. Load inventory from file" << endl;
            cout << "7. View daily sales table" <<endl;
            cout << "Q. Quit" << endl;
            cin >> choice;

            switch (choice) {
                case '1': {
                    int id, quantity;
                    string name, category;
                    double price;
                    cout << "Enter product id: ";
                    cin >> id;
                    cout << "Enter product name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter product category: ";
                    getline(cin, category);
                    cout << "Enter product price: $ ";
                    cin >> price;
                    cout << "Enter product quantity: ";
                    cin >> quantity;
                    Product product(id, name, category, price, quantity);
                    inventory.addProduct(product);
                    break;
                }

                case '2': {
                    int id;
                    cout << "Enter product id: ";
                    cin >> id;
                    inventory.removeProduct(id);
                    break;
                }

                case '3': {
                    int id, quantity;
                    string name, category;
                    double price;
                    cout << "Enter product id: ";
                    cin >> id;
                    cout << "Enter updated product name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter updated product category: ";
                    getline(cin, category);
                    cout << "Enter updated product price: $ ";
                    cin >> price;
                    cout << "Enter updated product quantity: ";
                    cin >> quantity;
                    inventory.updateProduct(id, name, category, price, quantity);
                    break;
                }

                case '4': {
                    inventory.printProduct();
                    break;
                }

                case '5': {
                    string filename;
                    cout << "Enter filename: ";
                    cin >> filename;
                    inventory.saveInventoryToFile(filename);
                    break;
                }

                case '6': {
                    string filename;
                    cout << "Enter filename: ";
                    cin >> filename;
                    inventory.loadInventoryFromFile("recordone");
                    break;
                }
                case '7':{
                    salesTable.printSales();
                    cout << "-----------------------------------------------------------" <<endl;
                    break;
                }

                case 'q':
                case 'Q':
                    cout << "Goodbye,Admin!" << endl;
                    cout << "-----------------------------------------------------------" <<endl;
                    return 0;

                default:
                    cout << "Invalid Choice. Please Try again" << endl;
                    cout << "-----------------------------------------------------------" <<endl;
                    break;
            }
        } while (true);
    } else {
        cout << "Invalid user type. Exiting..." << endl;
        cout << "-----------------------------------------------------------" <<endl;
    }

    return 0;
}
