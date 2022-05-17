/* Ashton Gray
 * Grady Sullivan
 * Project 5
 * client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

int main(int argc, char **argv) 
{
    int clientfd;
    char *num1, *num2;
    char *host, *port;
    rio_t rio;
    char buf[MAXLINE];
    char xml[MAXLINE];
    char *ptr;
    char num;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        exit(0);
    }

    num1 = argv[1];
    num2 = argv[2];

    host = "localhost";
    port = "8080";

    clientfd = Open_clientfd(host, port);

    // xml
    sprintf(xml,"<?xml version='1.0'?>\r\n"
		 "<methodCall>\r\n"
		 "<methodName>sample.addmultiply</methodName>\r\n"
		 "<params>\r\n"
		 "<param>\r\n"
		 "<value><double>%s</double></value>\r\n"
		 "</param>\r\n"
		 "<param>\r\n"
		 "<value><double>%s</double></value>\r\n"
		 "</param>\r\n"
		 "</params>\r\n"
		 "</methodCall>\n\n",num1,num2);

    // buffer (including header)
    sprintf(buf, "POST /RPC2 HTTP/1.1\r\n"
    		 "Content-Type: text/xml\r\n"
		 "User-Agent: XML-RPC.NET\r\n"
    		 "Content-Length: %d\r\n"
		 "Expect: 100-continue\r\n"
		 "Connection: Keep-Alive\r\n"
		 "Host: localhost:8080\r\n\n%s",strlen(xml),xml);

    //printf("%s", buf);

    /* 
	Write your code here.
	Recommend to use the Robust I/O package.
    */

    Rio_writen(clientfd, buf, sizeof(buf));

    Rio_readinitb(&rio, clientfd);

    while (Rio_readlineb(&rio, buf, sizeof(buf)) > 0){
	if((ptr = strstr(buf,"double")) != NULL){ // searches for "double"
		ptr = ptr + 7;
		num = *ptr;
		while(num != '<'){		
			printf("%c",(num));
			ptr++;
			num = *ptr;
		}
		printf("   ");
		
	}
	//printf("%s\n", buf);
	
	
    };
    printf("\n");

   
    Close(clientfd);
    exit(0);
}






