/*******************************************************************************
 * NAME:	    iec60062.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains some functions to convert numerical
 *		    values to strings in "R" notation, according to IEC
 *		    60062:2016.
 *
 * CREATED:	    11/07/2017
 *
 * LAST EDITED:	    11/07/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>

#include "iec60062.h"

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    rtostr
 *
 * DESCRIPTION:	    This function converts the base 10 (e0) float in `value' to
 *		    "R" notation, according to the IEC 60062:2016 standard.
 *
 * ARGUMENTS:	    value: (float) -- the value to convert
 *		    tolerance: (float) -- the component's tolerance, in percent:
 *			i.e. 1, 5, 10, etc.
 *		    type: (int) -- the type of component. One of three macros
 *			which are defined in iec60062.h
 *
 * RETURN:	    char * -- an allocated string containing the "R" notation
 *		    of the components value, or NULL if an error occurred.
 *
 * NOTES:	    The returned string must be free'd after use.
 ***/
char * iec_rtostr(float value, float tolerance, int type)
{
  return NULL; /* Implement rtostr */
}

/*******************************************************************************
 * FUNCTION:	    rtof
 *
 * DESCRIPTION:	    This function converts the "R" notation string in `rvalue'
 *		    to a component value and tolerance. The value is returned,
 *		    and the tolerance is placed into *tolerance at the end of
 *		    the call. A negative value is returned if there is an error.
 *
 * ARGUMENTS:	    rvalue: (char *) -- the "R" notation string.
 *		    tolerance: (float *) -- location to place the value of the
 *			component's tolerance after the function call.
 *		    type: (int *) -- the type of component. One of three macros
 *			defined in iec60062.h. Type is placed here on return.
 *
 * RETURN:	    float -- components value, or less than 0 if an error
 *			occurred.
 *
 * NOTES:	    Since inductors and capacitors have the same "R" notation,
 *		    if this notation is encountered, *type is set to the bitwise
 *		    OR of C_INDUCTOR and C_RESISTOR
 ***/
float iec_rtof(char * rvalue, float * tolerance, int * type)
{
  return -1.0F; /* TODO: Implement rtof */
}

/*******************************************************************************
 * FUNCTION:	    iec_rener
 *
 * DESCRIPTION:	    This function rounds `value' to the nearest value in the
 *		    Rener series, or to the next value in `direction.'
 *
 * ARGUMENTS:	    value: (float) -- the value to round.
 *		    series: (int) -- the Rener series to use. One of macros
 *			defined in iec60062.h.
 *		    direction: (int) -- the direction to round in. One of macros
 *			defined in iec60062.h.
 *
 * RETURN:	    float -- the rounded value, or -1F if an error has occurred.
 *
 * NOTES:	    none.
 ***/
float iec_rener(float value, int series, int direction)
{
  return -1.0F; /* TODO: Implement iec_rener */
}

/*******************************************************************************
 * FUNCTION:	    iec_eser
 *
 * DESCRIPTION:	    Round `value' to the nearest value in the IEC E series
 *		    `series,' or to the next value in direction `direction.'
 *
 * ARGUMENTS:	    value: (float) -- the value to round.
 *		    series: (int) -- the series to use. One of macros defined in
 *			iec60062.h. May be bitwise OR of two or more series.
 *		    direction: (int) -- the direction to round in. One of macros
 *			defined in iec60062.h.
 *
 * RETURN:	    float -- the rounded value, or -1F if an error has occurred.
 *
 * NOTES:	    none.
 ***/
float iec_eser(float value, int series, int direction)
{
  return -1.0F; /* TODO: Implement iec_eser */
}

/*******************************************************************************
 * FUNCTION:	    iec_etol
 *
 * DESCRIPTION:	    Round `value' to the nearest value in the IEC E series with
 *		    tolerance `tolerance,' or to the next value in `direction.'
 *
 * ARGUMENTS:	    value: (float) -- the value to round.
 *		    tolerance: (float) -- the decimal tolerance value to use
 *			for rounding. Value returned is NOT guaranteed to be
 *			within the tolerance specified.
 *		    direction: (int) -- the direction to round. One of macros
 *			defined in iec60062.h.
 *
 * RETURN:	    float -- the rounded value, or -1F if an error has occurred.
 *
 * NOTES:	    This fn may be used in lieu of iec_eser() if the series
 *		    is not known. THE VALUE RETURNED IS NOT GUARANTEED TO BE
 *		    WITHIN THE TOLERANCE SPECIFIED. 
 ***/
float iec_etol(float value, float tolerance, int direction)
{
  return -1.0F; /* TODO: Implement iec_etol */
}

/******************************************************************************/
