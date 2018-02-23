#define SYNTAX_ERROR  1
#define ALL_BLANKS    2
#define TOO_LONG      3

/* Function Prototypes */

long check_string( char *, char *, int, int );
long check_numeric( char * );

/* These are limits on the position and velocity tolerances */

#define POS_ERROR_LOWER 0.0          /* Degrees */
#define POS_ERROR_UPPER 2.0          /* Degrees */
#define VEL_ERROR_LOWER 0.0          /* Degrees/s */
#define VEL_ERROR_UPPER 2.0          /* Degrees/s */

#ifdef TELESCOPE

/* For the Telescope */

#define ECT            32           /* Encoder Conversion Table Counts Factor      */
#define RAW_PER_VE     1.0          /* Raw Counts per Virtual Encoder Count        */
#define AZDEG_TO_I222  45.0/2.0     /* Az. Factor between deg/s and I222 cnts/msec */
#define ELDEG_TO_I222  16.875/0.75  /* El. Factor between deg/s and I222 cnts/msec */
#define AZ_I223_S      30.0         /* Az. home velocity using switch              */
#define EL_I223_S      10.0         /* El. home velocity using switch              */
#define AZ_I223_H       1.0         /* Az. home velocity using tape head           */
#define EL_I223_H       1.0         /* El. home velocity using tape head           */

#else

/* For the stage */

#define ECT            32        /* Encoder Conversion Table Counts Factor   */
#define RAW_PER_VE     0.75/32.0 /* Raw Counts per Virtual Encoder Count/ECT */
#define AZDEG_TO_I222  0.5208    /* Factor between deg/s and I222 cnts/msec  */
#define ELDEG_TO_I222  0.5208    /* Factor between deg/s and I222 cnts/msec  */
#define AZ_I223_S      2.5       /* Az. home velocity using switch           */
#define EL_I223_S      2.5       /* El. home velocity using switch           */
#define AZ_I223_H      1.0       /* Az. home velocity using tape head        */
#define EL_I223_H      1.0       /* El. home velocity using tape head        */

#endif
