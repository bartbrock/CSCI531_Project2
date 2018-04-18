struct numbers
{
	int low;
	int high;
	int a[5000];
};

program QS5000_PROG {
	version QS5000_V1 {
		numbers qsort(numbers)=1;
	}=1;
} = 0x12345678;
