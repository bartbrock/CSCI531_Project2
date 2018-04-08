struct numbers
{
	int a[100];
};

program ADD_PROG {
	version ADD_V1 {
		numbers print(numbers)=1;
	}=1;
} = 0x12345678;
