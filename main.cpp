// DZ_28.9.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "merge_sort.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    const int arr_size = 100000000; // Размер массива
    int* arr = new int[arr_size];

    // Инициализация генератора случайных чисел
    srand(0);

    cout << "Allocate memory for array..." << endl;

    // Генерация массива случайных чисел
    cout << "Single thread\nGenerating random numbers and set in array..." << endl;
    for (size_t i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % 50000;
    }

    time_t start, end;
    cout << "Sorting in single thread started..." << endl;
    time(&start);
    // Сортировка без многопоточности
    mergeSort(arr, 0, arr_size - 1, false);
    time(&end);
    double seconds = difftime(end, start);
    printf("Elapsed time: %f seconds\n", seconds);

    // Проверка, что массив отсортирован
    cout << "Checking sorted array..." << endl;
    bool sorted = true;
    for (long i = 0; i < arr_size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            cout << "Array is not sorted at position " << i << endl;
            sorted = false;
            break;
        }
    }
    if (sorted)
        cout << "Array is sorted correctly." << endl;

    // Подготовка к многопоточной сортировке
    cout << "\nMultithread\nGenerating random numbers and set in array..." << endl;
    for (size_t i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % 50000;
    }
    cout << "Sorting in multithread started..." << endl;
    time(&start);
    // Включение многопоточности
    mergeSort(arr, 0, arr_size - 1, true);
    time(&end);
    seconds = difftime(end, start);
    printf("Elapsed time: %f seconds\n", seconds);

    // Проверка, что массив отсортирован
    cout << "Checking sorted array..." << endl;
    sorted = true;
    for (long i = 0; i < arr_size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            cout << "Array is not sorted at position " << i << endl;
            sorted = false;
            break;
        }
    }
    if (sorted)
        cout << "Array is sorted correctly." << endl;

    delete[] arr;
    return 0;
}