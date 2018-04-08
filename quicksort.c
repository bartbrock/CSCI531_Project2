/* QuickSort Multithreaded */
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define ZERO 0

pthread_t tid[2];
int ret1,ret2;

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    for(i=0; i<(0xFFFFFFFF);i++);

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing done\n");
        ret1  = 100;
        pthread_exit(&ret1);
    }
    else
    {
        printf("\n Second thread processing done\n");
        ret2  = 200;
        pthread_exit(&ret2);
    }

    return NULL;
}
/*
int main(void)
{
    int i = 0;  
    int err;
    int *ptr[2];

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    pthread_join(tid[0], (void**)&(ptr[0]));
    pthread_join(tid[1], (void**)&(ptr[1]));

    printf("\n return value from first thread is [%d]\n", *ptr[0]);
    printf("\n return value from second thread is [%d]\n", *ptr[1]);

    return 0;
}
*/

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

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void extractArray(int arr[], int arr2[], int start, int size)
{
	for (int i = start; i < size; i++)
		{
			arr[i-start] = arr2[i];
		}
}
// Driver program to test above functions
int main()
{
	int arrLow[], arrHigh[], arr[] = {10, 7, 8, 88, 9, 1, 99, 5, 32, 29, 2, 104, 11};
	int n = sizeof(arr)/sizeof(arr[0]);
	int pivot = partition(arr, 0, n-1);
	// create sub arrays
	int arrHighSize = n - pivot;
	extractArray(arrHigh, arr, pivot, arrHighSize);
	extractArray(arrLow, arr, ZERO, pivot-1);

	//send upper portion to remote
	//if ( pthread_create(&(tid[i]), NULL, &doSomeThing, NULL))
          //          printf("\ncan't create thread :[%s]", strerror(err));
        quickSort(arr, 0, pivot-1);
	//wait for thread to complete
	//pthread_join();
	printf("Sorted array: \n");
	printArray(arr, n);
	return 0;
}

