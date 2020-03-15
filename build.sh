#!/bin/bash
gcc -fPIC -pie  -Wl,-E faketime_ld.c -o faketime_ld
gcc date.c -o date
strip -s faketime_ld
strip -s date

