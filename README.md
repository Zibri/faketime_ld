# faketime_ld
Simple faketime using LD_LIBRARY but a single file

# usage example
```
$ ./faketime_ld 21137400 ./date
--------------------------1------------------------
time (NULL)   :   21137400 Wed Sep  2 18:30:00 1970
time (&var)   :   21137400 Wed Sep  2 18:30:00 1970
gettimeofday  :   21137400 Wed Sep  2 18:30:00 1970
clock_gettime :   21137400 Wed Sep  2 18:30:00 1970
---------------------------------------------------
--------------------------2------------------------
time (NULL)   :   21137405 Wed Sep  2 18:30:05 1970
time (&var)   :   21137405 Wed Sep  2 18:30:05 1970
gettimeofday  :   21137405 Wed Sep  2 18:30:05 1970
clock_gettime :   21137405 Wed Sep  2 18:30:05 1970
---------------------------------------------------
--------------------------3------------------------
time (NULL)   :   21137410 Wed Sep  2 18:30:10 1970
time (&var)   :   21137410 Wed Sep  2 18:30:10 1970
gettimeofday  :   21137410 Wed Sep  2 18:30:10 1970
clock_gettime :   21137410 Wed Sep  2 18:30:10 1970
---------------------------------------------------
```
Alternate syntax:  
```TDELTA=3600 LD_PRELOAD=./faketime_ld date```

![faketime_ld](https://github.com/Zibri/faketime_ld/workflows/C/C++%20CI/badge.svg)
