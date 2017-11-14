/*******************************************************************************
 * NAME:	    iec60062.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the public interface for the C source in
 *		    iec60062.c. These functions are used to convert component
 *		    values to strings in "R" notation (See IEC 60062:2015) for
 *		    "pretty printing" component values to the user.
 *
 * CREATED:	    11/07/2017
 *
 * LAST EDITED:	    11/14/2017
 ***/

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

/* `Types' for iec_rtostr() and iec_rtof()
 */
#define IEC_CAPACITOR	0x0
#define IEC_RESISTOR	0x1
#define IEC_INDUCTOR	0x2

/* IEC E series for iec_etol() and iec_eser()
 */
#define IEC_E3		0x004
#define IEC_E6		0x008
#define IEC_E12		0x010
#define IEC_E24		0x020
#define IEC_E48		0x040
#define IEC_E96		0x080
#define IEC_E192	0x100

/* The Renard series rounding function enforces the "least rounded" series.
 * This was a design choice at the expense of the series.
 */
#define IEC_R5		0x0200
#define IEC_R10		0x0400
#define IEC_R20		0x0800
#define IEC_R40		0x1000
#define IEC_R80		0x2000

/* Directions to round -- up, down, or to the nearest.
 */
#define IEC_ROUND_UP	0xfd
#define IEC_ROUND_DOWN	0xfe
#define IEC_ROUND_NEAR	0xff

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/**
 * This function returns an alloc'd string.
 */
extern char * iec_rtostr(float value, float tolerance, int type);

/**
 * Return the float value of the "R" notation, and place the tolerance in
 * *tolerance.
 */
extern float iec_rtof(char * rvalue, float * tolerance, int * type);

/**
 * Round `value' using the Renard series.
 */
extern float iec_renard(float value, int series, int direction);

/**
 * Round value using E series `series'
 */
extern float iec_eser(float value, int series, int direction);

/**
 * Round value to E series using `tolerance'
 */
extern float iec_etol(float value, float tolerance, int direction);

/******************************************************************************/
