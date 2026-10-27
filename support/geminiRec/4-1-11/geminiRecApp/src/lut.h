#ifndef INCluth
#define INCluth


#define LUT_NUM_SZ	4
#define LUT_TAG_SZ	MAX_STRING_SIZE

typedef struct LUT
{
    ELLNODE node;
    char tag[LUT_TAG_SZ];
    long nval;
    long table; 
    union
    {
	long lval;
	double dval;
	char sval[LUT_TAG_SZ];
    } val[LUT_NUM_SZ];
    union
    {
	long lval;
	double dval;
    } tol_lo[LUT_NUM_SZ];
    union
    {
	long lval;
	double dval;
    } tol_hi[LUT_NUM_SZ];
} LUT;


#endif	/* !INCluth */
