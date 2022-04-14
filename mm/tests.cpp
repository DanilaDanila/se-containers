#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "mm.h"
#include <ctime>
#include <doctest.h>
#include <iostream>

using namespace lab618;

struct Item {
  int number;
  std::string string;
  time_t date;
  bool alive = true;

  Item() = default;

  Item(int number) : number(number) {
    string = "Hello";
    date = time(0); // now
  }

  ~Item() { alive = false; }
};

TEST_CASE("just compiles") { CMemoryManager<Item> mm(1); }

TEST_CASE("simple alloc dealloc") {
  CMemoryManager<Item> mm(1);

  Item *some_item = new (mm.newObject()) Item(123);
  mm.deleteObject(some_item);
}

TEST_CASE("not so simple test") {
  CMemoryManager<Item> mm(2);

  Item *p_items[10];

  for (int i = 0; i < 10; ++i) {
    p_items[i] = new (mm.newObject()) Item(i);
  }

  for (int i = 0; i < 10; ++i) {
    CHECK(p_items[i]->number == i);
    CHECK(p_items[i]->string == "Hello");
    CHECK(p_items[i]->alive == true);
    mm.deleteObject(p_items[i]);
    CHECK(p_items[i]->alive == false);
  }
}

/*
TEST_CASE("alloc string") {
  typedef struct {
    char c_str[20];
  } c_string_t;

  CMemoryManager<c_string_t> mm(1);
  c_string_t *a = mm.newObject();
  c_string_t *b = mm.newObject();

  mm.deleteObject(a);
  mm.deleteObject(b);
}
*/
