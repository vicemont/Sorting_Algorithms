
#include <iostream>
using namespace std;

int medianPartition(int* nums, int low, int high)
{
    int mid = (low + high) / 2;

    //Find the median of first, middle, and last
    if(nums[low] > nums[mid]) {
        int temp = nums[low];
        nums[low] = nums[mid];
        nums[mid] = temp;
    }

    if(nums[low] > nums[high]) {
        int temp = nums[low];
        nums[low] = nums[high];
        nums[high] = temp;
    }

    if(nums[mid] > nums[high]) {
        int temp = nums[mid];
        nums[mid] = nums[high];
        nums[high] = temp;
    }

    // Move median pivot to the end
    int temp = nums[mid];
    nums[mid] = nums[high];
    nums[high] = temp;

    int pivot = nums[high];
    int i = low - 1;

    //Partition the array
    for(int j = low; j < high; j++) {
        if(nums[j] < pivot) {
            i++;

            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }

    // Place pivot in correct position
    temp = nums[i + 1];
    nums[i + 1] = nums[high];
    nums[high] = temp;

    return i + 1;
}

void quickSortMedian(int* nums, int low, int high)
{
    if(low < high) {

        //Partition the array
        int pi = medianPartition(nums, low, high);

        //Recursively sort left and right sides
        quickSortMedian(nums, low, pi - 1);
        quickSortMedian(nums, pi + 1, high);
    }
}

