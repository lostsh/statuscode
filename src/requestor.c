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

    //Settings for target socket
    struct sockaddr_in target = {0};
    target.sin_family = AF_INET;
    target.sin_port = htons(80);
    target.sin_addr.s_addr = inet_addr(target_ip);

    //to check the return code
    int status = -1;

    //Connect socket to server
    if((status = connect(sockfd, (struct sockaddr*)&target, sizeof(target))) < 0) return status;

    //Send HTTP request
    char *reqStr = "HEAD / HTTP/1.0\r\n\r\n";
    if((status = send(sockfd, reqStr, len(reqStr), 0)) < 0) return status;

    //Handle http response
    char resp_buff[16] = "";
    int resp_size = recv(sockfd, resp_buff, sizeof(resp_buff), 0);
    if(resp_size <= 0) return resp_size;
    *(resp_buff+resp_size-1) = '\0';

    //Close socket
    shutdown(sockfd, 2);

    //parse output
    if((status = parseCode(resp_buff, return_code)) < 0) return status;

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