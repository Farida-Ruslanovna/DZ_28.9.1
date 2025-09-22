#ifndef MERGE_SORT_H
#define MERGE_SORT_H

// Объявление функции mergeSort
void mergeSort(int* arr, int l, int r, bool multithread = false);

// Объявление функции merge для слияния двух отсортированных частей
void merge(int* arr, int l, int m, int r);

#endif