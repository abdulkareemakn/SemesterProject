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
bool isValidCardNumber(long int n);

int main() {

  Item items[7];
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

void readInventory(Item *items[], int size, int properties) {
  std::string item;
  std::ifstream inventoryDatabase("database.csv");
  while (std::getline(inventoryDatabase, item)) {
    int length = item.length();
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < length; j++) {
      }
    }
  }
}
