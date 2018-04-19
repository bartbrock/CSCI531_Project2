#pragma once
/* QuickSort Multithreaded */
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<time.h>
#include <sys/time.h>
#include <stdint.h>

#include "qsRPC.h"


#define ZERO 0

// type definition of the thread/rpc parameters
// same as numbers in .h file
//typedef struct arrayParamsStruct{
//	int low;
//	int high;
//	int a[5000];
//} arrayParamsType;

// declare structure variables for global use
numbers arrayParams, arrayParamsLow, arrayParamsHigh;
// initial working array for quicksort
int arr[5000];
// thread id array
pthread_t tid[2];

// A utility function to swap two elements
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* quickSortThread is used to create thread for quick short function
   the parameter structure is passed by pointer
*/
void* quickSortThread(void *arg)
{
	numbers *aP = (numbers *)arg;
	//printf("Enter quickSortThread, aP.a[0]= %d \n", aP->a[0]);
	int low = aP->low;
	int high = aP->high;
	int *arr = aP->a;

	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
	//printf("Exit quickSortThread \n");
	pthread_exit(NULL);
}


/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	//printf("\n");
}

void extractArrayStruct(numbers *params, int arrOld[], int start, int size)
{
	//printf("Enter extractArrayStruct \n");
	for (int i = start; i < size+start; i++)
		{
			params->a[i-start] = arrOld[i];
			//printf("i= %d, arrOld= %d, arrayParms= %d, address= %d \n", i, arrOld[i], params->a[i-start], &params->a[i-start]);
			
		}
	params->low = 0;
	params->high = size-1;
}

void extractArray(int arrNew[], int arrOld[], int start, int size)
{
	//printf("Enter extractArray \n");
	for (int i = start; i < size+start; i++)
		{
			//printf("i= %d, start= %d, size= %d, arrOld= %d \n", i, start, size, arrOld[i]);
			arrNew[i-start] = arrOld[i];
		}
}

bool isDupElement(int testNum, int aSize)
{
	bool result = false;
	for (int i = 0; i < aSize; i++)
		{
			if (arr[i] == testNum) result = true;
		}
	return result;
}

void createRandomArray(int size) 
{
	int element;
	for (int pos = 0; pos < size; pos++ ) 
	{
		element = rand() % 10001;
		if (isDupElement(element, pos))
			pos--;
		else
			arr[pos] = element;
        }
}

uint64_t get_posix_clock_time()
{
	struct timespec ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
		return (uint64_t)(ts.tv_sec * 1000000000 + ts.tv_nsec);
	else
		return 0;
}
