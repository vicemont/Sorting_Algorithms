
#include <iostream>
using namespace std;

void bubbleSort(int* nums, int numsSize)
{
    //Go through the array multiple times
    for(int i = 0; i < numsSize - 1; i++) {

        // Compare adjacent elements
        for(int j = 0; j < numsSize - i - 1; j++) {

            //Swap if elements are in the wrong order
            if(nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

