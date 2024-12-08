#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

struct Item {
  std::string name;
  std::string ID;
  int quantity;
  float price;
  // TODO int reorderLevel;
};
void welcomeScreen(void);

bool authentication(void);
void readInventory(Item items[], int size);
void displayInventory(Item items[], int size);
void writeInventory(Item items[], int size);
void restockInventory(Item items[], int size);
void updatePrices(Item items[], int size);
void sellItem(Item items[], int size);
void logReceipt(std::string name, std::string ID, int quantity, float bill,
                int paymentMethod);
void printReceipt(std::string name, int quantity, float price, float bill,
                  int paymentMethod);

bool isValidCardNumber(long int n);

int transactionCount = 0;
int cashTransaction = 0;
int creditTransaction = 0;

int main() {

  int size = 7;
  Item items[7];

  welcomeScreen();

  if (authentication()) {

    readInventory(items, size);
    displayInventory(items, size);
    // sellItem(items, size);
    //     writeInventory(items, size);

  } else
    std::cout << "Invalid Credentials" << std::endl;
}

bool isValidCardNumber(long int n) {
  int digit;
  int sum = 0;
  bool runNextIteration = true;

  while (n != 0) {
    if (runNextIteration) {
      digit = n % 10;

      sum += digit;
      n /= 10;

      runNextIteration = false;

    } else {
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

void welcomeScreen(void) {

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

void readInventory(Item items[], int size) {

  std::string item;
  std::ifstream inventoryDatabase("inventory.csv");

  if (inventoryDatabase.is_open()) {

    int i = 0;
    std::string temp;

    while (std::getline(inventoryDatabase, item)) {
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

void displayInventory(Item items[], int size) {
  std::cout << std::left << std::setw(10)
            << "Name\t\t|  ID\t\t|  Quantity\t|  Price\t\n\n";

  for (int i = 0; i < size; i++) {
    std::cout << std::left << std::setw(10) << items[i].name << "\t|  "
              << items[i].ID << "\t|  " << items[i].quantity << "\t\t|  $"
              << items[i].price << "\n";
  }

  std::cout << "\n\n";
}

void writeInventory(Item items[], int size) {
  std::ofstream inventoryDatabase("inventory.csv");

  for (int i = 0; i < size; i++) {
    inventoryDatabase << items[i].name << "," << items[i].ID << ","
                      << items[i].quantity << "," << items[i].price;

    if (i != size - 1) {
      inventoryDatabase << "\n";
    }
  }

  inventoryDatabase.close();
}

bool authentication(void) {
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

void sellItem(Item items[], int size) {
  std::string id;
  int quantity;
  int paymentMethod;
  float cash;
  float bill;
  float change;

  std::cout << std::left << std::setw(10) << "Name\t\t|  ID\t\t|  Price\n\n";

  for (int i = 0; i < size; i++) {
    std::cout << std::left << std::setw(10) << items[i].name << "\t|  "
              << items[i].ID << "\t|  $" << items[i].price << "\n";
  }

  std::cout << "\nWhich item do you want to sell? \n";
  std::cout << "Item ID: ";
  std::getline(std::cin, id);

  // show quantity
  for (int i = 0; i < size; i++) {
    if (id == items[i].ID) {
      std::cout << "\nItem available in stock: " << items[i].quantity << "\n";

      std::cout << "Quantity to sell: ";
      std::cin >> quantity;

      if (quantity > items[i].quantity) {
        std::cout << "\nInvalid. More than stock available";
        return;
      }

      bill = quantity * items[i].price;
      std::cout << "\nTotal Bill: $" << bill << "\n";

      for (int i = 1; i <= 3; i++) {

        std::cout << "\nChoose the desired payment method\n";
        std::cout << "1. Credit\n";
        std::cout << "2. Cash\n";
        std::cout << "Payment Method: ";
        std::cin >> paymentMethod;

        if (paymentMethod == 1) {
          long int cardNumber;

          std::cout << "\nCard Number: ";
          std::cin >> cardNumber;

          creditTransaction++;

          if (!isValidCardNumber(cardNumber)) {
            std::cout << "Invalid Card Number. Transaction failed!\n";
            return;
          }
          break;
        } else if (paymentMethod == 2) {
          std::cout << "\nCash Amount: $";
          std::cin >> cash;
          if (cash < bill) {
            std::cout << "Insufficient Cash\n";
            return;
          }
          change = cash - bill;
          std::cout << "\nChange owed: $" << change << "\n";

          cashTransaction++;
          break;
        } else {
          std::cout << "Invalid Payment method!";
          if (i == 3)
            return;
        }
      }

      logReceipt(items[i].name, items[i].ID, quantity, bill, paymentMethod);

      printReceipt(items[i].name, quantity, items[i].price, bill,
                   paymentMethod);

      items[i].quantity -= quantity;
      std::cout << "\nTransaction success\n";

      transactionCount++;
      break;

    } else {
      if (i == size - 1) {
        std::cout << "Invalid Product ID";
        return;
      }
    }
  }
}

void logReceipt(std::string name, std::string ID, int quantity, float bill,
                int paymentMethod) {
  std::ofstream receiptsDatabase("receipts.csv", std::ios::app);
  std::cout << "\nTransaction Processing. Press any character to print "
               "receipt.";
  std::cin.ignore();
  std::getchar();
  std::cout << "\n\n";

  receiptsDatabase << name << "," << ID << "," << quantity << "," << bill
                   << "\n";

  receiptsDatabase.close();
}

void printReceipt(std::string name, int quantity, float price, float bill,
                  int paymentMethod) {

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
  std::cout << std::left << std::setw(10) << name << "\t\t| " << std::right
            << quantity << "  | $" << price << "   |" << "\n";

  std::cout << "\n\n";

  std::cout << "Total Amount: \t\t$" << bill;
  std::cout << "\n\n\n";

  if (paymentMethod == 1) {
    std::cout << "Payment Method: \t" << "Credit";
  } else {
    std::cout << "Payment Method: \t" << "Cash";
  }

  std::cout << "\n\n";
  std::cout << "-------------------------------------------\n";
  std::cout << "Thank you for your purchase!\n";
}

void restockInventory(Item items[], int size) {
  displayInventory(items, size);
  std::string ID;
  int quantity;
  std::cout << "\n";
  std::cout << "Which item do you want to restock? (ID)";
  std::getline(std::cin, ID);
  for (int i = 0; i < size; i++) {
    if (ID == items[i].ID) {
      std::cout << "Quantity to restock? ";
      std::cin >> quantity;

      items[i].quantity += quantity;

      std::cout << "Stock updated successfully!\n";
    }
    if (i == size - 1)
      std::cout << "Invalid ID!\n";
  }
}

void updatePrices(Item items[], int size) {
  displayInventory(items, size);
  std::string ID;
  float price;

  std::cout << "Which item's price is to be updated? (ID)";
  std::getline(std::cin, ID);

  for (int i = 0; i < size; i++) {
    if (ID == items[i].ID) {
      std::cout << "What is the new price? ";
      std::cin >> price;

      if (price <= 0) {
        std::cout << "Invalid Amount!\n";
      }
      items[i].price = price;
      std::cout << "Price updated successfully!\n";
    }
    if (i == size - 1)
      std::cout << "Invalid ID!\n";
  }
}
