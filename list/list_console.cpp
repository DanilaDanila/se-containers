#include <iostream>

#include "list.h"

using namespace lab618; // да, плохо

typedef CSingleLinkedList<int> ilist;
typedef CDualLinkedList<int> dilist;

ilist irange(int start = 0, int stop = 10, int step = 1) {
  ilist list;

  for (int i = start; i < stop; i += step) {
    list.pushBack(i);
  }

  return list;
}

void print_list(const ilist &list) {
  for (auto it = list.begin(); it.isValid(); ++it) {
    std::cout << *it << " ";
  }

  std::cout << "\n";
}

void pop_list(ilist &list) {
  const int N = list.getSize();
  for (int i = 0; i < N; ++i) {
    auto tmp = list.popFront();
    ++tmp;
  }
}

dilist dirange(int start = 0, int stop = 10, int step = 1) {
  dilist list;

  for (int i = start; i < stop; i += step) {
    list.pushBack(i);
  }

  return list;
}

void print_dlist(const dilist &list) {
  for (auto it = list.begin(); it.isValid(); ++it) {
    std::cout << *it << " ";
  }

  std::cout << "\n";
}

void pop_dlist(dilist &list) {
  const int N = list.getSize();
  for (int i = 0; i < N; ++i) {
    auto tmp = list.popBack();
    ++tmp;
  }
}

void dlist_iter_check(const dilist &list) {
  for (auto it = list.begin(); it.isValid(); ++it)
    ;
  for (auto it = list.end(); it.isValid(); --it)
    ;
}

void beautify_print(const ilist &list, ilist::CIterator &itt) {
  for (auto it = list.begin(); it.isValid(); ++it) {
    std::cout << "[" << it.getData() << "]";
    if (itt.getLeaf() == it.getLeaf()) {
      std::cout << " ^";
    }
    if (it.getLeaf() == list.__begin()) {
      std::cout << " <-- begin";
    }
    if (it.getLeaf() == list.__end()) {
      std::cout << " <-- end";
    }
    std::cout << "\n";
  }
}

void console() {
  ilist list = irange(0, 5);
  ilist::CIterator it = list.begin();

  std::string input;
  std::system("clear");
  beautify_print(list, it);
  std::cout << "> ";
  std::cin >> input;
  do {
    std::system("clear");
    if (input == "append") {
      std::cin >> input;
      int num = atoi(input.c_str());
      list.pushBack(num);
    } else if (input == "size") {
      std::cout << "getSize: " << list.getSize() << "\n";
    } else if (input == "check") {
      std::cout << "isValid: " << it.isValid() << "\n";
    } else if (input == "at") {
      std::cin >> input;
      int id = atoi(input.c_str());
      for (it = list.begin(); id > 0; --id, ++it)
        ;
    } else if (input == "next") {
      ++it;
    } else if (input == "del") {
      list.erase(it);
    }

    beautify_print(list, it);
    std::cout << "> ";
    std::cin >> input;
  } while (input != "stop");
}

void beautify_print(const dilist &list, dilist::CIterator &itt) {
  for (auto it = list.begin(); it.isValid(); ++it) {
    std::cout << "[" << it.getData() << "]";
    if (itt.getLeaf() == it.getLeaf()) {
      std::cout << " ^";
    }
    if (it.getLeaf() == list.__begin()) {
      std::cout << " <-- begin";
    }
    if (it.getLeaf() == list.__end()) {
      std::cout << " <-- end";
    }
    std::cout << "\n";
  }
}

void console2() {
  dilist list = dirange(0, 5);
  dilist::CIterator it = list.begin();

  std::string input;
  std::system("clear");
  beautify_print(list, it);
  std::cout << "> ";
  std::cin >> input;
  do {
    std::system("clear");
    if (input == "append") {
      std::cin >> input;
      int num = atoi(input.c_str());
      list.pushBack(num);
    } else if (input == "size") {
      std::cout << "getSize: " << list.getSize() << "\n";
    } else if (input == "check") {
      std::cout << "isValid: " << it.isValid() << "\n";
    } else if (input == "at") {
      std::cin >> input;
      int id = atoi(input.c_str());
      for (it = list.begin(); id > 0; --id, ++it)
        ;
    } else if (input == "next") {
      ++it;
    } else if (input == "back") {
      --it;
    } else if (input == "del") {
      list.erase(it);
    } else if (input == "ndel") {
      list.eraseAndNext(it);
    }

    beautify_print(list, it);
    std::cout << "> ";
    std::cin >> input;
  } while (input != "stop");
}

int main() { console2(); }
