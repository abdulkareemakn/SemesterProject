#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

struct Item {
  std::string name;
  std::string ID;
  int quantity;
  float price;
  // TODO int reorderLevel;
};
// TODO void welcomeScreen(void);
void readInventory(std::array<Item, 7> &items, int properties);

bool isValidCardNumber(long int n);

int main() {

  std::array<Item, 7> items;
  readInventory(items, 4);

  //  welcomeScreen();

  long int cardNumber;

  std::cout << "Card Number: ";
  std::cin >> cardNumber;

  std::cout << isValidCardNumber(cardNumber) << std::endl;
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

void readInventory(std::array<Item, 7> &items, int properties) {
  int itemsCount = items.size();

  std::string item;
  std::ifstream inventoryDatabase("database.csv");

  if (inventoryDatabase.is_open()) {

    int lineCount = 0;
    while (std::getline(inventoryDatabase, item, ',')) {

      int length = item.length();
      for (int j = 0; j < length; j++) {

        do {
          items[lineCount].name += item[j];
        } while (item[j] != ',');
      }
      lineCount++;
    }
  }
  inventoryDatabase.close();
}
