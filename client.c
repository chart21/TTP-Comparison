/*
** client.c -- a stream socket client demo
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include "sockethelper.h"
#define PORT "6000" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

 
void *receiver(void* threadParameters)
{
	int sockfd, numbytes;  
	//char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(((thargs_t*) threadParameters)->client, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			perror("client: connect");
			close(sockfd);
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		exit(2);
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure
   
    //signal main thread that connection was established
    printf("Locking conn \n");
    pthread_mutex_lock(&mtx_connection_established);
    printf("Locked conn \n");
    num_successful_connections += 1; 
    printf("Modyfying conn \n");
    pthread_mutex_unlock(&mtx_connection_established);
    printf("unlocked conn \n");
    pthread_cond_signal(&cond_successful_connection);
    printf("signal conn \n");
    //get start signal from main
    printf("Locking conn \n");
    pthread_mutex_lock(&mtx_connection_established);
    while (num_successful_connections != -1) {
        printf("unlocking conn and waiting for signal \n");
        pthread_cond_wait(&cond_successful_connection, &mtx_connection_established);
    }
        printf("done waiting \n");

    
    printf("start rec \n");
    if ((recv(sockfd, ((thargs_t*) threadParameters)->inputs, ((thargs_t*) threadParameters)->inputs_size, MSG_WAITALL)) == -1) {
	    perror("recv");
	    exit(1);
	}
    
    //signal main thread that data was received
    /* pthread_mutex_lock(&mtx_data_received); */
    /* num_data_received += 1; */ 
    /* pthread_mutex_unlock(&mtx_data_received); */
    /* pthread_cond_signal(&cond_data_received); */
    
	printf("client: received data \n");

	close(sockfd);


}

