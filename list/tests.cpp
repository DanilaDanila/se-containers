#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <iostream>

#include "list.h"

using namespace lab618; // да, плохо

typedef CSingleLinkedList<int> ilist;
typedef CDualLinkedList<int> dilist;

void irange(ilist &list, int start = 0, int stop = 10, int step = 1) {
  for (int i = start; i < stop; i += step) {
    list.pushBack(i);
  }
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

void dirange(dilist &list, int start = 0, int stop = 10, int step = 1) {
  for (int i = start; i < stop; i += step) {
    list.pushBack(i);
  }
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

void beautify_print(const ilist &list) {
  for (auto it = list.begin(); it.isValid(); ++it) {
    std::cout << "[" << it.getData() << "]";
    if (it.getLeaf() == list.__begin()) {
      std::cout << " <-- begin";
    }
    if (it.getLeaf() == list.__end()) {
      std::cout << " <-- end";
    }
    std::cout << "\n";
  }
}

TEST_CASE("just compiles") {
  CSingleLinkedList<int> list;
  const CSingleLinkedList<int> clist;

  CDualLinkedList<int> dlist;
  const CDualLinkedList<int> cdlist;

  CHECK(true);
}

TEST_CASE("pushBack / pushFront test") {
  int arr[] = {1, 2, 3, 4};
  ilist list;
  CHECK(!list.begin().isValid());

  list.pushBack(arr[0]);
  CHECK(list.begin().isValid());
  CHECK(list.begin().getData() == arr[0]);

  list.pushBack(arr[1]);
  CHECK(list.begin().isValid());
  auto it = list.begin();
  ++it;
  CHECK(it.getData() == arr[1]);

  list.pushFront(arr[2]);
  CHECK(list.begin().isValid());
  CHECK(list.begin().getData() == arr[2]);

  list.pushFront(arr[3]);
  CHECK(list.begin().isValid());
  CHECK(list.begin().getData() == arr[3]);

  dilist dlist;
  CHECK(!dlist.begin().isValid());

  dlist.pushBack(arr[0]);
  CHECK(dlist.begin().isValid());
  CHECK(dlist.begin().getData() == arr[0]);

  dlist.pushBack(arr[1]);
  CHECK(dlist.begin().isValid());
  auto dit = dlist.begin();
  ++dit;
  CHECK(dit.getData() == arr[1]);

  dlist.pushFront(arr[2]);
  CHECK(dlist.begin().isValid());
  CHECK(dlist.begin().getData() == arr[2]);

  dlist.pushFront(arr[3]);
  CHECK(dlist.begin().isValid());
  CHECK(dlist.begin().getData() == arr[3]);
}

TEST_CASE("getSize Test") {

  int arr[] = {1, 2, 3, 4};
  ilist list;
  CHECK(list.getSize() == 0);

  list.pushBack(arr[0]);
  CHECK(list.getSize() == 1);
  list.pushBack(arr[1]);
  CHECK(list.getSize() == 2);
  list.pushFront(arr[2]);
  CHECK(list.getSize() == 3);
  list.pushFront(arr[3]);
  CHECK(list.getSize() == 4);

  dilist dlist;
  CHECK(dlist.getSize() == 0);

  dlist.pushBack(arr[0]);
  CHECK(dlist.getSize() == 1);
  dlist.pushBack(arr[1]);
  CHECK(dlist.getSize() == 2);
  dlist.pushFront(arr[2]);
  CHECK(dlist.getSize() == 3);
  dlist.pushFront(arr[3]);
  CHECK(dlist.getSize() == 4);
}

TEST_CASE("erase test list") {
  {
    ilist list;
    irange(list, 0, 1);
    auto it = list.begin();
    list.erase(it);
    CHECK(list.getSize() == 0);
  }
  {
    ilist list;
    irange(list, 0, 5);
    for (auto it = list.begin(); it.isValid(); ++it) {
      list.erase(it);
    }

    CHECK(list.getSize() == 0);
  }
  {
    ilist list;
    irange(list);
    for (auto it = list.begin(); it.isValid(); ++it) {
      if (it.getData() % 2 == 0)
        list.erase(it);
    }

    auto it = list.begin();
    CHECK(it.getData() == 1);
    ++it;
    CHECK(it.getData() == 3);
    ++it;
    CHECK(it.getData() == 5);
    ++it;
    CHECK(it.getData() == 7);
    ++it;
    CHECK(it.getData() == 9);
    ++it;
    CHECK(!it.isValid());
  }

  {
    ilist list;
    irange(list);
    for (auto it = list.begin(); it.isValid(); ++it) {
      if (it.getData() % 2 != 0)
        list.erase(it);
    }

    auto it = list.begin();
    CHECK(it.getData() == 0);
    ++it;
    CHECK(it.getData() == 2);
    ++it;
    CHECK(it.getData() == 4);
    ++it;
    CHECK(it.getData() == 6);
    ++it;
    CHECK(it.getData() == 8);
    ++it;
    CHECK(!it.isValid());
  }
}

TEST_CASE("erase test dlist forward") {
  {
    dilist list;
    dirange(list);
    for (auto it = list.begin(); it.isValid(); ++it) {
      if (it.getData() % 2 == 0)
        list.erase(it);
    }

    auto it = list.begin();
    CHECK(it.getData() == 1);
    ++it;
    CHECK(it.getData() == 3);
    ++it;
    CHECK(it.getData() == 5);
    ++it;
    CHECK(it.getData() == 7);
    ++it;
    CHECK(it.getData() == 9);
    ++it;
    CHECK(!it.isValid());
  }

  {
    dilist list;
    dirange(list);
    for (auto it = list.begin(); it.isValid(); ++it) {
      if (it.getData() % 2 != 0)
        list.erase(it);
    }

    auto it = list.begin();
    CHECK(it.getData() == 0);
    ++it;
    CHECK(it.getData() == 2);
    ++it;
    CHECK(it.getData() == 4);
    ++it;
    CHECK(it.getData() == 6);
    ++it;
    CHECK(it.getData() == 8);
    ++it;
    CHECK(!it.isValid());
  }
}

TEST_CASE("erase test dlist backward") {
  {
    dilist list;
    dirange(list);
    for (auto it = list.end(); it.isValid(); --it) {
      if (it.getData() % 2 == 0)
        list.erase(it);
    }

    auto it = list.begin();
    CHECK(it.getData() == 1);
    ++it;
    CHECK(it.getData() == 3);
    ++it;
    CHECK(it.getData() == 5);
    ++it;
    CHECK(it.getData() == 7);
    ++it;
    CHECK(it.getData() == 9);
    ++it;
    CHECK(!it.isValid());
  }

  {
    dilist list;
    dirange(list);
    for (auto it = list.end(); it.isValid(); --it) {
      if (it.getData() % 2 != 0)
        list.erase(it);
    }

    auto it = list.begin();
    CHECK(it.getData() == 0);
    ++it;
    CHECK(it.getData() == 2);
    ++it;
    CHECK(it.getData() == 4);
    ++it;
    CHECK(it.getData() == 6);
    ++it;
    CHECK(it.getData() == 8);
    ++it;
    CHECK(!it.isValid());
  }
}
