# A Library for Handling Discrete Component Values #

This is a library that can be used to round empirical discrete component
values to values that are present in the IEC 60062:2015 standard. I've used
this library in a couple of programs which calculate circuit component values
based on a set of desired conditions.<br/>
## Component Rounding ##
Three functions are used to round component values to standard values:

`float iec_renard(float value, int series, int direction);`

`float iec_eser(float value, int series, int direction);`

`float iec_etol(float value, float tolerance, int direction);`


* `iec_renard` - This function rounds \`value' to the nearest
  value in the Renard series, or to the next value in \`direction.' The Renard
  series is used to dictate component values for fuses.
* `iec_eser` - Round \`value' to the nearest value in the IEC E
  series \`series,' or to the next value in direction \`direction.' The E
  series dictates component values for all other passive discrete components.
* `iec_etol` - Round \`value' to the nearest value in the IEC E
  series with tolerance \`tolerance,' or to the next value in \`direction.' This
  fn may be used in lieu of iec_eser() if the series is not known. THE VALUE
  RETURNED IS NOT GUARANTEED TO BE WITHIN THE TOLERANCE SPECIFIED.

With the exception of the third function, the only function parameter supplied
"by the user" is the first, `value`. The final two should be macros
defined in iec60062.h. In the case of `iec_etol`, the second
parameter is also supplied by the user, and is the tolerance which the user
wishes to bound the search.

## Pretty Printing ##
In addition, the library provides two functions which can be used to convert
between "R" notation and floating point values:

`char * iec_rtostr(float value, float tolerance, int type);`

`float iec_rtof(char * rvalue, float * tolerance, int * type);`

* `iec_rtostr` - converts the base 10 (e0) float in \`value'
  to "R" notation, according to the IEC 60062:2016 standard. The returned
  string must be free'd after use.
* `iec_rtof` - converts the "R" notation string in \`rvalue'
  to a component value and tolerance. The value is returned, and the
  tolerance is placed into *tolerance at the end of the call. A negative
  value is returned if there is an error.
