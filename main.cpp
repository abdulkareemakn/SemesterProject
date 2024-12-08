/*

CSC103	| Programming Fundamentals
Semester Project

Name		|  Registration No

Ahmad Ali	|  FA24-BSE-012
Abdul Kareem	|  FA24-BSE-123
Ahmad Faisal	|  FA24-BSE-126

// Implemented by Ahmad Faisal
void welcomeScreen(void);
bool authentication(void);
void logReceipt(float bill, int paymentMethod);
void printReceipt(std::string name, int quantity, float price, float bill, int paymentMethod);

// Implemented by Abdul Kareem
void readInventory(Item items[], int size);
void writeInventory(Item items[], int size);
void restockInventory(Item items[], int size);
void displayInventory(Item items[], int size);

// Implemented by Ahmad Ali
void updatePrices(Item items[], int size);
void sellItem(Item items[], int size);
bool isValidCardNumber(long long int n);
void progressReports(Item items[], int size);

*/

#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

const int SIZE = 17;

int transactionCount = 0;

// Struct declared to store information about items
struct Item
{
    std::string name;
    std::string ID;
    int quantity;
    float price;
};

// Function Prototypes
void welcomeScreen(void);

bool authentication(void);

void createInventory(void);
void readInventory(Item items[], int size);
void displayInventory(Item items[], int size);
void writeInventory(Item items[], int size);
void restockInventory(Item items[], int size);

void sellItem(Item items[], int size);
void updateItemPrices(Item items[], int size);

void logReceipt(float bill, int paymentMethod);
void printReceipt(std::string name, int quantity, float price, float bill, int paymentMethod);

void progressReports(Item items[], int size);

bool isValidCardNumber(long long int n);

int main(void)
{
    // An array of structs. The size of the array is according to the number of items in the database.
    Item items[SIZE];

    int choice = 0;

    welcomeScreen();

    if (authentication())
    {
        // createInventory();
        readInventory(items, SIZE);

        while (true)
        {
            std::cout << "1. Display Inventory\n";
            std::cout << "2. Sell Item\n";
            std::cout << "3. Restock Inventory\n";
            std::cout << "4. Update Prices\n";
            std::cout << "5. View Progress Report\n";
            std::cout << "6. Save and Exit\n";

            std::cout << "\nSelect a number to proceed: ";
            std::cin >> choice;
            std::cout << "\n";

            if (choice == 1)
            {
                displayInventory(items, SIZE);
            }
            else if (choice == 2)
            {
                sellItem(items, SIZE);
            }
            else if (choice == 3)
            {
                restockInventory(items, SIZE);
            }
            else if (choice == 4)
            {
                updateItemPrices(items, SIZE);
            }
            else if (choice == 5)
            {
                progressReports(items, SIZE);
            }
            else if (choice == 6)
            {
                writeInventory(items, SIZE);
                return 0;
            }
            else
            {
                std::cout << "Invalid choice!\n";
                std::cout << "Saving and exiting!\n";
                writeInventory(items, SIZE);

                return 0;
            }
        }
    }
    else
        std::cout << "Invalid Credentials!" << std::endl;
}

void welcomeScreen(void)
// This function displays the welcome screen of the program.
{
    std::cout << "\t\t\t\t\t\tA Retail Inventory Management System\n";
    std::cout << "\n\n\n";
    std::cout << "\t\t\t\t\t\t\t\tMade by";
    std::cout << "\n\n\n";
    std::cout << "\t\t\t\t\t\tAhmad Ali\t  |     FA24-BSE-012\n";
    std::cout << "\t\t\t\t\t\tAbdul Kareem\t  |     FA24-BSE-123\n";
    std::cout << "\t\t\t\t\t\tAhmad Faisal\t  |     FA24-BSE-123\n";
    std::cout << "\n\n";
    std::cout << "---------------------------------------------------------------"
                 "---------------------------------------------------------------"
                 "--------";
}

bool authentication(void)
// This function authenticates the user. The default username is "admin" and the default password is "password". The
// password could be hashed to increase security but it was beyond the scope of the program. The function returns true
// if the user is authenticated, otherwise it returns false.
{
    std::string username = "admin";
    std::string password = "password";

    std::string input_username;
    std::string input_password;

    std::cout << "\n\n\n\t\t\t\t\t\t\t\tWelcome\n\n";
    std::cout << "\t\t\t\t\t\t\t\t Login\n";
    std::cout << "\n\n";

    std::cout << "\tUsername: ";
    std::getline(std::cin, input_username);

    std::cout << "\tPassword: ";
    std::getline(std::cin, input_password);
    std::cout << "\n\n";

    if (username == input_username && password == input_password)
        return true;
    else
        return false;
}

void createInventory(void)
{
    std::ofstream database("inventory.csv");

    if (database.is_open())
    {
        // Fruits
        database << "Apples,GR1006,250,0.8\n";
        database << "Strawberries,GR1015,110,3.8\n";
        database << "Grapes (1kg),GR1021,90,2.99\n";
        database << "Pineapple (each),GR1023,60,4.5\n";
        database << "Watermelon (each),GR1024,50,6\n";

        // Dairy
        database << "Milk,DR1002,200,1.20\n";
        database << "Eggs,DR1003,120,2.99\n";
        database << "Salted Butter,DR1005,100,3.00\n";
        database << "Yogurt,DR1009,90,2.20\n";
        database << "Cheddar Cheese (500g),DR1014,85,5\n";
        database << "Fresh Cream (250ml),DR1026,150,2.5\n";
        database << "Mozzarella Cheese (500g),DR1027,70,4.5\n";
        database << "Chocolate Milk (1L),DR1028,80,2.2\n";

        // Bakery
        database << "Brown Bread (Loaf),BR1004,80,1.5\n";
        database << "Croissant (each),BR1030,100,1.2\n";
        database << "Bagel (each),BR1033,200,1\n";
        database << "Chocolate Chip Cookies (6),BR1036,120,2.99\n";
    }
    database.close();
}

void readInventory(Item items[], int size)
// This function reads the inventory database from the file and stores the information in the array of structs. This
// function assumes that there is a database file named "inventory.csv" in the same directory as the program. To create
// the database file, uncomment line 85 to call the createInventory() function which will create the database file.
{
    std::string item;
    std::ifstream inventoryDatabase("inventory.csv");

    if (inventoryDatabase.is_open())
    {
        int i = 0;
        std::string temp;

        while (std::getline(inventoryDatabase, item))
        {
            std::istringstream item_attributes(item);

            std::getline(item_attributes, items[i].name, ',');
            std::getline(item_attributes, items[i].ID, ',');

            std::getline(item_attributes, temp, ',');
            items[i].quantity = std::stoi(temp);

            std::getline(item_attributes, temp, ',');
            items[i].price = std::stof(temp);

            i++;
        }
    }
    inventoryDatabase.close();
}

void displayInventory(Item items[], int size)
// This function displays the inventory on the console.
{
    std::cout << "\n";
    std::cout << std::left << std::setw(30) << "Name" << "| " << std::setw(15) << "ID" << "| " << std::setw(10)
              << "Quantity" << "| " << std::setw(10) << "Price\n\n";

    for (int i = 0; i < size; i++)
    {
        std::cout << std::left << std::setw(30) << items[i].name << "|  " << std::setw(15) << items[i].ID << "|  "
                  << std::setw(10) << items[i].quantity << "|  " << std::setw(10) << std::fixed << std::setprecision(2)
                  << items[i].price << "\n";
    }

    std::cout << "\n\n";
}

void writeInventory(Item items[], int size)
// This function writes the inventory database to the file. The function writes the information from the array of
// structs to the file.
{
    std::ofstream inventoryDatabase("inventory.csv");

    for (int i = 0; i < size; i++)
    {
        inventoryDatabase << items[i].name << "," << items[i].ID << "," << items[i].quantity << "," << items[i].price;

        if (i != size - 1)
        {
            inventoryDatabase << "\n";
        }
    }

    inventoryDatabase.close();
}

void restockInventory(Item items[], int size)
// This function allows the user to restock the inventory. The user is prompted to enter the item ID and the quantity to
// restock. The function then updates the quantity of the item in the inventory.
{
    displayInventory(items, size);
    std::string ID;
    int quantity;

    std::cout << "\n";
    std::cout << "Specify the item ID for restocking: ";
    std::cin.ignore();
    std::getline(std::cin, ID);

    for (int i = 0; i < size; i++)
    {
        if (ID == items[i].ID)
        {
            std::cout << "How many items do you want to restock? ";
            std::cin >> quantity;

            items[i].quantity += quantity;

            std::cout << "Stock updated successfully!\n\n";
            break;
        }
        if (i == size - 1)
        {
            std::cout << "Invalid ID! Restock Failed!\n\n";
            return;
        }
    }
}

void sellItem(Item items[], int size)
{
    std::string id;
    int quantity;
    int paymentMethod;
    float cash;
    float bill;
    float change;

    std::cout << std::left << std::setw(10) << "Name\t\t|  ID\t\t|  Price\n\n";

    for (int i = 0; i < size; i++)
    {
        std::cout << std::left << std::setw(10) << items[i].name << "\t|  " << items[i].ID << "\t|  $" << items[i].price
                  << "\n";
    }

    std::cout << "\nWhich item would you like to sell? \n";
    std::cout << "Item ID: ";
    std::cin.ignore();
    std::getline(std::cin, id);

    // show quantity
    for (int i = 0; i < size; i++)
    {
        if (id == items[i].ID)
        {
            std::cout << "\nStock on hand: " << items[i].quantity << "\n";

            std::cout << "Number of units to sell: ";
            std::cin >> quantity;

            if (quantity > items[i].quantity)
            {
                std::cout << "\nInvalid! Not enough stock available to fulfill this request.\n\n";
                return;
            }

            bill = quantity * items[i].price;
            std::cout << "\nTotal Amount: $" << bill << "\n";

            for (int i = 1; i <= 3; i++)
            {
                std::cout << "\nSelect your preferred payment method.\n";
                std::cout << "1. Credit\n";
                std::cout << "2. Cash\n";
                std::cout << "Payment Method: ";
                std::cin >> paymentMethod;

                if (paymentMethod == 1)
                {
                    long long int cardNumber;

                    std::cout << "\nCard Number: ";
                    std::cin >> cardNumber;

                    if (!isValidCardNumber(cardNumber))
                    {
                        std::cout << "Invalid Card Number! Transaction failed!\n\n";
                        continue;
                    }
                    break;
                }
                else if (paymentMethod == 2)
                {
                    std::cout << "\nCash Amount: $";
                    std::cin >> cash;
                    if (cash < bill)
                    {
                        std::cout << "Insufficient Cash! Tranaction failed!\n\n";
                        continue;
                    }
                    change = cash - bill;
                    std::cout << "\nChange owed: $" << change << "\n";

                    break;
                }
                else
                {
                    std::cout << "Invalid Payment method! Transaction failed!\n\n";
                    if (i == 3)
                        return;
                }
            }

            logReceipt(bill, paymentMethod);

            printReceipt(items[i].name, quantity, items[i].price, bill, paymentMethod);

            items[i].quantity -= quantity;
            std::cout << "\nTransaction successful!\n\n";

            transactionCount++;
            break;
        }
        else
        {
            if (i == size - 1)
            {
                std::cout << "Invalid Product ID! Transaction failed!\n\n";
                return;
            }
        }
    }
}

void updateItemPrices(Item items[], int size)
// This function allows the user to update the prices of the items in the inventory. The user is prompted to enter the
// item ID and the new price. The function then updates the price of the item in the inventory.
{
    displayInventory(items, size);
    std::string ID;
    float price;

    std::cout << "Specify the item ID for price update: ";
    std::cin.ignore();
    std::getline(std::cin, ID);

    for (int i = 0; i < size; i++)
    {
        if (ID == items[i].ID)
        {
            std::cout << "What is the updated price? ";
            std::cin >> price;

            if (price <= 0)
            {
                std::cout << "Invalid Amount! Price update failed!\n\n";
            }
            items[i].price = price;
            std::cout << "Price has been updated successfully!\n\n";
            break;
        }
        if (i == size - 1)
        {
            std::cout << "Invalid ID! Price update failed!\n\n";
            return;
        }
    }
}

void logReceipt(float bill, int paymentMethod)
// This function logs the transaction details mainly the bill and the payment method to the receipts database file. This
// allows the program to keep track of the transactions made.
{
    std::ofstream receiptsDatabase("receipts.csv", std::ios::app);
    receiptsDatabase << bill << "," << paymentMethod << "\n";

    receiptsDatabase.close();
}

void printReceipt(std::string name, int quantity, float price, float bill, int paymentMethod)
// This function prints the receipt of the transaction.
{
    std::cout << "\nTransaction Processing. Press any character to print "
                 "receipt.";
    std::cin.ignore();
    std::getchar();
    std::cout << "\n\n";

    std::cout << "+========================================+\n";
    std::cout << "|                 Receipt                |\n";
    std::cout << "+========================================+\n";

    std::cout << "\n";

    std::cout << "------------------------------------------\n";
    std::cout << "            Items Purchased               \n";
    std::cout << "------------------------------------------\n";

    std::cout << "\n";

    std::cout << "| Item Name\t\t| Qty | Price    |\n";
    std::cout << "------------------------------------------\n";
    std::cout << std::left << std::setw(10) << name << "\t\t| " << std::right << quantity << "  | $" << price << "   |"
              << "\n";

    std::cout << "\n\n";

    std::cout << "Total Amount: \t\t$" << bill;
    std::cout << "\n\n\n";

    if (paymentMethod == 1)
    {
        std::cout << "Payment Method: \t" << "Credit";
    }
    else
    {
        std::cout << "Payment Method: \t" << "Cash";
    }

    std::cout << "\n\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "Thank you for your purchase!\n\n";
}

void progressReports(Item items[], int size)
// This function displays the progress reports of the transactions made. The function displays the total number of
// transactions, the total revenue, and the number of transactions made with cash and credit.
{
    std::string lines;
    float total = 0;
    int cash = 0;
    int credit = 0;
    std::string temp;

    std::ifstream receipts("receipts.csv");
    if (receipts.is_open())
    {
        while (std::getline(receipts, lines))
        {
            std::istringstream line(lines);

            std::getline(line, temp, ',');
            total += std::stof(temp);

            std::getline(line, temp, ',');
            if (temp == "1")
                credit++;
            if (temp == "2")
                cash++;
        }
    }
    std::cout << "\nTotal Transactions: " << transactionCount << "\n";
    std::cout << "\n";

    std::cout << "Transactions made with cash: " << cash << "\n";
    std::cout << "Transactions made with credit: " << credit << "\n";

    std::cout << "Total Revenue: $" << total << "\n\n";
}

bool isValidCardNumber(long long int n)
// This function checks if the credit card number is valid. This is an implementation of the Luhn Algorithm. See more at
// https://en.wikipedia.org/wiki/Luhn_algorithm
{
    if (n < 0)
        return false;

    int digit;
    int sum = 0;
    bool runNextIteration = true;

    while (n != 0)
    {
        if (runNextIteration)
        {
            digit = n % 10;

            sum += digit;
            n /= 10;

            runNextIteration = false;
        }
        else
        {
            digit = n % 10;
            digit *= 2;

            if (digit > 9)
                digit -= 9;

            sum += digit;
            n /= 10;

            runNextIteration = true;
        }
    }

    if (sum % 10 == 0)
        return true;
    else
        return false;
}
