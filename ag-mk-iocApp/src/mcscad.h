/*
 * Contains values shared between CAD routines and other
 * routines further down the processing chain.
 */

/* "move" command */

#define MASK_AZMOVE   1023
#define MASK_AZNOMOVE  520
#define MASK_ELMOVE    511
#define MASK_ELNOMOVE    8

#define CLIENT_TCS       0
#define CLIENT_ENG       1

/* "stop" command */

#define MASK_AZSTOP     61
#define MASK_AZNOSTOP    0
#define MASK_ELSTOP     64
#define MASK_ELNOSTOP    1
