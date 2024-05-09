#### Custom implementation of memory allocation functions

This is an attempt to make my own memory allocation functions (malloc, calloc, realloc and free) using `sbrk()` in Linux.

Program compiles and runs as expected, may use it in future projects.


Projects using this implementation:

- None for now

##### How to compile the library and source file

From: https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

Create `/bin/static` folder and make the object with `gcc -c src/memalloc_j/memalloc_j.c -o bin/static/memalloc_j.o`

Create the library with `ar rcs bin/static/libmemalloc_j.a bin/static/memalloc_j.o`

Compile `main.c` with the bash file `compile.sh`
