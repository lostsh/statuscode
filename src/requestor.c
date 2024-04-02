/**
* \file requestor.c
* \version 1.0 beta
* \author Vernhes Yohann (lostsh)
* \date 1 april 2024
* \brief requestor lib to send HTTP request
* requestor module file
*/

#include "requestor.h"
#include <sys/socket.h>
#include <arpa/inet.h>

/**
* \note this func do not use send and recv
* it use read and write from the unistd lib
*/
int getHttpCode(const char *target_ip, char *return_code){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in target = {0};
    target.sin_family = AF_INET;
    target.sin_port = htons(80);
    target.sin_addr.s_addr = inet_addr(target_ip);

    //Connect socket to server
    if(connect(sockfd, (struct sockaddr*)&target, sizeof(target)) < 0){
        //write(STDERR_FILENO, "[ ! ]\tException: connect failed\n", 32);
        return 1;
    }

    //Send HTTP request
    char *reqStr = "HEAD / HTTP/1.0\r\n\r\n";
    if(send(sockfd, reqStr, len(reqStr), 0) < 0){
        //write(STDERR_FILENO, "[ ! ]\tException: send failed\n", 29);
        return 1;
    }

    //Handle http response
    char resp_buff[16] = "";
    int resp_size = recv(sockfd, resp_buff, sizeof(resp_buff), 0);
    if(resp_size <= 0){
        //write(STDERR_FILENO, "[ ! ]\tException: read or socket closed\n", 40);
        return resp_size;
    }
    *(resp_buff+resp_size-1) = '\0';
    //write(STDOUT_FILENO, resp_buff, resp_size);
    //write(1, "\n", 1);

    //Colose socket
    shutdown(sockfd, 2);

    //parse output
    int parse_success = parseCode(resp_buff, return_code);
    if(parse_success < 0){
        //write(STDERR_FILENO, "[ ! ]\tExeption: parsing code\n", 29);
        return parse_success;
    }

    //close(sockfd);
    return 0;
}

int parseCode(const char *responseStr, char *out_code){
    unsigned short int c = 0;
    while('\0' != *(responseStr+c) && len(out_code) < 3){
        if(' ' == *(responseStr+c)){
            *(out_code) = *(responseStr+c+1);
            *(out_code+1) = *(responseStr+c+2);
            *(out_code+2) = *(responseStr+c+3);
            *(out_code+3) = '\0';
        }
        c++;
    }
    return 0;
}

wlen_t len(const char *word){
    wlen_t size = 0;
    while('\0' != *(word+size)) size++;
    return size;
}