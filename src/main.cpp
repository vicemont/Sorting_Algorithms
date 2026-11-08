
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <utility>

#include "Algorithms.h"

using namespace std;

const int RUNS = 3;

struct TestCase
{
    string type;
    vector<int> data;
};

// Runs one algorithm several times and returns its average runtime.
// Each run starts with a fresh copy of the original array.
template <typename SortFunction>
double benchmark(const vector<int>& original, SortFunction sortFunction)
{
    double totalTime = 0.0;

    for (int run = 0; run < RUNS; run++)
    {
        vector<int> nums = original;

        auto start = chrono::high_resolution_clock::now();
        sortFunction(nums.data(), static_cast<int>(nums.size()));
        auto end = chrono::high_resolution_clock::now();

        if (!is_sorted(nums.begin(), nums.end()))
        {
            return -1.0;
        }

        chrono::duration<double, micro> elapsed = end - start;
        totalTime += elapsed.count();
    }

    return totalTime / RUNS;
}

// Reads all test arrays from test_arrays.txt.
bool loadTestCases(const string& filename, vector<TestCase>& testCases)
{
    ifstream inputFile(filename);

    if (!inputFile)
    {
        cerr << "Error: Could not open " << filename << endl;
        return false;
    }

    int numberOfCases;

    if (!(inputFile >> numberOfCases) || numberOfCases < 0)
    {
        cerr << "Error: Invalid test case count in " << filename << endl;
        return false;
    }

    for (int i = 0; i < numberOfCases; i++)
    {
        string type;
        int size;

        if (!(inputFile >> type >> size) || size < 0)
        {
            cerr << "Error: Invalid test case information at case "
                 << (i + 1) << endl;
            return false;
        }

        vector<int> values(size);

        for (int j = 0; j < size; j++)
        {
            if (!(inputFile >> values[j]))
            {
                cerr << "Error: Not enough array values in test case "
                     << (i + 1) << endl;
                return false;
            }
        }

        testCases.push_back({type, values});
    }

    return true;
}

// Runs all seven sorting algorithms on one test array.
vector<pair<string, double>> runAlgorithms(const vector<int>& arr)
{
    vector<pair<string, double>> results;

    results.push_back({
        "Heap Sort",
        benchmark(arr, [](int* nums, int n) {
            heapSort(nums, n);
        })
    });

    results.push_back({
        "Quick Sort",
        benchmark(arr, [](int* nums, int n) {
            if (n > 1) quickSort(nums, 0, n - 1);
        })
    });

    results.push_back({
        "Median-of-Three Quick Sort",
        benchmark(arr, [](int* nums, int n) {
            if (n > 1) quickSortMedian(nums, 0, n - 1);
        })
    });

    results.push_back({
        "Merge Sort",
        benchmark(arr, [](int* nums, int n) {
            mergeSortArray(nums, n);
        })
    });

    results.push_back({
        "Insertion Sort",
        benchmark(arr, [](int* nums, int n) {
            insertionSort(nums, n);
        })
    });

    results.push_back({
        "Selection Sort",
        benchmark(arr, [](int* nums, int n) {
            selectionSort(nums, n);
        })
    });

    results.push_back({
        "Bubble Sort",
        benchmark(arr, [](int* nums, int n) {
            bubbleSort(nums, n);
        })
    });

    return results;
}

// Calculates average runtime across all test arrays of a given size and type.
void testGroup(const vector<TestCase>& testCases, int size, const string& type)
{
    vector<pair<string, double>> totals;
    vector<int> validCounts;

    int numberOfCases = 0;

    for (const TestCase& test : testCases)
    {
        if (static_cast<int>(test.data.size()) != size || test.type != type)
        {
            continue;
        }

        numberOfCases++;

        vector<pair<string, double>> results = runAlgorithms(test.data);

        if (totals.empty())
        {
            for (const auto& result : results)
            {
                totals.push_back({result.first, 0.0});
                validCounts.push_back(0);
            }
        }

        for (size_t i = 0; i < results.size(); i++)
        {
            if (results[i].second >= 0.0)
            {
                totals[i].second += results[i].second;
                validCounts[i]++;
            }
        }
    }

    if (numberOfCases == 0)
    {
        return;
    }

    cout << "\n====================================================\n";
    cout << "Input Type: " << type << " | Array Size: " << size << '\n';
    cout << "Number of test arrays: " << numberOfCases << '\n';
    cout << "Average runtime (" << RUNS << " timing runs per array)\n";
    cout << "----------------------------------------------------\n";

    cout << left << setw(32) << "Sorting Algorithm"
         << right << setw(18) << "Average (microsec)" << '\n';

    cout << "----------------------------------------------------\n";

    double fastestTime = -1.0;
    string fastestAlgorithm = "None";

    for (size_t i = 0; i < totals.size(); i++)
    {
        cout << left << setw(32) << totals[i].first;

        if (validCounts[i] > 0)
        {
            double average = totals[i].second / validCounts[i];

            cout << right << setw(18) << fixed << setprecision(2)
                 << average;

            if (fastestTime < 0.0 || average < fastestTime)
            {
                fastestTime = average;
                fastestAlgorithm = totals[i].first;
            }
        }
        else
        {
            cout << right << setw(18) << "FAILED";
        }

        cout << '\n';
    }

    cout << "----------------------------------------------------\n";

    if (fastestTime >= 0.0)
    {
        cout << "Fastest Algorithm: " << fastestAlgorithm
             << " (" << fixed << setprecision(2)
             << fastestTime << " microseconds)\n";
    }
    else
    {
        cout << "No algorithm produced a valid sorted result.\n";
    }
}

int main()
{
    vector<TestCase> testCases;

    // Load the test arrays from the external text file.
    if (!loadTestCases("test_arrays.txt", testCases))
    {
        return 1;
    }

    cout << "SORTING ALGORITHM BENCHMARK\n";
    cout << "Loaded " << testCases.size()
         << " test arrays from test_arrays.txt\n";

    vector<int> sizes = {100, 500, 1000, 2000};

    vector<string> types = {
        "Random",
        "AlreadySorted",
        "ReverseSorted",
        "Duplicates"
    };

    // Run benchmarks for every array size and input type.
    for (int size : sizes)
    {
        for (const string& type : types)
        {
            testGroup(testCases, size, type);
        }
    }

    cout << "\nBenchmark completed.\n";

    return 0;
}
