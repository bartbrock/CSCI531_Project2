#include "quicksort.h"

/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

numbers *
qsrpc_prog_1(char *host, numbers *params)
{
	CLIENT *clnt;
	numbers  *result_1;
	numbers* qsort_1_arg = params;

#ifndef	DEBUG
	// setup remote connection
	clnt = clnt_create (host, QSRPC_PROG, QSRPC_V1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	
	// call to remote
	result_1 = qsort_1(qsort_1_arg, clnt);
	if (result_1 == (numbers *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	// get return values from result
	// 
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	return result_1;
}


int
main (int argc, char *argv[])
{
	char *host;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	int n = 0, err = 0;
	int arraySize100 = 100, arraySize1000 = 1000, arraySize5000 = 5000;
	int pivot = 0;
	int arrHighSize = 0;

	// set up timers 
	srand(time(0));	
 	time_t s100, e100, s1000, e1000, s5000, e5000;   // start and end times for all runs
	uint64_t start_time_value1, end_time_value1, start_time_value2, end_time_value2, start_time_value3, end_time_value3;
	uint64_t time_diff1, time_diff2, time_diff3;

	/*******************************************************************************
			Trial #1  Array size = 100
	********************************************************************************/
	printf("\n************** Start Trial 1 Array Size = 100 ************** \n");
	// mark start time
        time(&s100);		
	start_time_value1 = get_posix_clock_time();
	
	// set up array 
	n = arraySize100;
	createRandomArray(n);

	// start quicksort process
	//printf("\nOriginal array, size= %d \n", n);
	//printArray(arr, n);

	// divide array into two
	pivot = partition(arr, 0, n-1);
	arrHighSize = n - pivot;

	printf("\nPivot Vaule = %d, Low Array Size = %d, High Array Size = %d \n", arr[pivot], pivot, arrHighSize);

	// create sub arrays
	extractArrayStruct(&arrayParamsLow, arr, ZERO, pivot);
	extractArrayStruct(&arrayParamsHigh, arr, pivot, arrHighSize);
	//printf("\npre-sorted arrayParamsLow: \n");
	//printArray(arrayParamsLow.a, pivot);
	//printf("pre-sorted arrayParamsHigh: \n");
	//printArray(arrayParamsHigh.a, arrHighSize);

        //send upper portion to thread
	if (pthread_create(&(tid[1]), NULL, &quickSortThread,(void *)&arrayParamsHigh))
                  printf("\ncan't create thread :[%s] \n", strerror(err));
 
	//send lower portion to remote
	// call to rpc stub ++++++++++++
	arrayParams = *(qsrpc_prog_1(host, &arrayParamsLow));

	//if (pthread_create(&(tid[0]), NULL, &quickSortThread,(void *)&arrayParamsLow))
        //          printf("\ncan't create thread :[%s] \n", strerror(err));

       
	// process upper portion
	//quickSort(arrHigh, 0, arrHighSize-1);

	//wait for thread to complete
	//pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("\nSorted Array\n");
	printArray(arrayParams.a, arrayParamsLow.high + 1);
	printArray(arrayParamsHigh.a, arrHighSize);

	// mark end time
	time(&e100);	
	end_time_value1 = get_posix_clock_time();
	time_diff1 = end_time_value1 - start_time_value1;
	//printf("\nStart time: %s\n", ctime(&s100));
	//printf("End time : %s\n", ctime(&e100));
	//printf("Runtime in seconds : %f \n", difftime(e100, s100));
	printf("Runtime in milliseconds : %f \n", (double)time_diff1 / 1000000);
	// ---------------------------- End Run # 1 ---------------------------------
	printf("\n--------------------- End Run # 1 -------------------- \n\n");

	/*******************************************************************************
			Trial #2  Array size = 1000
	********************************************************************************/
	printf("\n************** Start Trial 2 Array Size = 1000 ************** \n");
	// mark start time
	time(&s1000);
	start_time_value2 = get_posix_clock_time();
	
	// set up array 
	n = arraySize1000;
	createRandomArray(n);

	// start quicksort process
	//printf("\nOriginal array, size= %d \n", n);
	//printArray(arr, n);

	// divide array into two
	pivot = partition(arr, 0, n - 1);
	arrHighSize = n - pivot;

	printf("\nPivot Vaule = %d, Low Array Size = %d, High Array Size = %d \n", arr[pivot], pivot, arrHighSize);

	// create sub arrays
	extractArrayStruct(&arrayParamsLow, arr, ZERO, pivot);
	extractArrayStruct(&arrayParamsHigh, arr, pivot, arrHighSize);
	//printf("\npre-sorted arrayParamsLow: \n");
	//printArray(arrayParamsLow.a, pivot);
	//printf("pre-sorted arrayParamsHigh: \n");
	//printArray(arrayParamsHigh.a, arrHighSize);

	//send upper portion to thread
	if (pthread_create(&(tid[1]), NULL, &quickSortThread, (void *)&arrayParamsHigh))
		printf("\ncan't create thread :[%s] \n", strerror(err));

	//send lower portion to remote
	// call to rpc stub ++++++++++++
	arrayParams = *(qsrpc_prog_1(host, &arrayParamsLow));

	//if (pthread_create(&(tid[0]), NULL, &quickSortThread,(void *)&arrayParamsLow))
	//          printf("\ncan't create thread :[%s] \n", strerror(err));


	// process upper portion
	//quickSort(arrHigh, 0, arrHighSize-1);

	//wait for thread to complete
	//pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("\nSorted Array\n");
	printArray(arrayParams.a, arrayParamsLow.high + 1);
	printArray(arrayParamsHigh.a, arrHighSize);

	// mark end time
	time(&e1000);
	end_time_value2 = get_posix_clock_time();
	time_diff2 = end_time_value2 - start_time_value2;
	//printf("\nStart time: %s\n", ctime(&s1000));
	//printf("End time : %s\n", ctime(&e1000));
	//printf("Runtime in seconds : %f \n", difftime(e1000, s1000));
	printf("Runtime in milliseconds : %f \n", (double)time_diff2 / 1000000);
	// ---------------------------- End Run # 2 ---------------------------------
	printf("\n--------------------- End Run # 2 -------------------- \n\n");
	
	/*******************************************************************************
				Trial #3  Array size = 5000
	********************************************************************************/
	printf("\n************** Start Trial 3 Array Size = 5000 ************** \n");
	// mark start time
	time(&s5000);
	start_time_value3 = get_posix_clock_time();

	// set up array 
	n = arraySize5000;
	createRandomArray(n);

	// start quicksort process
	//printf("\nOriginal array, size= %d \n", n);
	//printArray(arr, n);

	// divide array into two
	pivot = partition(arr, 0, n - 1);
	arrHighSize = n - pivot;

	printf("\nPivot Vaule = %d, Low Array Size = %d, High Array Size = %d \n", arr[pivot], pivot, arrHighSize);

	// create sub arrays
	extractArrayStruct(&arrayParamsLow, arr, ZERO, pivot);
	extractArrayStruct(&arrayParamsHigh, arr, pivot, arrHighSize);
	//printf("\npre-sorted arrayParamsLow: \n");
	//printArray(arrayParamsLow.a, pivot);
	//printf("pre-sorted arrayParamsHigh: \n");
	//printArray(arrayParamsHigh.a, arrHighSize);

	//send upper portion to thread
	if (pthread_create(&(tid[1]), NULL, &quickSortThread, (void *)&arrayParamsHigh))
		printf("\ncan't create thread :[%s] \n", strerror(err));

	//send lower portion to remote
	// call to rpc stub ++++++++++++
	arrayParams = *(qsrpc_prog_1(host, &arrayParamsLow));

	//if (pthread_create(&(tid[0]), NULL, &quickSortThread,(void *)&arrayParamsLow))
	//          printf("\ncan't create thread :[%s] \n", strerror(err));


	// process upper portion
	//quickSort(arrHigh, 0, arrHighSize-1);

	//wait for thread to complete
	//pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("\nSorted Array\n");
	printArray(arrayParams.a, arrayParamsLow.high + 1);
	printArray(arrayParamsHigh.a, arrHighSize);

	// mark end time
	time(&e5000);
	end_time_value3 = get_posix_clock_time();
	time_diff3 = end_time_value3 - start_time_value3;
	//printf("\nStart time: %s\n", ctime(&s5000));
	//printf("End time : %s\n", ctime(&e5000));
	//printf("Runtime in seconds : %f \n", difftime(e5000, s5000));
	printf("Runtime in milliseconds : %f \n", (double)time_diff3 / 1000000);
	// ---------------------------- End Run # 3 ---------------------------------
	printf("\n--------------------- End Run # 3 -------------------- \n\n");


	// print out time results for all trials
	printf("TRIAL 1, 100 elements \n");
	printf("Runtime in milliseconds : %f \n\n", (double)time_diff1 / 1000000);
	printf("TRIAL 2, 1000 elements \n");
	printf("Runtime in milliseconds : %f \n\n", (double)time_diff2 / 1000000);
	printf("TRIAL 3, 5000 elements \n");
	printf("Runtime in milliseconds : %f \n\n", (double)time_diff3 / 1000000);

exit (0);
}
