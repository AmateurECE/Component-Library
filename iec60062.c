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
 * LAST EDITED:	    11/09/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <math.h>

#include "iec60062.h"

/*******************************************************************************
 * STATIC VARIABLES
 ***/

/* E series values */
static const float e3[] = { 1.0, 2.2, 4.7 };
static const float e6[] = { 1.0, 1.5, 2.2, 3.3, 4.7, 6.8 };
static const float e12[] = {
  1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2
};
static const float e24[] = {
  1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0,
  3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1
};
static const float e48[] = {
  1.00, 1.05, 1.10, 1.15, 1.21, 1.27, 1.33, 1.40, 1.47, 1.54,
  1.62, 1.69, 1.78, 1.87, 1.96, 2.05, 2.15, 2.26, 2.37, 2.49,
  2.61, 2.74, 2.87, 3.01, 3.16, 3.32, 3.48, 3.65, 3.83, 4.02,
  4.22, 4.42, 4.64, 4.87, 5.11, 5.36, 5.62, 5.90, 6.19, 6.49,
  6.81, 7.15, 7.50, 7.87, 8.25, 8.66, 9.09, 9.53
};
static const float e96[] = {
  1.00, 1.02, 1.05, 1.07, 1.10, 1.13, 1.15, 1.18, 1.21, 1.24,
  1.27, 1.30, 1.33, 1.37, 1.40, 1.43, 1.47, 1.50, 1.54, 1.58,
  1.62, 1.65, 1.69, 1.74, 1.78, 1.82, 1.87, 1.91, 1.96, 2.00,
  2.05, 2.10, 2.15, 2.21, 2.26, 2.32, 2.37, 2.43, 2.49, 2.55,
  2.61, 2.67, 2.74, 2.80, 2.87, 2.94, 3.01, 3.09, 3.16, 3.24,
  3.32, 3.40, 3.48, 3.57, 3.65, 3.74, 3.83, 3.92, 4.02, 4.12,
  4.22, 4.32, 4.42, 4.53, 4.64, 4.75, 4.87, 4.99, 5.11, 5.23,
  5.36, 5.49, 5.62, 5.76, 5.90, 6.04, 6.19, 6.34, 6.49, 6.65,
  6.81, 6.98, 7.15, 7.32, 7.50, 7.68, 7.87, 8.06, 8.25, 8.45,
  8.66, 8.87, 9.09, 9.31, 9.53, 9.76
};
static const float e192[] = {
  1.00, 1.01, 1.02, 1.04, 1.05, 1.06, 1.07, 1.09, 1.10, 1.11,
  1.13, 1.14, 1.15, 1.17, 1.18, 1.20, 1.21, 1.23, 1.24, 1.26,
  1.27, 1.29, 1.30, 1.32, 1.33, 1.35, 1.37, 1.38, 1.40, 1.42,
  1.43, 1.45, 1.47, 1.49, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60,
  1.62, 1.64, 1.65, 1.67, 1.69, 1.72, 1.74, 1.76, 1.78, 1.80,
  1.82, 1.84, 1.87, 1.89, 1.91, 1.93, 1.96, 1.98, 2.00, 2.03,
  2.05, 2.08, 2.10, 2.13, 2.15, 2.18, 2.21, 2.23, 2.26, 2.29,
  2.32, 2.34, 2.37, 2.40, 2.43, 2.46, 2.49, 2.52, 2.55, 2.58,
  2.61, 2.64, 2.67, 2.71, 2.74, 2.77, 2.80, 2.84, 2.87, 2.91,
  2.94, 2.98, 3.01, 3.05, 3.09, 3.12, 3.16, 3.20, 3.24, 3.28,
  3.32, 3.36, 3.40, 3.44, 3.48, 3.52, 3.57, 3.61, 3.65, 3.70,
  3.74, 3.79, 3.83, 3.88, 3.92, 3.97, 4.02, 4.07, 4.12, 4.17,
  4.22, 4.27, 4.32, 4.37, 4.42, 4.48, 4.53, 4.59, 4.64, 4.70,
  4.75, 4.81, 4.87, 4.93, 4.99, 5.05, 5.11, 5.17, 5.23, 5.30,
  5.36, 5.42, 5.49, 5.56, 5.62, 5.69, 5.76, 5.83, 5.90, 5.97,
  6.04, 6.12, 6.19, 6.26, 6.34, 6.42, 6.49, 6.57, 6.65, 6.73,
  6.81, 6.90, 6.98, 7.06, 7.15, 7.23, 7.32, 7.41, 7.50, 7.59,
  7.68, 7.77, 7.87, 7.96, 8.06, 8.16, 8.25, 8.35, 8.45, 8.56,
  8.66, 8.76, 8.87, 8.98, 9.09, 9.20, 9.31, 9.42, 9.53, 9.65,
  9.76, 9.88
};

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static float gnp10(float value);
static float stdvalue(float value, float * array, size_t size, int direction);

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
 *			iec60062.h.
 *		    direction: (int) -- the direction to round in. One of macros
 *			defined in iec60062.h.
 *
 * RETURN:	    float -- the rounded value, or -1F if an error has occurred.
 *
 * NOTES:	    none.
 ***/
float iec_eser(float value, int series, int direction)
{
  if (!isnormal(value) || value <= 0)
    return -1.0F;

  switch (series) {
  case IEC_E3:
    return stdvalue(gnp10(value), (float *)&e3,
		    sizeof(e3) / sizeof(float), direction);
  case IEC_E6:
    return stdvalue(gnp10(value), (float *)&e6,
		    sizeof(e6) / sizeof(float), direction);
  case IEC_E12:
    return stdvalue(gnp10(value), (float *)&e12,
		    sizeof(e12) / sizeof(float), direction);
  case IEC_E24:
    return stdvalue(gnp10(value), (float *)&e24,
		    sizeof(e24) / sizeof(float), direction);
  case IEC_E48:
    return stdvalue(gnp10(value), (float *)&e48,
		    sizeof(e48) / sizeof(float), direction);
  case IEC_E96:
    return stdvalue(gnp10(value), (float *)&e96,
		    sizeof(e96) / sizeof(float), direction);
  case IEC_E192:
    return stdvalue(gnp10(value), (float *)&e192,
		    sizeof(e192) / sizeof(float), direction);
  default:
    return -1.0F;
  }
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
  if (tolerance < 1.0F) {
    return iec_eser(value, IEC_E192, direction);
  } else if (tolerance < 2.0F) {
    return iec_eser(value, IEC_E96, direction);
  } else if (tolerance < 5.0F) {
    return iec_eser(value, IEC_E48, direction);
  } else if (tolerance < 10.0F) {
    return iec_eser(value, IEC_E24, direction);
  } else if (tolerance < 20.0F) {
    return iec_eser(value, IEC_E12, direction);
  } else if (tolerance == 20.0F) {
    return iec_eser(value, IEC_E6, direction);
  } else if (tolerance > 20.0F) {
    return iec_eser(value, IEC_E3, direction);
  }

  return -1.0F;
}

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    gnp10
 *
 * DESCRIPTION:	    Find the greatest natural power of 10, k, such that
 *		    value mod (10 ^ k) > 0, value mod (10 ^ (k - 1)) == 0
 *
 * ARGUMENTS:	    value: (float) -- the value to round.
 *
 * RETURN:	    float -- the value, or NaN if an error occurs.
 *
 * NOTES:	    none.
 ***/
static float gnp10(float value)
{
  if (!isnormal(value) || value <= 0.0F)
    return NAN;

  return floorf(log10f(value));
}

static float stdvalue(float value, float * array, size_t size, int direction)
{
  float t = gnp10(value);
  if (isnan(t))
    return -1.0F;
  value /= pow(10, (int)t);

  size_t index = size / 3;
  if (value < array[index * 2]) {
    if (value < array[index])
      index = 0;
  } else {
    index *= 2;
  }

  float t1 = 0.0F, t2 = 0.0F;
  while (index < size) { /* TODO: Incorrect Implementation of the algorithm. */
    if (array[index] == value)
      return value;
    t2 = t1;
    t1 = array[index] / value;
    if (t1 < t2)
      return array[--index] * pow(10, (int)t);
    index++;
  }

  return -1.0F; /* Should never get here. */
}

/******************************************************************************/
