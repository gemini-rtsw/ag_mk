/* States of 20Hz data */

#define MCS_VALID   0
#define MCS_INVALID 1
#define MCS_TIMEOUT 2

/* PMAC Access, Interlock Signals */

#define MCS_GOOD 0
#define MCS_BAD  1

/* Axis States */

#define MCS_NOT_DATUMED 0
#define MCS_BRAKED      1
#define MCS_STATIONARY  2
#define MCS_SLEWING     3
#define MCS_TRACKING    4
#define MCS_PARKED      5

/* Virtual Encoder algorithms for the axes */

#define MCS_FDE  0
#define MCS_FULL 1
#define MCS_N    2
#define MCS_M_N  3
#define MCS_EL_N 4

/* Virtual Encoder heads */

#define MCS_NONE         0
#define MCS_HEAD_1       1
#define MCS_HEAD_2       2
#define MCS_HEAD_3       3
#define MCS_HEAD_4       4
#define MCS_HEADS_1_3    5
#define MCS_HEADS_2_4    6
#define MCS_HEADS_1_2    7
#define MCS_HEAD_1_T     8
#define MCS_HEAD_2_T     9
#define MCS_ALL_AZHEADS 10
#define MCS_ALL_ELHEADS 11

/* Debug States */

/* MCS_NONE defined earlier */
/* MCS_FULL defined earlier */

/* Elevation Striker Bracket Positions */

#define MCS_OBSERVING   0
#define MCS_ENGINEERING 1

/* Elevation Tilt Switch Positions */

#define MCS_BELOW_45_DEGREES 0
#define MCS_ABOVE_45_DEGREES 1

/* Follow States */

#define MCS_IGNORING  0
#define MCS_FOLLOWING 1

/* Health States */

/* MCS_GOOD and MCS_BAD already defined */
#define MCS_WARNING 2

/* In-Position States */

#define MCS_FALSE 0
#define MCS_TRUE  1

/* Logging States - logData SIR record */

#define MCS_LOG_OFF      0
#define MCS_LOG_PRIMED   1
#define MCS_LOG_ON       2

/* Simulation States */

/* MCS_NONE defined earlier */
/* MCS_FULL defined earlier */
#define MCS_VSM  2
#define MCS_FAST 3

/* Operational States of the MCS */

#define MCS_BOOTING      0
#define MCS_INITIALISING 1
#define MCS_RUNNING      2

/* Azimuth Cable Wraps */

#define MCS_WRAP_A 0
#define MCS_WRAP_B 1
#define MCS_WRAP_C 2

/* Look-up Tables */

#define MCS_REFERENCE 0
#define MCS_TAPE      1
