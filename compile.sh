#!/bin/bash

gcc -c src/main.c -o bin/main.o
gcc bin/main.o -l memalloc_j -o bin/main

