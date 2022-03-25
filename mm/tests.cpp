#include "mm.h"
#include <ctime>
#include <iostream>

using namespace lab618;

struct Item {
  int number;
  std::string string;
  time_t date;

  Item() = default;

  Item(int number) : number(number) {
    string = "Hello";
    date = time(0); // now
  }
};

void do_smth(CMemoryManager<Item> &mm) {
  Item *p_items[200];

  for (int i = 0; i < 200; ++i) {
    p_items[i] = new (mm.newObject()) Item(i);
  }

  for (int i = 0; i < 200; ++i) {
    std::cout << p_items[i]->number << " " << p_items[i]->string << " "
              << p_items[i]->date << "\n";
    mm.deleteObject(p_items[i]);
  }
}

int main() {
  auto mm = CMemoryManager<Item>(4, true);

  do_smth(mm);
  return 0;
}
