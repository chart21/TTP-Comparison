#pragma once
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
pthread_mutex_t mtx_connection_established;
pthread_cond_t cond_successful_connection;
int num_successful_connections = 0;

pthread_mutex_t mtx_data_received;
pthread_cond_t cond_data_received;
int num_data_received = 0;



pthread_mutex_t dataToSend;
pthread_mutex_t startSignal;
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

typedef struct thread_arguments {
  int threadID;
  char *inputs;
  int inputs_size;
  char *client;
  char *hostname;
  //char *data;
  //char *length
} thargs_t;


