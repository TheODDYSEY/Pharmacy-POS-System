# Pharmacy Management System 

## Introduction
This project is a Pharmacy Management System implemented in C++. The system provides functionalities for both clients and administrators. Clients can view available products, add products to the cart, remove products from the cart, view products in the cart, and checkout. Administrators, on the other hand, can add, remove, and update products in the inventory, view all products, save inventory to a file, load inventory from a file, and view the daily sales table.

## Setup and Compilation
To run the Pharmacy Management System, you will need a C++ compiler such as g++ on Linux or MinGW on Windows. Follow the steps below:

1. Save the provided code in a file, for example, `pharmacy_management.cpp`.

2. Open a terminal or command prompt and navigate to the directory containing the code file.

3. Compile the code using the C++ compiler. For example, on Linux:
   ```
   g++ -o pharmacy_management pharmacy_management.cpp
   ```

4. After successful compilation, run the executable:
   ```
   ./pharmacy_management
   ```

## Usage

Upon running the program, you will be prompted to enter whether you are a client or an admin. To interact with the system, follow the instructions provided by the program.

### For Clients:
1. Enter your username and password.
2. You will then be presented with a menu:
   ```
   Please choose an option:
   1. View available products
   2. Add a product to the cart
   3. Remove a product from the cart
   4. View products in the cart
   5. Checkout
   Q. Quit
   ```
3. Select the desired option by entering the corresponding number or 'Q' to quit.
4. If you select option 1, the available products will be displayed, and you can add products to your cart using option 2. You can also remove products from the cart (option 3), view products in the cart (option 4), and proceed to checkout (option 5).
5. After the checkout, a receipt will be generated, and the daily sales table will be updated.

### For Admins:
1. Enter your admin username and password.
2. You will then be presented with an admin menu:
   ```
   Please choose an option:
   1. Add a product
   2. Remove a product
   3. Update a product
   4. View all products
   5. Save inventory to file
   6. Load inventory from file
   7. View daily sales table
   Q. Quit
   ```
3. Select the desired option by entering the corresponding number or 'Q' to quit.
4. If you select option 1, you can add a new product to the inventory by providing its details. Option 2 allows you to remove a product from the inventory by providing its ID. Option 3 lets you update a product's details. Option 4 displays all products in the inventory, and option 5 allows you to save the inventory to a file. Option 6 lets you load the inventory from a file. Option 7 displays the daily sales table.

## Important Note
- The provided code does not include the implementation of the `Client` and `Admin` classes' methods, so make sure to add them based on your requirements.
- The implementation assumes the existence of a `SalesTable` class for tracking daily sales.
- The `Inventory` class handles the management of products and their operations.
- Ensure `recordone` or `inventory.txt` are in same directory as main cpp file to be able to load inventory items.
  
## Conclusion
The Pharmacy Management System allows clients to purchase products and administrators to manage the inventory efficiently.
