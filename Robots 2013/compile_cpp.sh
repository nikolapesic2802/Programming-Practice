#!/bin/bash

NAME=robots

/usr/bin/g++ -DEVAL -static -O2 -o $NAME grader.c $NAME.cpp
