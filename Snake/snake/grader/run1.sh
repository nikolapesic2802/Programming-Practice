#!/bin/sh

if [ -e gslibIN ] ; then rm gslibIN ; fi
if [ -e gslibOUT ] ; then rm gslibOUT ; fi

mkfifo gslibIN 
mkfifo gslibOUT

./gslib1 > gslibIN < gslibOUT &
./snake
