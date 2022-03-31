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

void test_list() {
  std::cout << "Test all methods\n";
  {
    ilist list = irange();
    int a = 1;
    list.pushBack(a);
    list.pushFront(a);
    a = list.popFront();
    ++a;
    a = list.getSize();
    ++a;

    auto it = list.begin();
    a = it.getData();
    ++a;
    a = *it;
    ++a;
    auto tmp = it.getLeaf();
    a = tmp->data;
    ++a;
  }

  std::cout << "Test list\n";
  {
    std::cout << "\tBasic test\n";
    ilist list = irange();
    print_list(list);
    pop_list(list);
  }

  {
    std::cout << "\tRemove odd\n";
    ilist list = irange();
    print_list(list);
    for (auto it = list.begin(); it.isValid(); ++it) {
      if (it.getData() % 2 == 1)
        list.erase(it);
    }
    print_list(list);
    pop_list(list);
  }

  {
    std::cout << "\tRemove even\n";
    ilist list = irange();
    print_list(list);
    for (auto it = list.begin(); it.isValid(); ++it) {
      if (it.getData() % 2 == 0)
        list.erase(it);
    }
    print_list(list);
    pop_list(list);
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

void test_dlist() {
  std::cout << "Test all methods\n";
  {
    dilist list = dirange();
    int a = 1;
    list.pushBack(a);
    list.pushFront(a);
    a = list.popBack();
    ++a;
    a = list.popFront();
    ++a;
    a = list.getSize();
    ++a;

    auto it = list.begin();
    a = it.getData();
    ++a;
    a = *it;
    ++a;
    auto tmp = it.getLeaf();
    a = tmp->data;
    ++a;
  }

  std::cout << "Test dlist\n";
  {
    std::cout << "\tBasic test\n";
    dilist list = dirange();
    print_dlist(list);
    pop_dlist(list);
  }

  {
    std::cout << "\tForward test\n";
    {
      std::cout << "\t\tRemove odd\n";
      dilist list = dirange();
      print_dlist(list);
      for (auto it = list.begin(); it.isValid(); ++it) {
        if (it.getData() % 2 == 1)
          list.erase(it);
      }
      print_dlist(list);
      dlist_iter_check(list);
      pop_dlist(list);
    }

    {
      std::cout << "\t\tRemove even\n";
      dilist list = dirange();
      print_dlist(list);
      for (auto it = list.begin(); it.isValid(); ++it) {
        if (it.getData() % 2 == 0)
          list.erase(it);
      }
      print_dlist(list);
      dlist_iter_check(list);
      pop_dlist(list);
    }
  }

  {
    std::cout << "\tBackword test\n";
    {
      std::cout << "\t\tRemove odd\n";
      dilist list = dirange();
      print_dlist(list);
      for (auto it = list.end(); it.isValid(); --it) {
        if (it.getData() % 2 == 1)
          list.eraseAndNext(it);
      }
      print_dlist(list);
      dlist_iter_check(list);
      pop_dlist(list);
    }

    {
      std::cout << "\t\tRemove even\n";
      dilist list = dirange();
      print_dlist(list);
      for (auto it = list.end(); it.isValid(); --it) {
        if (it.getData() % 2 == 0)
          list.eraseAndNext(it);
      }
      print_dlist(list);
      dlist_iter_check(list);
      pop_dlist(list);
    }
  }
}

int main() {
  test_list();
  test_dlist();
}
