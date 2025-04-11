#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

int main() {
  std::string name = "Apple";
  int quantity = 10;
  float bill = 34.89;
  bool method = 0;
  float change = 5.11;

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
  std::cout << std::left << std::setw(10) << name << "\t\t| " << quantity
            << "  | $" << bill << "   |" << "\n";

  std::cout << "\n\n";

  std::cout << "Total Amount: \t\t$" << bill;
  std::cout << "\n\n\n";

  if (method) {
    std::cout << "Payment Method: \t" << "Credit";
  } else {
    std::cout << "Payment Method: \t" << "Cash";
  }

  std::cout << "\n\n";
  std::cout << "-------------------------------------------\n";
  std::cout << "Thank you for your purchase!\n";
  std::cout << std::endl;
}
