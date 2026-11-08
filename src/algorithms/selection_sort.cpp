
#include <iostream>
using namespace std;

void selectionSort(int* nums, int numsSize)
{
    // Go through each position in the array
    for(int i = 0; i < numsSize - 1; i++) {

        int minIndex = i;

        // Find the smallest element in the unsorted portion
        for(int j = i + 1; j < numsSize; j++) {
            if(nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the smallest element into its correct position
        int temp = nums[i];
        nums[i] = nums[minIndex];
        nums[minIndex] = temp;
    }
}

