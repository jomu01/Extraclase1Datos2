#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "PagedArray.h"

void quickSort(PagedArray& arr, int low, int high);
void insertionSort(PagedArray& arr, int low, int high);
void bubbleSort(PagedArray& arr, int low, int high);

#endif // SORTING_ALGORITHMS_H
