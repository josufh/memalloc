#### Custom implementation of memory allocation functions.

Use `gcc -o memalloc.so -fPIC -shared memalloc.c` to compile.

Use `export LD_PRELOAD=$PWD/memalloc.so` to use in Linux console.
Use `unset LD_PRELOAD` to stop using it.
