
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "Algorithms.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Invalid input.";
        return 1;
    }

    string algorithm = argv[1];
    int selectedSize = stoi(argv[2]);

    ifstream file("test_arrays.txt");

    if (!file.is_open()) {
        cout << "Could not open test_arrays.txt";
        return 1;
    }

    int numberOfTests;
    file >> numberOfTests;

    double totalTime = 0;
    int totalRuns = 0;

    for (int i = 0; i < numberOfTests; i++) {

        string type;
        int size;

        file >> type >> size;

        vector<int> original(size);

        for (int j = 0; j < size; j++) {
            file >> original[j];
        }

        if (size != selectedSize) {
            continue;
        }

        // Run each matching array three times
        for (int run = 0; run < 3; run++) {

            vector<int> nums = original;

            auto start = high_resolution_clock::now();

            if (algorithm == "Heap Sort")
                heapSort(nums.data(), size);

            else if (algorithm == "Quick Sort")
                quickSort(nums.data(), 0, size - 1);

            else if (algorithm == "Median-of-Three Quick Sort")
                quickSortMedian(nums.data(), 0, size - 1);

            else if (algorithm == "Merge Sort")
                mergeSortArray(nums.data(), size);

            else if (algorithm == "Insertion Sort")
                insertionSort(nums.data(), size);

            else if (algorithm == "Selection Sort")
                selectionSort(nums.data(), size);

            else if (algorithm == "Bubble Sort")
                bubbleSort(nums.data(), size);

            else {
                cout << "Unknown algorithm.";
                return 1;
            }

            auto end = high_resolution_clock::now();

            double elapsed =
                duration<double, micro>(end - start).count();

            if (!is_sorted(nums.begin(), nums.end())) {
                cout << "Sorting failed.";
                return 1;
            }

            totalTime += elapsed;
            totalRuns++;
        }
    }

    if (totalRuns == 0) {
        cout << "No test arrays found for this size.";
        return 1;
    }

    double averageMicroseconds = totalTime / totalRuns;
    double averageMilliseconds = averageMicroseconds / 1000.0;

    cout << "Algorithm: " << algorithm << endl;
    cout << "Input Size: " << selectedSize << endl;
    cout << "Arrays Tested: " << totalRuns / 3 << endl;
    cout << "Average Runtime: " << averageMilliseconds << " milliseconds";

    return 0;
}
