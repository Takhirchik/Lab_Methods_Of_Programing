#include <iostream>
#include <thread>
#include <vector>
#include <ctime>

using namespace std;

void shell_sort(int* arr, int size)
{
    for (auto d = size; d > 0; d /= 2) {
        for (auto i = d; i < size; i++) {
            for (auto j = i; j >= d && arr[j] < arr[j - d]; j -= d) {
                int tmp = arr[j];
                arr[j] = arr[j - d];
                arr[j - d] = tmp;
            }
        }
    }
}

void sort(int* arr, int step, int n, int i) {
    for (i; i < (n - step); i++) {
        for (int j = i; j >= 0 && arr[j] > arr[j + step]; j--) {
            int tmp = arr[j];
            arr[j] = arr[j + step];
            arr[j + step] = tmp;
        }
    }
}

void parralel_shell_sort(int* arr, int step, int n, int max_threads)
{
    vector<thread> threads;
    for (int i = 0; i < max_threads; i++) {
        if (i > n) break;
        threads.push_back(thread(sort, arr, step, n, i));
    }
    for (auto& t : threads) {
        t.join();
    }
    if (step / 2 > 1) {
        parralel_shell_sort(arr, step / 2, n, max_threads / 2);
    }
    else {
        sort(arr, step, n, 0);
    }
}

// Функция для создания убывающего динам. массива
int* createArray(int n) {
    int* array = new int[n];
    for (int i = 0; i < n; ++i)
        array[i] = n - i;
    return array;
}


// Выводит динамический массив array размерности size
void printArray(int* array, int size) {
    for (int i = 0; i < size; ++i)
        cout << array[i] << " ";
}

void printTimeOfWork1(int sizeOfArray, void functionOfSort(int*, int)) {
    int* array = createArray(sizeOfArray);

    clock_t start = clock();

    functionOfSort(array, sizeOfArray);
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "time of work: " << duration << '\n' << '\n';
}

// Печатает время работы функции сортировки
void printTimeOfWork(int sizeOfArray, void functionOfSort(int*, int, int, int)) {
    int* array = createArray(sizeOfArray);

    clock_t start = clock();
    functionOfSort(array, sizeOfArray/2, sizeOfArray, 16);
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "time of work: " << duration << '\n' << '\n';
}

int main() {

    printTimeOfWork1(10000000, shell_sort);
    printTimeOfWork(10000000, parralel_shell_sort);
    cout << endl;
}