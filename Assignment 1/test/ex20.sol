 The mathematical functions exp, log, sqrt, sin, cos, and atan2 are
       built in.  Other built-in functions:

       length the length of its argument taken as a string, or  of  $0  if  no
              argument.

       rand   random number on (0,1)

       srand  sets seed for rand and returns the previous seed.

       int    truncates to an integer value

       substr(s, m, n)
              the n-character substring of s that begins at position m counted
              from 1.

       index(s, t)
              the position in s where the string t occurs, or  0  if  it  does
              not.

       match(s, r)
              the position in s where the regular expression r occurs, or 0 if
              it does not.  The variables RSTART and RLENGTH are  set  to  the
              position and length of the matched string.

       split(s, a, fs)
              splits  the  string s into array elements a[1], a[2], ..., a[n],
              and returns n.  The separation is done with the regular  expres-
              sion  fs  or with the field separator FS if fs is not given.  An
              empty string as field separator splits the string into one array
              element per character.

       sub(r, t, s)
              substitutes t for the first occurrence of the regular expression
              r in the string s.  If s is not given, $0 is used.

       gsub   same as sub except that all occurrences of the  regular  expres-
              sion  are  replaced;  sub and gsub return the number of replace-
              ments.

       sprintf(fmt, expr, ... )
              the string resulting from formatting expr ...  according to  the
              printf(3) format fmt

       system(cmd)
              executes cmd and returns its exit status

       tolower(str)
              returns  a copy of str with all upper-case characters translated
              to their corresponding lower-case equivalents.

       toupper(str)
              returns a copy of str with all lower-case characters  translated
              to their corresponding upper-case equivalents.
