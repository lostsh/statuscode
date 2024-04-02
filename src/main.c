/**
* \file main.c
* \version 1.0 beta
* \author Vernhes Yohann (lostsh)
* \date 1 april 2024
* \brief check the http code of inputed websites
* Main file using requestor lib to send requests
*/

#include "requestor.h"
#include <stdio.h>

void printUsage(const char *scriptname){
    printf("[ = ]\tRequestor\n");
    printf("[ * ]\tSend HTTP request on port 80 of spcified target.\n");
    printf("[ * ]\tRetrieve HTTP response code.\n\n");
    printf("[ + ]\tUsage: %s\n", scriptname);
    printf("[ > ]\t-t [target_ip] \t Input target ip (required)\n");
    printf("[ > ]\t-v             \t Enable verbose mode\n");
    printf("[ > ]\t-h             \t Show this help\n\n");
}

int main(int argc, char **argv){
    //Handle arguments
    if(argc < 2){
        fprintf(stderr, "[ ! ]\tException: no arguments given\n");
        printUsage(argv[0]);
        return 1;
    }

    // arguments vars
    short int argv_target_index = -1;
    unsigned char debug = 0;

    // iterate over argv
    for(int i=0; i<argc; i++){
        if(*argv[i] == '-'){
            switch(*(argv[i]+1)){
                case 't':
                    if(i<argc-1) argv_target_index = i+1;
                break;
                case 'v':
                    debug = 1;
                break;
                case 'h':
                    printUsage(argv[0]);
                    return 0;
                break;
            }
        }
    }
    //Exception on missing target
    if(argv_target_index < 0){
        fprintf(stderr, "[ ! ]\tException: missing target argument\n");
        printUsage(argv[0]);
        return 1;
    }

    //Run requestor
    if(debug) printf("[ = ]\tStarting requestor\n");

    char return_code[8] = "";
    int success = getHttpCode(*(argv+argv_target_index), return_code);
    if(success != 0){
        fprintf(stderr, "[ ! ]\tException: cannot retrive http code\n");
        return success;
    }

    //Outpur
    if(debug) printf("[ > ]\tHTTP CODE: [%s]\n", return_code);
    else printf("%s", return_code);
    return 0;
}