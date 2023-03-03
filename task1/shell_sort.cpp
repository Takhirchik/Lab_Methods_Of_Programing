#include <iostream>
#include <string>

template< class RandomIt>
class Compare {
public:
    static bool less(RandomIt a, RandomIt b) {
        return a > b;
    }
};

class CompareStr {
public:
    static bool less(char* a, char* b) {
        return strcmp(a, b) >= 0;
    }
};

template< class RandomIt, class Compare>
void shell_sort(RandomIt* arr, size_t size)
{
    for (auto d = size / 2; d > 0; d /= 2)
        for (auto i = d; i < size; ++i)
            for (auto j = i - d; j >= 0 && Compare::less(arr[j], arr[j + d]); j -= d) {
                RandomIt temp = arr[j];
                arr[j] = arr[j + d];
                arr[j + d] = temp;
            }

}

template< class RandomIt >
void print_array(const RandomIt* arr, size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}


int main() {
    const size_t n1 = 6;
    int arr1[n1] = { 1, 3, 6, -2, 99, -40 };
    const size_t n2 = 5;
    double arr2[n2] = { 1.9, 7.8, 1.9, 29.8, -1.7 };
    shell_sort<int, Compare<int>>(arr1, n1);
    shell_sort<double, Compare<double>>(arr2, n2);
    print_array(arr1, n1);
    std::cout << std::endl;
    print_array(arr2, n2);
    std::cout << std::endl;
}