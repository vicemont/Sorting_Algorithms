
#include <stdio.h>
#include <stdlib.h>

// Merges two halves of the array
static void merge(int* num, int left, int right, int* temp)
{
    int mid = (left + right) / 2;
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (num[i] < num[j])
            temp[k++] = num[i++];
        else
            temp[k++] = num[j++];
    }

    while (i <= mid)
        temp[k++] = num[i++];

    while (j <= right)
        temp[k++] = num[j++];

    for (int i = left; i <= right; i++)
        num[i] = temp[i];
}

// Recursively sorts the array
static void mergeSort(int* nums, int left, int right, int* temp)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(nums, left, mid, temp);
        mergeSort(nums, mid + 1, right, temp);

        merge(nums, left, right, temp);
    }
}

// Function called from main.cpp
void mergeSortArray(int* nums, int numsSize)
{
    if (numsSize <= 1)
        return;

    int* temp = (int*)malloc(sizeof(int) * numsSize);

    mergeSort(nums, 0, numsSize - 1, temp);

    free(temp);
}
