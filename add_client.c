/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "add.h"


void
add_prog_1(char *host)
{
	CLIENT *clnt;
	numbers  *result_1;
	numbers  print_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, ADD_PROG, ADD_V1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	printf("Generating data..");
	for (int i=1;i<100;i++)
	{
		print_1_arg.a[i]=i+10;
		printf("-%d ", print_1_arg.a[i]);
	}
	printf("Connecting... \n");
	printf("Receiving data.. \n");
	result_1 = print_1(&print_1_arg, clnt);
	if (result_1 == (numbers *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{
		for (int i=0;i<100;i++)
		{
			printf("%d->", result_1->a[i]);

		}
		printf("\n");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
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
	add_prog_1 (host);
exit (0);
}