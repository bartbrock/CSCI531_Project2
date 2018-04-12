/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "qs100.h"

bool_t
xdr_numbers (XDR *xdrs, numbers *objp)
{
	register int32_t *buf;

	int i;

	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, (2 +  100 )* BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->low))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->high))
				 return FALSE;
			 if (!xdr_vector (xdrs, (char *)objp->a, 100,
				sizeof (int), (xdrproc_t) xdr_int))
				 return FALSE;
		} else {
			IXDR_PUT_LONG(buf, objp->low);
			IXDR_PUT_LONG(buf, objp->high);
			{
				register int *genp;

				for (i = 0, genp = objp->a;
					i < 100; ++i) {
					IXDR_PUT_LONG(buf, *genp++);
				}
			}
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, (2 +  100 )* BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->low))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->high))
				 return FALSE;
			 if (!xdr_vector (xdrs, (char *)objp->a, 100,
				sizeof (int), (xdrproc_t) xdr_int))
				 return FALSE;
		} else {
			objp->low = IXDR_GET_LONG(buf);
			objp->high = IXDR_GET_LONG(buf);
			{
				register int *genp;

				for (i = 0, genp = objp->a;
					i < 100; ++i) {
					*genp++ = IXDR_GET_LONG(buf);
				}
			}
		}
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->low))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->high))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->a, 100,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}
