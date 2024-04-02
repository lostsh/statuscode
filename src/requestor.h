/**
* \file requestor.h
* \version 1.0 beta
* \author Vernhes Yohann (lostsh)
* \date 1 april 2024
* \brief requestor lib to send HTTP request
* requestor module header file
*/

#ifndef REQUESTOR_H
#define REQUESTOR_H

int getHttpCode(const char *target_ip, char *return_code);
int parseCode(const char*, char*);

typedef unsigned short int wlen_t;
wlen_t len(const char*);

#endif /*REQUESTOR_H*/