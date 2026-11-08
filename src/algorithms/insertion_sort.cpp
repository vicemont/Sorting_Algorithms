
#include <iostream>
using namespace std;

void insertionSort(int* nums, int numsSize)
{
    //Starts with the second element
    for(int i = 1; i < numsSize; i++) {

        int key = nums[i];
        int j = i - 1;

        // Move larger elements one position to the right
        while(j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }

        // Insert key into its correct position
        nums[j + 1] = key;
    }
}


