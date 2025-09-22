#include "merge_sort.h"
#include <future>

// Функция слияния двух отсортированных подмассивов
void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;     // Размер левой части
    int nr = r - m;         // Размер правой части

    int* left = new int[nl]; // Временный массив для левой части
    int* right = new int[nr]; // Временный массив для правой части

    // Копирование данных в временные массивы
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Слияние двух массивов
    while (i < nl && j < nr)
    {
        if (left[i] < right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    // Копирование оставшихся элементов из левой части
    while (i < nl)
        arr[k++] = left[i++];

    // Копирование оставшихся элементов из правой части
    while (j < nr)
        arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

// Рекурсивная функция сортировки с возможностью использования потоков
void mergeSort(int* arr, int l, int r, bool multithread)
{
    if (l >= r)
        return;

    int m = (l + r) / 2;

    // Если включена многопоточность и размер подмассива больше порога
    if (multithread && (m - l > 100000))
    {
        // Асинхронная сортировка левой части
        auto future_left = std::async(std::launch::async, mergeSort, arr, l, m, multithread);
        // Сортировка правой части в текущем потоке
        mergeSort(arr, m + 1, r, multithread);
        // Ожидание завершения левой части
        future_left.get();
    }
    else
    {
        // Последовательная сортировка
        mergeSort(arr, l, m, multithread);
        mergeSort(arr, m + 1, r, multithread);
    }
    // Объединение отсортированных частей
    merge(arr, l, m, r);
}