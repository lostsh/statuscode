# statuscode
Simple C99 script to retrieve **HTTP status code** from _(simple)_ request on port **80** of a given ip.
> Minimalist dependecy on sys lib
>> - main.c: `stdio.h`
>> - requestor.c: `unistd.h` _(for i/o)_, `sys/socket.h`, `arpa/inet.h`

To be precise, the script is just sending `HEAD / HTTP1.0\r\n\r\n` to port **80** of the given target ip. Then read the first **16 bytes** of the response to extract the **http status code**.

For refence about the HTTP verb `HEAD` see [rfc spec](https://www.rfc-editor.org/rfc/rfc1945.html#section-8.2) which explain is the same as `GET` but the server only answer with headers.


## Build / Compile

### 1. Using make
Just type `make` into the directory containing the `Makefile` and the binary will be build into `bin/`.

### 2. Using gcc
From the dicretory containing `src/` and `bin/` use the following gcc compilation line :
```bash
gcc  -g -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700 -fsanitize=address src/main.c src/requestor.c -o bin/requestor
```

## Install 

## Run
Example to make output pretty: 
```bash
./bin/main -t $(dig domain.tld +dnssec +short) && echo -e "\n"
```

The binary file is in the `bin/` direcotry, either `main` or `requestor`.

Give target ip by argument. `./bin/requestor -t 1.1.1.1`.

Verbose option is available, to enable it add the `-v` argument to comand line.

## Example
