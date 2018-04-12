struct numbers
{
	int low;
	int high;
	int a[100];
};

program GS100_PROG {
	version GS100_V1 {
		numbers qsort(numbers)=1;
	}=1;
} = 0x12345678;
