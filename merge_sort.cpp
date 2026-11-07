#include<stdio.h>
#include<stdlib.h>
void merge(int *num, int left, int right, int *temp)
{
	int mid = (left+right)/2;
	int i = left;
	int j = mid+1;
	int k = left;
	while(i <= mid && j <= right)
	{
		if(num[i] < num[j])
		temp[k++] = num[i++];
		else
		temp[k++] = num[j++];
	}
	while(i <= mid)
	temp[k++] = num[i++];
	while(j <= right)
	temp[k++] = num[j++];

	for(int i = left; i <= right; i++)
	num[i] = temp[i];
}
void mergeSort(int *nums, int left, int right, int *temp)
{
	if(left < right)
	{
		int mid = (left+right)/2;
		mergeSort(nums, left, mid, temp);
		mergeSort(nums, mid+1, right, temp);
		merge(nums, left, right, temp);
	}
}
void sortArray(int* nums, int numsSize)
{
	int lefts=0;
	int rights=numsSize-1;
	int *temp = (int*)malloc(sizeof(int) * (rights+1));
	mergeSort(nums, lefts, rights, temp);
	for(int i = 0; i <numsSize; i++)
	{
		printf(" %d ", nums[i]);
	}
}
int main()
{
	int arr[5] = {1,2,45,78,9};
	sortArray(arr,5);
}








