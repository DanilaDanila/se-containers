#include "sort.h"

#include <cassert>

namespace lab618 {

void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc) {
  if (length == 1) {
    return;
  }

  int half = length / 2;
  void **left = ppArray;
  void **right = ppArray + half;

  mergeSort(left, half, pCompareFunc);
  mergeSort(right, length - half, pCompareFunc);

  void **tmp = new void *[length];

  for (int i = 0, j = 0; i + j < length;) {
    if (i == half) {
      tmp[i + j] = right[j];
      ++j;
    } else if (j == length - half) {
      tmp[i + j] = left[i];
      ++i;
    } else if (pCompareFunc(left[i], right[j]) > 0) {
      tmp[i + j] = left[i];
      ++i;
    } else {
      tmp[i + j] = right[j];
      ++j;
    }
  }

  for (int i = 0; i < length; ++i) {
    ppArray[i] = tmp[i];
  }

  delete[] tmp;
}

} // namespace lab618
