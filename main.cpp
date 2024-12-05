#include <cmath>
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
// TODO void welcomeScreen(void);

void authentication(void);
void readInventory(Item items[], int size, int properties);
void sellItem(Item items[], int size);

bool isValidCardNumber(long int n);

int main() {

  int properties = 4;
  int size = 7;
  Item items[7];
  readInventory(items, size, properties);
  sellItem(items, size);

  //  welcomeScreen();
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

  std::cout << std::internal << "A Retail Inventory Management System";
}

void readInventory(Item items[], int size, int properties) {

  std::string item;
  std::ifstream inventoryDatabase("database.csv");

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

void authentication(void) {}

void sellItem(Item items[], int size) {
  std::string id;
  int quantity;
  bool paymentMethod;
  float cash;
  int bill;

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

      bill = items[i].quantity * items[i].price;
      std::cout << "\nTotal Bill: $" << bill << "\n";

      std::cout << "\nChoose the desired payment method\n";
      std::cout << "0. Cash\n";
      std::cout << "1. Credit\n";
      std::cout << "Payment Method: ";
      std::cin >> paymentMethod;

      if (paymentMethod) {
        long int cardNumber;

        std::cout << "\nCard Number: ";
        std::cin >> cardNumber;

        if (!isValidCardNumber(cardNumber)) {
          std::cout << "Invalid Card Number. Transaction failed!\n";
          return;
        }
      } else {
        std::cout << "\nCash Amount: ";
        std::cin >> cash;
        if (cash < bill) {
          std::cout << "Insufficient Cash\n";
          return;
        }
        std::cout << "\nChange owed: $" << cash - bill << "\n";
      }

      items[i].quantity -= quantity;
      std::cout << "\nTransaction success\n";
      break;

    } else {
      continue;
    }
  }
}
