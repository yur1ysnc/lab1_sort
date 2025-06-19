#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

struct Apartment {
    int building_number;
    int apartment_number;
    int room_count;
    double total_area;
    std::string owner_name;
    int residents;

    bool operator>(const Apartment& other) const {
        if (total_area != other.total_area)
            return total_area < other.total_area; // по убыванию
        if (building_number != other.building_number)
            return building_number > other.building_number;
        if (apartment_number != other.apartment_number)
            return apartment_number > other.apartment_number;
        return owner_name > other.owner_name;
    }

    bool operator<(const Apartment& other) const {
        return other > *this;
    }

    bool operator<=(const Apartment& other) const {
        return !(*this > other);
    }

    bool operator>=(const Apartment& other) const {
        return !(*this < other);
    }
};
// Сортировка пузырьком
template<class T>
void bubbleSort(T a[], long size) {
    for (long i = 0; i < size - 1; ++i) {
        for (long j = 0; j < size - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

// Сортировка вставками
template<class T>
void insertionSort(T a[], long size) {
    for (long i = 1; i < size; i++) {
        T key = a[i];
        long j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

template<class T> void quickSortR(T* a, long N) {
    long i = 0, j = N - 1;
    T p = a[N / 2], x;
    do {
        while (a[i] < p) i++;
        while (a[j] > p) j--;
        if (i <= j) {
            x = a[i]; a[i] = a[j]; a[j] = x;
            i++; j--;
        }
    } while (i <= j);

    if (j > 0) quickSortR(a, j + 1);
    if (N > i) quickSortR(a + i, N - i);
}

std::vector<Apartment> data_in(const std::string& filename) {
    std::vector<Apartment> data;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        Apartment apt;
        std::string field;

        std::getline(ss, field, ','); apt.building_number = std::stoi(field);
        std::getline(ss, field, ','); apt.apartment_number = std::stoi(field);
        std::getline(ss, field, ','); apt.room_count = std::stoi(field);
        std::getline(ss, field, ','); apt.total_area = std::stod(field);
        std::getline(ss, apt.owner_name, ',');
        std::getline(ss, field); apt.residents = std::stoi(field);

        data.push_back(apt);
    }
    return data;
}

void data_out(const std::string& filename, Apartment arr[], long size) {
    std::ofstream outFile(filename);
    for (long i = 0; i < size; i++) {
        outFile << arr[i].building_number << ","
                << arr[i].apartment_number << ","
                << arr[i].room_count << ","
                << arr[i].total_area << ","
                << arr[i].owner_name << ","
                << arr[i].residents << "\n";
    }
    outFile.close();
}

int main() {
    std::string filenames[] = {
        "apartments_100.txt", "apartments_1000.txt", "apartments_5000.txt",
        "apartments_10000.txt", "apartments_20000.txt", "apartments_30000.txt",
        "apartments_50000.txt", "apartments_70000.txt", "apartments_90000.txt",
        "apartments_100000.txt", 
    };

    for (const auto& fname : filenames) {
        std::vector<Apartment> vec = data_in("in_data/" + fname);
        if (vec.empty()) continue;

        long size = vec.size();
        Apartment* baseArray = new Apartment[size];
        for (long i = 0; i < size; i++) baseArray[i] = vec[i];

        // Пузырьковая

        Apartment* bubbleArr = new Apartment[size];
        std::copy(baseArray, baseArray + size, bubbleArr);
        auto start = std::chrono::high_resolution_clock::now();
        bubbleSort(bubbleArr, size);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << fname << " | Bubble: " << std::chrono::duration<double>(end - start).count() << " сек\n";
        data_out("out_data/Sorted_bubble_" + fname, bubbleArr, size);
        delete[] bubbleArr;

        // Вставки
        Apartment* insertArr = new Apartment[size];
        std::copy(baseArray, baseArray + size, insertArr);
        start = std::chrono::high_resolution_clock::now();
        insertionSort(insertArr, size);
        end = std::chrono::high_resolution_clock::now();
        std::cout << fname << " | Insertion: " << std::chrono::duration<double>(end - start).count() << " сек\n";
        data_out("out_data/Sorted_insertion_" + fname, insertArr, size);
        delete[] insertArr;

        // Быстрая
        Apartment* quickArr = new Apartment[size];
        std::copy(baseArray, baseArray + size, quickArr);
        start = std::chrono::high_resolution_clock::now();
        quickSortR(quickArr, size);
        end = std::chrono::high_resolution_clock::now();
        std::cout << fname << " | QuickSort: " << std::chrono::duration<double>(end - start).count() << " сек\n";
        data_out("out_data/Sorted_quick_" + fname, quickArr, size);
        delete[] quickArr;

        // std::sort
        Apartment* stdArr = new Apartment[size];
        std::copy(baseArray, baseArray + size, stdArr);
        start = std::chrono::high_resolution_clock::now();
        std::sort(stdArr, stdArr + size);
        end = std::chrono::high_resolution_clock::now();
        std::cout << fname << " | std::sort: " << std::chrono::duration<double>(end - start).count() << " сек\n";
        delete[] stdArr;

        delete[] baseArray;
    }

    return 0;
}