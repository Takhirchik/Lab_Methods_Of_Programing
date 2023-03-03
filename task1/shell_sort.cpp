#include <iostream>

template < class RandomIt >
void my_swap(RandomIt& first, RandomIt& second) //T - тип, указанный в параметре шаблона
{
    RandomIt temp(first); //временная переменная должна быть того же типа, что и параметры
    first = second;
    second = temp;
}

template< class RandomIt >
void shell_sort(RandomIt* arr, size_t size)
{
    for (auto d = size / 2; d > 0; d /= 2)
        //нужен цикл для first = a[0..d-1]
        for (auto i = d; i < size; ++i)
            for (auto j = i - d; j >= 0 && (arr[j] > arr[j + d]); j -= d) {
                RandomIt temp = arr[j];
                arr[j] = arr[j + d];
                arr[j + d] = temp;
            }

}

template< class RandomIt >
void print_array(const RandomIt * arr, size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}


int main() {
    const size_t n = 6;
    int arr[n] = { 1, 3, 6, -2, 99, -40 };
    shell_sort(arr, n);
    print_array(arr, n);
}
