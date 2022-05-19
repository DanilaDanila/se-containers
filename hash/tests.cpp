#include "hash.h"

#include <cassert>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace lab618;

struct Item {
  std::string key;
  unsigned int value;
};

unsigned int hash(const std::string *str) {
  unsigned int hsum = 0;
  unsigned int p = 1;
  const unsigned int pmp = 17;
  for (auto letter : *str) {
    hsum += letter * p;
    p *= pmp;
  }
  return hsum;
}

unsigned int ihash(const Item *item) { return hash(&(item->key)); }

//  Нам нужна только проверка на равенство, поэтому можно
// возвращать только '0' (равенство) и 'не 0' (неравенство).
int cmp(const std::string *str0, const std::string *str1) {
  return 1 - static_cast<int>(*str0 == *str1);
}

int icmp(const Item *item0, const Item *item1) {
  return 1 - static_cast<int>(item0->key == item1->key);
}

std::string gen_random(const int len) {
  static const char alphanum[] = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  tmp_s.reserve(len);

  for (int i = 0; i < len; ++i) {
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return tmp_s;
}

void cmp_test() {
  std::string first = gen_random(32);
  std::string second = gen_random(32);

  assert(cmp(&first, &second) != 0);
  assert(cmp(&first, &first) == 0);
  assert(cmp(&second, &second) == 0);
}

void some_test() {
  const int N = 20;
  auto hashmap = CHash<Item, ihash, icmp>(N, 16);
  Item strs[2 * N];
  for (int i = 0; i < 2 * N; ++i) {
    strs[i].key = std::to_string(i * i);
    strs[i].value = 1;
    hashmap.add(&strs[i]);
  }

  for (int i = 0; i < 2 * N; ++i) {
    Item item = {std::to_string(i * i), 1};
    std::cerr << i << ": " << hashmap.find(item) << "\n";
  }

  Item items[2 * N];
  for (int i = 0; i < 2 * N; ++i) {
    items[i].key = std::to_string(i * i);
    items[i].value = 3;
    hashmap.update(&items[i]);
  }

  for (int i = 0; i < 2 * N; ++i) {
    Item item = {std::to_string(i * i), 21313};
    hashmap.remove(item);
  }
}

void stress_test() {
  return;
  const int N = 2000;
  auto hashmap = CHash<std::string, hash, cmp>(N, 16);

  std::vector<std::string> vec_str(N);
  for (int i = 0; i < N; ++i) {
    std::string new_string = gen_random(32);
    vec_str[i] = new_string;
    hashmap.add(&vec_str[i]);
    std::cout << "ADD: " << vec_str[i] << "\n";
  }

  unsigned found = 0;
  unsigned missed = 0;
  for (auto &str : vec_str) {
    auto *ptr = hashmap.find(str);
    if (ptr != nullptr) {
      std::cout << "FOUND: " << *ptr << "\n";
      ++found;
    } else {
      ++missed;
    }
  }
  std::cout << "\nTOTAL FOUND: " << found << "\n";
  std::cout << "TOTAL MISSED: " << missed << " ((((\n";
}

int main() {
  srand(time_t(42));
  cmp_test();
  some_test();
  stress_test();
  return 0;
}
