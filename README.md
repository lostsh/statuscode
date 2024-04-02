# statuscode
Simple C99 script to retrieve **HTTP status code** from _(simple)_ request on port **80** of a given ip.
## Build / Compile
1. Using make
2. Using gcc _(signle commandline)_

### 1. Using make
Just type `make` into the directory containing the `Makefile` and the binary will be build into `bin/`.

### 2. Using gcc
From the dicretory containing `src/` and `bin/` use the following gcc compilation line :
```bash
gcc  -g -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700 -fsanitize=address src/main.c src/requestor.c -o bin/requestor
```

## Install 

## Run
The binary file is in the `bin/` direcotry, either `main` or `requestor`.


Give target ip by argument. `./bin/requestor -t 1.1.1.1`.

Verbose option is available, to enable it add the `-v` argument to comand line.

## Example
