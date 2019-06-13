#!/bin/sh

if [ -e gslibIN ] ; then rm gslibIN ; fi
if [ -e gslibOUT ] ; then rm gslibOUT ; fi

mkfifo gslibIN 
mkfifo gslibOUT

./gslib2 > gslibIN < gslibOUT &
./snake
