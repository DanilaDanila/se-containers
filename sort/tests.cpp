#include <cstdlib>
#include <iostream>

#include "sort.h"

using namespace lab618;

inline void assert(bool cmp, std::string msg) {
  if (!cmp) {
    std::cerr << msg << "\n";
    exit(1);
  }
}

template <typename T> inline int sign(T num) {
  if (num > 0) {
    return 1;
  } else if (num < 0) {
    return -1;
  }

  return 0;
}

typedef void(SortFuncType)(void **ppArray, int length,
                           CompareSortType pCompareFunc);

template <class T>
inline bool check_eq(const T **arr0, T **arr1, int length,
                     int(cmp)(T *el0, T *el1)) {
  for (int i = 0; i < length; ++i) {
    if (cmp(arr0[i], arr1[i]) != 0) {
      return false;
    }
  }

  return true;
}

template <class T> inline bool check(T **arr, int length, CompareSortType cmp) {
  for (int i = 0; i < length - 1; ++i) {
    if (cmp(arr[i], arr[i + 1]) < 0) {
      return false;
    }
  }

  return true;
}

template <class T> struct DataHolder {
  int key;
  T value;
};

typedef DataHolder<int> iDataHolder;

void print(iDataHolder **arr, int length) {
  std::cout << "{ ";
  for (int i = 0; i < length; ++i) {
    std::cout << arr[i]->key << " ";
  }
  std::cout << "}\n";
}

/*
int cmp(const void *dh0, const void *dh1) {
  return sign(reinterpret_cast<const iDataHolder *>(dh1)->key -
              reinterpret_cast<const iDataHolder *>(dh0)->key);
}
*/

int _cmp(const iDataHolder *dh0, const iDataHolder *dh1) {
  return sign(dh1->key - dh0->key);
}

int cmp(const void *first, const void *second) {
  return _cmp((const iDataHolder *)first, (const iDataHolder *)second);
}

iDataHolder **arange(int start, int stop, int direction = 1) {
  iDataHolder **arr = new iDataHolder *[stop - start];

  if (direction == 1) {
    for (int id = 0, value = start; value < stop; ++id, value += direction) {
      arr[id] = new iDataHolder;

      arr[id]->key = id;
      arr[id]->value = value;
    }
  } else {
    for (int id = 0, value = stop; value > start; ++id, value += direction) {
      arr[id] = new iDataHolder;

      arr[id]->key = id;
      arr[id]->value = value;
    }
  }

  return arr;
}

iDataHolder **arange(int length) { return arange(0, length); }

iDataHolder **randarr(int length, int from = 0, int to = 100) {
  iDataHolder **arr = new iDataHolder *[length];

  for (int id = 0; id < length; ++id) {
    arr[id] = new iDataHolder;

    const int randval = std::rand() % (to - from) + to;
    arr[id]->key = randval;
    arr[id]->value = randval;
  }

  return arr;
}

void ifree(iDataHolder **arr, int len) {
  for (int i = 0; i < len; ++i) {
    delete arr[i];
  }
  delete[] arr;
}

// ********** Bubble Sort ********** //

template <class T> inline void swap(T *&first, T *&second) {
  T *tmp = first;
  first = second;
  second = tmp;
}

void bubbleSort(void **ppArray, int length, CompareSortType pCompareFunc) {
  for (int i = 0; i < length; ++i) {
    for (int j = 0; j < length - i - 1; ++j) {
      if (pCompareFunc(ppArray[j], ppArray[j + 1]) < 0) {
        swap(ppArray[j], ppArray[j + 1]);
      }
    }
  }
}

template <class T>
void bubbleSort(T **ppArray, int length,
                int(pCompareFunc)(T *pElem1, T *pElem2)) {
  bubbleSort(reinterpret_cast<void **>(ppArray), length,
             (CompareSortType *)pCompareFunc);
}

// ********** TESTS ********** //

void test_arange(SortFuncType /* sort */) {
  std::cerr << "test 'arange' started\n";
  iDataHolder **arr = arange(10);
  for (int i = 0; i < 10; ++i) {
    assert(arr[0]->key == 0, "arange error");
    assert(arr[0]->value == 0, "arange error");
  }

  std::cerr << "test 'arange' passed!\n";
}

void test_check(SortFuncType /* sort */) {
  std::cerr << "test 'check' started\n";
  iDataHolder **arr = arange(10);
  assert(check<iDataHolder>(arr, 10, cmp), "check(T**) not working :(");
  ifree(arr, 10);

  auto wrong = randarr(100);
  assert(!check(wrong, 100, cmp), "check(T**) not working :(");
  ifree(wrong, 100);

  std::cerr << "test 'check' passed!\n";
}

void test_on_sorted(SortFuncType sort) {
  std::cerr << "test 'On sorted' started\n";
  iDataHolder **tiny = arange(4);
  sort((void **)tiny, 4, cmp);
  assert(check(tiny, 4, cmp), "test 'On sorted' failed on tiny :(");
  ifree(tiny, 4);

  iDataHolder **small = arange(10);
  sort((void **)small, 10, cmp);
  assert(check(small, 10, cmp), "test 'On sorted' failed on small :(");
  ifree(small, 10);

  iDataHolder **large = arange(128);
  sort((void **)large, 128, cmp);
  assert(check(large, 128, cmp), "test 'On sorted' failed on large :(");
  ifree(large, 128);

  iDataHolder **huge = arange(1024);
  sort((void **)huge, 1024, cmp);
  assert(check(huge, 1024, cmp), "test 'On sorted' failed on huge :(");
  ifree(huge, 1024);

  std::cerr << "test 'On sorted' passed!\n";
}

void test_presampled(SortFuncType sort) {
  std::cerr << "test 'Presampled' started\n";
  iDataHolder **small = randarr(10);
  sort((void **)small, 10, cmp);
  assert(check(small, 10, cmp), "test 'Presampled' failed on small :(");
  ifree(small, 10);

  iDataHolder **large = arange(0, 128, -1);
  sort((void **)large, 128, cmp);
  assert(check(large, 128, cmp), "test 'Presampled' failed on large :(");
  ifree(large, 128);

  std::cerr << "test 'Presampled' passed!\n";
}

void test_stress(SortFuncType sort) {
  std::cerr << "test 'Stress' started\n";
  const int length = 300;

  for (int i = 0; i < length; ++i) {
    iDataHolder **arr = randarr(length);
    sort((void **)arr, length, cmp);
    assert(check(arr, length, cmp), "test 'Stress' failed :(");
    ifree(arr, length);
  }

  std::cerr << "test 'Stress' passed!\n";
}

int main() {
  /*
  auto arr = randarr(10);

  print(arr, 10);
  heapSort<iDataHolder>(arr, 10, cmp);
  print(arr, 10);

  ifree(arr, 10);
  */
  auto tests_list = {test_arange, test_check, test_on_sorted, test_presampled,
                     test_stress};

  for (auto test : tests_list) {
    // test(bubbleSort);
    test(mergeSort);
    std::cerr << "\n";
  }
}
