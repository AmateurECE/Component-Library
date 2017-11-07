<h1>What's this?</h1>
This is a library that can be used to round empirical discrete component
values to values that are present in the IEC 60062:2015 standard. I've used
this library in a couple of programs which calculate circuit component values
based on a set of desired conditions.<br/>
<h1>Component Rounding</h1>
Three functions are used to round component values to standard values:<br/>
<code>float iec_rener(float value, int series, int direction);</code><br/>
<code>float iec_eser(float value, int series, int direction);</code><br/>
<code>float iec_etol(float value, float tolerance, int direction);</code><br/>
<list>
  <li/><code>iec_rener</code> - This function rounds `value' to the nearest
  value in the Rener series, or to the next value in `direction.' The Rener
  series is used to dictate component values for fuses.
  <li/><code>iec_eser</code> - Round `value' to the nearest value in the IEC E
  series `series,' or to the next value in direction `direction.' The E
  series dictates component values for all other passive discrete components.
  <li/><code>iec_etol</code> - Round `value' to the nearest value in the IEC E
  series with tolerance `tolerance,' or to the next value in `direction.' This
  fn may be used in lieu of iec_eser() if the series is not known. THE VALUE
  RETURNED IS NOT GUARANTEED TO BE WITHIN THE TOLERANCE SPECIFIED.
</list>
With the exception of the third function, the only function parameter supplied
"by the user" is the first, <code>value</code>. The final two should be macros
defined in iec60062.h. In the case of <code>iec_etol</code>, the second
parameter is also supplied by the user, and is the tolerance which the user
wishes to bound the search.</p>
<h1>Pretty Printing</h1>
<p>In addition, the library provides two functions which can be used to convert
  between "R" notation and floating point values:
  <code>
    char * iec_rtostr(float value, float tolerance, int type);<br/>
    float iec_rtof(char * rvalue, float * tolerance, int * type);<br/>
  </code>
  <list>
    <li/><code>iec_rtostr</code> - converts the base 10 (e0) float in `value'
    to "R" notation, according to the IEC 60062:2016 standard. The returned
    string must be free'd after use.
    <li/><code>iec_rtof</code> - converts the "R" notation string in `rvalue'
    to a component value and tolerance. The value is returned, and the
    tolerance is placed into *tolerance at the end of the call. A negative
    value is returned if there is an error.
  </list>
</p>
