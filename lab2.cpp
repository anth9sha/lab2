

#include <iostream>
#include <time.h>
#include <chrono>
using namespace std;
using namespace chrono;

const int N = 100;
int unsorted[N], sorted[N];

time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start_timer, end_timer;
nanoseconds result;

int binarySearch(int* arr, int value, int start, int end) {
    if (end >= start) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == value) {
            return mid;
        }

        if (arr[mid] > value) {
            return binarySearch(arr, value, start, mid - 1);
        }
        return binarySearch(arr, value, mid + 1, end);
    }

    return -1;
}

void quicksort(int* arr, int begin, int end) {
    int b = begin;
    int e = end;
    int mid = arr[(b + e) / 2];
    while (b < e) {
        while (arr[b] < mid) b++;
        while (arr[e] > mid) e--;
        if (b <= e) {
            swap(arr[b], arr[e]);
            b++;
            e--;
        }
    }
    if (begin < e) quicksort(arr, begin, e);
    if (e < end) quicksort(arr, b, end);
}

void insertionBinary(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        int key = arr[i];
        int lo = 0, hi = i - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (key < arr[mid]) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        for (int j = i; j > lo; --j) {
            arr[j] = arr[j - 1];
        }
        arr[lo] = key;
    }
}



void task1() {
    for (int i = 0; i < N; ++i) {
        unsorted[i] = rand() % 199 - 99;
        sorted[i] = unsorted[i];
    }
}

void task2() {
    start_timer = steady_clock::now();
    quicksort(sorted, 0, N - 1);
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "Время, затраченное на сортировку: " << result.count();
}

void task3() {
    quicksort(sorted, 0, N - 1);
    int min = sorted[0], max = sorted[0];
    start_timer = steady_clock::now();
    for (int i = 1; i < N; ++i) {
        if (min > unsorted[i]) {
            min = unsorted[i];
        }
        if (max < unsorted[i]) {
            max = unsorted[i];
        }
    }
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "Время поиска в неотсортированном массиве: " << result.count() << "\n";

    start_timer = steady_clock::now();
    min = sorted[0];
    max = sorted[N - 1];
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "Время поиска в отсортированном массиве: " << result.count();
}

void task4() {
    quicksort(sorted, 0, N - 1);
    int min = sorted[0];
    int max = sorted[N - 1];
    int average = (min + max) / 2;
    cout << "Среднее значение: " << average << "\n" << "\n";
    int count = 0;
    cout << "Хранится под индексами в неотсортированном массиве: ";
    start_timer = steady_clock::now();
    for (int i = 0; i < N; ++i) {
        if (unsorted[i] == average) {
            cout << i << " ";
            count++;
        }
    }
    if (count == 0) {
        cout << "Элемент отсутствует";
    }
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "\n" << "Количество индексов элементов: " << count << "\n";
    cout << "Время поиска в неотсортированном массиве: " << result.count() << "\n" << endl;

    count = 0;
    cout << "Хранится под индексами в отсортированном массиве: ";
    start_timer = steady_clock::now();
    for (int i = binarySearch(sorted, average, 0, N - 1); i < N; ++i, ++count) {
        if (sorted[i] != average) {
            break;
        }
        cout << i << " ";
    }
    if (count == 0) {
        cout << "Элемент отсутствует";
    }
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "\n" << "Количество индексов элементов: " << count << "\n";
    cout << "Время поиска в отсортированном массиве: " << result.count() << endl;
}

void task5() {
    int a, count = 0;
    cout << "Введите число a:" << "\n";
    cin >> a;
    quicksort(sorted, 0, N - 1);
    count = binarySearch(sorted, a, 0, N - 1);
    if (count == -1 || count == 0) {
        cout << "Элементов меньше a не найдено";
    }
    else {
        cout << "Количество элементов меньше a: " << count;
    }
}

void task6() {
    int b, count = 0, scount = 0;
    cout << "Введите число b:" << "\n";
    cin >> b;
    quicksort(sorted, 0, N - 1);
    for (int i = 0; i < N; ++i) {
        if (sorted[i] > b) {
            count++;
        }
    }
    cout << "Количество элементов больше b: " << count;
}

void task7() {
    quicksort(sorted, 0, N - 1);
    int a;
    cout << "Введите число: " << "\n";
    cin >> a;
    start_timer = steady_clock::now();
    int resultBS = binarySearch(sorted, a, 0, N - 1);
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    if (resultBS == -1) {
        cout << "Элемент отсутствует" << endl;
    }
    else {
        cout << "Номер числа в маcсиве: " << resultBS << endl;
    }
    cout << "Время поиска методом бинарного поиска: " << result.count() << endl;

    start_timer = steady_clock::now();
    for (int i = 0; i < N; ++i) {
        if (sorted[i] == a) {
            cout << "Номер числа в маcсиве: " << i << endl;
            break;
        }
    }
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "Время поиска методом перебора: " << result.count() << endl;
}

void task8() {
    cout << "Неотсортированный массив: ";
    for (int i = 0; i < N; ++i) {
        cout << unsorted[i] << " ";
    }
    int f, s;
    cout << "\n" << "\n" << "Введите индексы элементов, которые хотите поменять: " << "\n";
    cin >> f >> s;
    start_timer = steady_clock::now();
    swap(unsorted[f], unsorted[s]);
    end_timer = steady_clock::now();
    result = duration_cast<nanoseconds>(end_timer - start_timer);
    cout << "\n" << "Время смены элементов: " << result.count() << "\n " << endl << "Новый массив: ";
    for (int i = 0; i < N; ++i) {
        cout << unsorted[i] << " ";
    }
}

int main()
{
    setlocale(0, "");
    srand(time(NULL));
    task1();
    int choosetask;
    do
    {
        cout << "Выберите задание, которое хотите выполнить: " << "\n";
        cin >> choosetask;
        switch (choosetask){

        case 1:
            cout << "\n" << "Задание №1" << "\n";
            task1();
            cout << "Неотсортированный массив: ";
            for (int i = 0; i < N; ++i) {
                cout << unsorted[i] << " ";
            }
            cout << "\n" << endl;
            break;

        case 2:
            cout << "\n" << "Задание №2" << "\n";
            task2();
            cout << "\n" << "Отсортированный массив: ";
            for (int i = 0; i < N; ++i) {
                cout << sorted[i] << " ";
            }
            cout << "\n" << endl;
            break;

        case 3:
            cout << "\n" << "Задание №3" << "\n";
            task3();
            cout << "\n" << endl;
            break;

        case 4:
            cout << "\n" << "Задание №4" << "\n";
            task4();
            cout << "\n" << endl;
            break;

        case 5:
            cout << "\n" << "Задание №5" << "\n";
            task5();
            cout << "\n" << endl;
            break;

        case 6:
            cout << "\n" << "Задание №6" << "\n";
            task6();
            cout << "\n" << endl;
            break;

        case 7:
            cout << "\n" << "Задание №7" << "\n";
            task7();
            cout << "\n" << endl;
            break;

        case 8:
            cout << "\n" << "Задание №8" << "\n";
            task8();
            cout << "\n" << endl;
            break;

        case 9:
            int sortedbyins[N];
            for (int i = 0; i < N; ++i) {
                sortedbyins[i] = unsorted[i];
            }
            start_timer = steady_clock::now();
            insertionBinary(sortedbyins, N);
            end_timer = steady_clock::now();
            result = duration_cast<nanoseconds>(end_timer - start_timer);
            cout << "Время, затраченное на сортировку: " << result.count() << "\n";
            cout << "Полученный массив: ";
            for (int i = 0; i < N; ++i) {
                cout << sortedbyins[i] << " ";
            }
            cout << endl;
            break;

        case 0:
            cout << "\n" << "Выход.";
            break;

        default:
            cout << "Некорректный ввод" << endl;
            break;
        }
    } while (choosetask != 0);
    return 0;
}

