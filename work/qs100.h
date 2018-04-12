/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _QS100_H_RPCGEN
#define _QS100_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct numbers {
	int low;
	int high;
	int a[100];
};
typedef struct numbers numbers;

#define GS100_PROG 0x12345678
#define GS100_V1 1

#if defined(__STDC__) || defined(__cplusplus)
#define qsort 1
extern  numbers * qsort_1(numbers *, CLIENT *);
extern  numbers * qsort_1_svc(numbers *, struct svc_req *);
extern int gs100_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define qsort 1
extern  numbers * qsort_1();
extern  numbers * qsort_1_svc();
extern int gs100_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_numbers (XDR *, numbers*);

#else /* K&R C */
extern bool_t xdr_numbers ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_QS100_H_RPCGEN */
