
#include <iostream>
using namespace std;

int partition(int* nums, int low, int high)
{
    int pivot = nums[high];
    int i = low - 1;

    // Place elements smaller than pivot on the left
    for(int j = low; j < high; j++) {
        if(nums[j] < pivot) {
            i++;

            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }

    // Place pivot in its correct position
    int temp = nums[i + 1];
    nums[i + 1] = nums[high];
    nums[high] = temp;

    return i + 1;
}

void quickSort(int* nums, int low, int high)
{
    if(low < high) {

        // Partition the array
        int pi = partition(nums, low, high);

        // Recursively sort left and right sides
        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}


