/* QuickSort Multithreaded */
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define ZERO 0

// type definition of the thread/rpc parameters
typedef struct arrayParamsStruct{
	int low;
	int high;
	int a[100];
} arrayParamsType;

// declare structure variables for global use
arrayParamsType arrayParams, arrayParamsLow, arrayParamsHigh;

pthread_t tid[2];
int ret1,ret2;

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
	arrayParamsType *aP = (arrayParamsType *)arg;
	printf("Enter quickSortThread, aP.a[0]= %d \n", aP->a[0]);
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
	printf("Exit quickSortThread \n");
	pthread_exit(NULL);
}


/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void extractArrayStruct(arrayParamsType *params, int arrOld[], int start, int size)
{
	printf("Enter extractArrayStruct \n");
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
	printf("Enter extractArray \n");
	for (int i = start; i < size+start; i++)
		{
			//printf("i= %d, start= %d, size= %d, arrOld= %d \n", i, start, size, arrOld[i]);
			arrNew[i-start] = arrOld[i];
		}
}
// Driver program to test above functions
int main()
{
	
	int err = 0;

	int arrLow[15], arrHigh[15], arr[] = {10, 7, 8, 88, 9, 1, 99, 5, 32, 29, 2, 104, 11};
	int n = sizeof(arr)/sizeof(arr[0]);
	printf("Original array: \n");
	printArray(arr, n);
	int pivot = partition(arr, 0, n-1);
	int arrHighSize = n - pivot;

	printf("pivotIndex = %d, n = %d arrHighSize = %d \n", pivot, n, arrHighSize);

	// create sub arrays
	extractArrayStruct(&arrayParamsLow, arr, ZERO, pivot);
	extractArrayStruct(&arrayParamsHigh, arr, pivot, arrHighSize);
	printArray(arrayParamsLow.a, pivot);
	printArray(arrayParamsHigh.a, arrHighSize);

	//send lower portion to remote
	if (pthread_create(&(tid[0]), NULL, &quickSortThread,(void *)&arrayParamsLow))
                  printf("\ncan't create thread :[%s] \n", strerror(err));
        //send upper portion to thread
	if (pthread_create(&(tid[1]), NULL, &quickSortThread,(void *)&arrayParamsHigh))
                  printf("\ncan't create thread :[%s] \n", strerror(err));
        
	// process upper portion
	//quickSort(arrHigh, 0, arrHighSize-1);
	//wait for thread to complete
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("Sorted arrayParamsLow: \n");
	printArray(arrayParamsLow.a, arrayParamsLow.high+1);
	printf("Sorted arrayParamsHigh: \n");
	printArray(arrayParamsHigh.a, arrHighSize);
	return 0;
}
