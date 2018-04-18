struct numbers
{
        int low;
        int high;
        int a[5000];
};

program QSRPC_PROG {
        version QSRPC_V1 {
                numbers qsort(numbers)=1;
        }=1;
} = 0x12345678;
