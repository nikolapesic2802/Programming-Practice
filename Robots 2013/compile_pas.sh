#!/bin/bash

NAME=robots

/usr/bin/fpc -dEVAL -XS -O2 -o$NAME grader.pas
