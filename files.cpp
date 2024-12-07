#include <fstream>
int main() {
  std::ofstream database("inventory.csv");

  if (database.is_open()) {
    // grocery items
    database << "Bananas,GR1001,150,0.50\n";
    database << "Apples,GR1006,250,0.80\n";
    database << "Strawberries,GR1015,110,3.80\n";

    // dairy items
    database << "Milk,DR1002,200,1.20\n";
    database << "Eggs,DR1003,120,2.99\n";
    database << "Salted Butter,DR1005,100,3.00\n";
    database << "Yogurt,DR1009,90,2.20\n";
  }
  database.close();
}
