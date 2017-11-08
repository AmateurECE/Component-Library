/*******************************************************************************
 * NAME:	    gnp10-test.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    A test for the gnp10 function.
 *
 * CREATED:	    11/08/2017
 *
 * LAST EDITED:	    11/08/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "iec60062.c" /* gnp10() */
#include "error.h"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int gnp10(float value);
static float * gaussian(int size, float sigma);

/*******************************************************************************
 * MAIN
 ***/

int main() {

  const int arrsize = 10;
  const int numtests = 5;
  
  /* Array of (mean, sigma) pairs for generating the test data
   * Thema: One test for each scale of component value, with a prime sigma
   * which presents considerable swing.
   */
  const int tests[5][2] = {
    {0, 3},
    {10, 3},
    {100, 13},
    {1000, 133},
    {10000, 1333}
  };
  
  printf("Trial no.\tInput\t\tOutput\tFinal Value\n");
  float t, final, *arr;
  int diff;
  for (int i = 0; i < numtests; i++) {
    arr = gaussian(arrsize, tests[i][1]);
    StopIf(arr == NULL, 1, "Error: gaussian() returned NULL.\n");
    for (int j = 0; j < arrsize; j++) {
      t = fabsf(arr[j]) + (float)tests[i][0];
      diff = gnp10(t);
      final = t / powf(10.0F, (float)diff);
      printf("%d\t\t%8g\t%6d\t%8g\n", (10*i)+j+1, t, diff, final);
    }
    free(arr);
  }
}

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    gaussian
 *
 * DESCRIPTION:	    Generate an array of ten floating point values with mean = 0
 *		    and standard deviation `sigma.'
 *
 * ARGUMENTS:	    size: (int) -- the size of the array to allocate.
 *		    sigma: (float) -- the standard deviation
 *
 * RETURN:	    float * -- pointer to the allocated array, or NULL if there
 *		    was an error.
 *
 * NOTES:	    none.
 ***/
static float * gaussian(int size, float sigma)
{
  if (size <= 0 || sigma < 0)
    return NULL;

  gsl_rng_env_setup();
  gsl_rng * r = gsl_rng_alloc(gsl_rng_default);
  float * flarr = calloc(size, sizeof(float));
  if (flarr == NULL)
    return NULL;

  for (int i = 0; i < size; i++) {
    flarr[i] = (float)gsl_ran_gaussian(r, sigma);
  }

  gsl_rng_free(r);
  return flarr;
}

/******************************************************************************/
