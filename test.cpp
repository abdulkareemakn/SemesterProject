#include <fstream>
#include <iostream>
#include <string>
int main() {
  std::string lines;

  std::ifstream file("database.csv");

  if (file.is_open()) {
    while (std::getline(file, lines, ',')) {
    }
  }
}
