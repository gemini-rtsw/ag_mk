/* *INDENT-OFF* */
/*
*   FILENAME
*   sirDisplay.c
*
*   FUNCTION NAME(S)
*   sirDisplayTime -   formats a time for display
*   sirRADecSys    -   formats a frame into the strings allowed by FITS
*   sirRArcsecs    -   formats an angle in arcsecs for display
*   sirRDegs -         formats an angle in degrees for display
*   sirSDegsSigned -   formats an angles as +/-dms for display
*   sirSDegsUnsigned - formats an angles as dms for display
*   sirSHrs -          formats an angle as an RA
*   sirDisplayFrame -  formats a coordinate frame for display
*   sirHealth       -  Sets the severity of a health record
*
*/
/*
 * $Log:
 */
/* *INDENT-ON* */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dbDefs.h>
#include <alarm.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <sirRecord.h>
#include "tcsConstants.h"
#include "slalib.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirDisplayTime
 *
 *   Purpose:
 *   Generate a string representing an angle
 *
 *   Description:
 *   Format input SIR value which is an MJD time
 *   and convert to the time as hh mm ss.sss 
 *
 *   Invocation:
 *   sirDisplayTime (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long sirDisplayTime(struct sirRecord *psir)
{
    double time;                /* Time as MJD */
    int jy, jmo, jd;            /* Year, month, day */
    double fd;                  /* Fraction of day */
    int status;
    int jh, jm, js, jss;        /* hrs, min, sec, frac-sec as integers */

/* Read input double value MJD */
    sscanf(psir->val, "%lg", &time);

/* Convert to year, month, day, frac day */
    slaDjcl(time, &jy, &jmo, &jd, &fd, &status);
    jh = (int) (fd * 24.0);     /* Hours */
    jm = (int) ((fd * 24.0 - jh) * 60.0);       /* Minutes */
    jss = (int) ((((fd * 24.0 - jh) * 60.0) - jm) * 600.0);     /* Fractional
                                                                   secs */
    js = jss / 10;              /* Secs */
    jss = jss - js * 10;

/* Write out time as a string in to the SIR .VAL field */
    sprintf(psir->val, "%2.2d:%2.2d:%2.2d.%d", jh, jm, js, jss);
    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirRaDecSys
 *
 *   Purpose:
 *   Generate a FITS conforming string describing the coordinate system 
 *
 *   Description:
 *   A simple translation routine that takes the string the TCS uses to
 *   describe the coordinate system and converts it to the form required
 *   by the FITS keyword RADECSYS. For az/el frames the string is set to
 *   blank.
 *
 *   Invocation:
 *   sirRaDecSys (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *-
 */
/* *INDENT-ON* */

long sirRaDecSys(struct sirRecord *psir)
{

    long status;                /* return status */
    char inFrame[16] ;          /* Input frame description */

    status = 0;

    strcpy(inFrame, psir->val) ;

    if (strcmp(inFrame, "FK5") == 0 ||
        strcmp(inFrame, "FK4") == 0 ||
        strcmp(inFrame, "FK4-NO-E") == 0 ) {
      strcpy(psir->val, inFrame) ;
    } else if (strcmp(inFrame, "APPT") == 0) {
      strcpy(psir->val, "GAPPT") ;
    } else {
      strcpy(psir->val, " " ) ;
    }

    return status;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirRArcsecs
 *
 *   Purpose:
 *   Generate a string representing an angle
 *
 *   Description:
 *   Format input SIR value which is an angle in radians 
 *   and convert to decimal string as arcsecs, format f7.3 
 *
 *   Invocation:
 *   sirRArcsecss (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   sscanf         (stdio)           Read and convert a string
 *   sprintf        (stdio)           Write a formatted string
 *
 *-
 */
/* *INDENT-ON* */

long sirRArcsecs(struct sirRecord *psir)
{
    double radval;              /* Angle in rads */
    double arcsecs;                /* Angle in degs */
    int alarm = NO_ALARM;       /* Alarm status returned */

/* Read in double value in radians */
    sscanf(psir->val, "%lg", &radval);
    arcsecs = radval / AS2R;

/* Check for alarm. Assume alarm values in degrees */
    if ((arcsecs <= psir->low) || (arcsecs >= psir->high))
        alarm = MINOR_ALARM;
    if ((arcsecs <= psir->lolo) || (arcsecs >= psir->hihi))
        alarm = MAJOR_ALARM;
    sprintf(psir->val, "%+7.3f", arcsecs);         /* Write out as signed string in degs */
    psir->brsv = alarm;
    return alarm;
}

/*+
 *   Function name:
 *   sirHealth
 *
 *   Purpose:
 *   Set the alarm severity of a health record based on the health value
 *
 *   Description:
 *   Check the incoming health strings and set the alarm severity accordingly
 *
 *   Invocation:
 *   sirHealth (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   sscanf         (stdio)           Read and convert a string
 *   sprintf        (stdio)           Write a formatted string
 *
 *-
 */
/* *INDENT-ON* */

long sirHealth(struct sirRecord *psir)
{
    int alarm ;                 /* Alarm status returned */
    char hval[80];              /* health value */
    int i ;

/* Read in string value and uppercase it */
    strcpy (hval, psir->val) ;
    i = 0 ;
    while (hval[i] != '\0') {
      hval[i] = toupper((int)hval[i]) ;
      i++ ;
    }	

/* Set alarm value */
    if (!strncmp(hval, "GOOD",3))
      alarm = NO_ALARM;
    else if (!strncmp(hval, "WARNING", 7))
      alarm = MINOR_ALARM;
    else if (!strncmp (hval, "BAD", 3))
      alarm = MAJOR_ALARM;
    else
      alarm = INVALID_ALARM ;

    psir->brsv = alarm;
    return alarm;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirRDegs
 *
 *   Purpose:
 *   Generate a string representing an angle
 *
 *   Description:
 *   Format input SIR value which is an angle in radians 
 *   and convert to decimal string as degs, format f7.3 
 *
 *   Invocation:
 *   sirRDegs (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long sirRDegs(struct sirRecord *psir)
{
    double radval;              /* Angle in rads */
    double degs;                /* Angle in degs */
    int alarm = NO_ALARM;       /* Alarm status returned */

/* Read in double value in radians */
    sscanf(psir->val, "%lg", &radval);
    degs = radval * R2D;

/* Check for alarm. Assume alarm values in degrees */
    if ((degs <= psir->low) || (degs >= psir->high))
        alarm = MINOR_ALARM;
    if ((degs <= psir->lolo) || (degs >= psir->hihi))
        alarm = MAJOR_ALARM;
    sprintf(psir->val, "%+7.3f", degs);         /* Write out as signed string in degs */
    psir->brsv = alarm;
    return alarm;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirSDegsSigned
 *
 *   Purpose:
 *   Generate a string representing an angle
 *
 *   Description:
 *   Format input SIR value which is an angle in degrees 
 *   and convert to a signed sexagesimal string : deg ,min, sec, frac 
 *
 *   Invocation:
 *   sirSDegsSigned (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */
/* *INDENT-ON* */

long sirSDegsSigned(struct sirRecord *psir)
{
    double radval;              /* Angle in rads */
    double degs;                /* Angle in degs */
    char sign;                  /* + or - */
    int dmsf[4];                /* deg, min, sec, frac as integers */
    int alarm = NO_ALARM;       /* Alarm status returned */

/* Read input double value in degrees */
    sscanf(psir->val, "%lg", &degs);

    radval = degs * D2R;

/* Check for alarm. Assume alarm values in degrees */
    if ((degs <= psir->low) || (degs >= psir->high))
        alarm = MINOR_ALARM;
    if ((degs <= psir->lolo) || (degs >= psir->hihi))
        alarm = MAJOR_ALARM;

/* Convert to deg, min, sec, frac in dmsf */
    slaDr2af(2, radval, &sign, dmsf);

/* Format output string : angle as sexagesimal string  "+DDD:MM:SS.SS" */
    sign = dmsf[0] + dmsf[1] + dmsf[2] ? sign : '+';
    sprintf(psir->val, "%c%02d:%02d:%02d.%02d", sign, dmsf[0], dmsf[1], dmsf[2],
            dmsf[3]);
    psir->brsv = alarm;
    return alarm;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirSDegsUnsigned
 *
 *   Purpose:
 *   Generate a string representing an angle
 *
 *   Description:
 *   Format input SIR value which is an angle in radians 
 *   and convert to unsigned sexagesimal string : deg ,min, sec, frac 
 *   in the range 0 to 2*pi 
 *
 *   Invocation:
 *   sirSDegsUnsigned (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long sirSDegsUnsigned(struct sirRecord *psir)
{
    double radval;              /* Angle in rads */
    double degs;                /* Angle in degs */
    char sign;                  /* + or - */
    int dmsf[4];                /* deg, min, sec, frac as integers */
    int alarm = NO_ALARM;       /* Alarm status returned */

/* Read input double value in radians */
    sscanf(psir->val, "%lg", &radval);
    radval = slaDranrm(radval); /* Normalise to 0 to 2 pi */
    degs = radval * R2D;

/* Check for alarm. Assume alarm values in degrees */
    if ((degs <= psir->low) || (degs >= psir->high))
        alarm = MINOR_ALARM;
    if ((degs <= psir->lolo) || (degs >= psir->hihi))
        alarm = MAJOR_ALARM;

/* Convert to deg, min, sec, frac in dmsf */
    slaDr2af(2, radval, &sign, dmsf);

/* Format output string : angle as sexagesimal string  "+DDD:MM:SS.SS" */
    sprintf(psir->val, "%3d:%02d:%02d.%02d", dmsf[0], dmsf[1], dmsf[2],
            dmsf[3]);
    psir->brsv = alarm;
    return alarm;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirSHrs
 *
 *   Purpose:
 *   Generate a string representing an RA
 *
 *   Description:
 *   Formats input SIR value which is an angle in radians 
 *   and convert to sexagesimal RA string : Hrs ,min, sec, frac 
 *
 *   Invocation:
 *   sirSHrs (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long sirSHrs(struct sirRecord *psir)
{
    double radval;              /* Angle in rads */
    double degs;                /* Angle in degs */
    char sign;                  /* + or - */
    int hmsf[4];                /* hrs, min, sec, frac as integers */
    int alarm = NO_ALARM;       /* Alarm status returned */

/* Read input double value in radians */
    sscanf(psir->val, "%lg", &radval);

/* Normalise to 0 to 2 pi */
    radval = slaDranrm(radval);
    degs = radval * R2D;

/* Check for alarm. Assume alarm values in degrees */
    if ((degs <= psir->low) || (degs >= psir->high))
        alarm = MINOR_ALARM;
    if ((degs <= psir->lolo) || (degs >= psir->hihi))
        alarm = MAJOR_ALARM;

/* Convert to hrs, min, sec, frac in dmsf */
    slaDr2tf(3, radval, &sign, hmsf);

/* Handle 23 59 59.9999999999 -> 24 00 00.000 problem */
    if (hmsf[0] == 24)
        hmsf[0] = 0;

/* Format output string : angle as sexagesimal string  "HH:MM:SS.SS" */
    sprintf(psir->val, "%20d:%02d:%02d.%03d", hmsf[0], hmsf[1], hmsf[2],
            hmsf[3]);
    psir->brsv = alarm;
    return alarm;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   sirDisplayFrame
 *
 *   Purpose:
 *   Generate a string representing the coordinate system code
 *
 *   Description:
 *   This routine is attached to a string SIR record that pulls in the value
 *   of the coordinate frame code and then converts it into a suitable
 *   string.
 *
 *   Invocation:
 *   sirDisplayFrame (&psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir     (struct sirRecord *) Pointer to sir record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long sirDisplayFrame(struct sirRecord *psir)
{

    long status;                /* return status */
    FRAMETYPE sirFrame;         /* Frame value input to SIR */
    char stringFrame[16];       /* String to represent coordinate system */

    status = 0;

    sscanf(psir->val, "%d", (int *) &sirFrame);

    if (sirFrame == AZEL_MNT)
        strcpy(stringFrame, "Mount Az/El");
    else if (sirFrame == AZEL_TOPO)
        strcpy(stringFrame, "Topo Az/El");
    else if (sirFrame == APPT)
        strcpy(stringFrame, "Apparent");
    else if (sirFrame == FK5)
        strcpy(stringFrame, "FK5");
    else if (sirFrame == FK4)
        strcpy(stringFrame, "FK4");
    else
        strcpy(stringFrame, "Unknown");

    strcpy(psir->val, stringFrame);

    return status;
}

/* Register these symbols for use by IOC code */

epicsRegisterFunction( sirDisplayTime   );
epicsRegisterFunction( sirRaDecSys      );
epicsRegisterFunction( sirRArcsecs      );
epicsRegisterFunction( sirRDegs         );
epicsRegisterFunction( sirSDegsSigned   );
epicsRegisterFunction( sirSDegsUnsigned );
epicsRegisterFunction( sirSHrs          );
epicsRegisterFunction( sirDisplayFrame  );
epicsRegisterFunction( sirHealth        );
