
#include <iostream>
using namespace std;

void heapify(int* nums, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the largest among root and children
    if(left < n && nums[left] > nums[largest])
        largest = left;

    if(right < n && nums[right] > nums[largest])
        largest = right;

    // Swap and continue heapifying
    if(largest != i) {
        int temp = nums[i];
        nums[i] = nums[largest];
        nums[largest] = temp;

        heapify(nums, n, largest);
    }
}

void heapSort(int* nums, int numsSize)
{
    // Buid the Max Heap
    for(int i = numsSize/2 - 1; i >= 0; i--)
        heapify(nums, numsSize, i);

    //Extract elements from heap
    for(int i = numsSize - 1; i > 0; i--) {

        // Move largest element to the end
        int temp = nums[0];
        nums[0] = nums[i];
        nums[i] = temp;

        // Restore Max Heap
        heapify(nums, i, 0);
    }
}


