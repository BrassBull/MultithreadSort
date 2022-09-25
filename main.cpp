#include <iostream>
#include <thread>
#include <ctime>
using namespace std;
void combine_array(double* arr, int first, int mid_val, int end) //объединение подмассивов
{
    double* start = new double[mid_val - first + 1];
    double* last = new double[end - mid_val];
    int temp_1 = mid_val - first + 1;
    int temp_2 = end - mid_val;
    int i, j;
    int k = first;
    for (i = 0; i < temp_1; i++) {
        start[i] = arr[i + first];
    }
    for (i = 0; i < temp_2; i++) {
        last[i] = arr[i + mid_val + 1];
    }
    i = j = 0;
    while (i < temp_1 && j < temp_2) {
        if (start[i] <= last[j]) {
            arr[k++] = start[i++];
        }
        else {
            arr[k++] = last[j++];
        }
    }
    while (i < temp_1) {
        arr[k++] = start[i++];
    }
    while (j < temp_2) {
        arr[k++] = last[j++];
    }
    delete[] start;
    delete[] last;
}
void quicksort(double* mas, int first, int last) //алгоритм быстрой сортировки с рекурсией
{
    double mid, count;
    int f = first, l = last;
    mid = mas[(f + l) / 2]; //вычисление опорного элемента
    do
    {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        if (f <= l) //перестановка элементов
        {
            count = mas[f];
            mas[f] = mas[l];
            mas[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l);
    if (f < last) quicksort(mas, f, last);
}

int main() 
{
    int size;
    cout << "Array size: "; cin >> size;
    double *arr = new double[size];
    double *barr = new double[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() * 0.01;
        barr[i] = arr[i];
    }
    clock_t t = clock();
    std::thread thr1(quicksort, arr, 0, (size / 2 - 1) / 2);
    std::thread thr2(quicksort, arr, ((size / 2 - 1) / 2) + 1, size / 2 - 1);
    std::thread thr3(quicksort, arr, size / 2, size / 2 + (size - 1 - size / 2) / 2);
    std::thread thr4(quicksort, arr, (size / 2 + (size - 1 - size / 2) / 2) + 1, size - 1);
    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();
    combine_array(arr, 0, (size / 2 - 1) / 2, size / 2 - 1);
    combine_array(arr, size / 2, size / 2 + (size - 1 - size / 2) / 2, size - 1);
    combine_array(arr, 0, (size - 1) / 2, size - 1);
    t = clock() - t;
    cout << "Quick Sort with Multi-threading: ";
    std::cout << "\n Time -> " << (float)t / CLOCKS_PER_SEC << std::endl;
    t = clock();
    quicksort(barr, 0, size - 1);
    t = clock() - t;
    cout << "Quick Sort without Multi-threading: ";
    std::cout << "\n Time -> " << (float)t / CLOCKS_PER_SEC << std::endl;
    delete[] arr;
    delete[] barr;
    return 0;
}