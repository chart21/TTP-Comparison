#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <chrono>
#include "programs.hpp"
#include "networking.hpp"
#include "sockethelper.h"
#include "time.h"

void readInputFromFile(DATATYPE** inputs,int playerID, int input_length)
{
    std::ifstream playerinput("Player-Data/Input-P" + std::to_string(playerID) + "-0");
    if (!playerinput.is_open())
        std::cout << "Error reading from file";

    int i = 0;
    DATATYPE single_input;

    while (playerinput >> single_input)
    {
        if(i == input_length)
            break;
        inputs[0][i] = single_input;
        i++;
    }
    if(i < input_length) {
        printf("ERROR; Not enoguh inputs in player file.");
        playerinput.close();
        exit(-5);
        }
   playerinput.close();
}


int main(int argc, char *argv[])
{
if(ttp_is_input_party == 1)
    printf("TTP: Acting as input party P0 \n");
else
    printf("TTP: Acting as an external party \n");
char* ips[input_players-ttp_is_input_party];
//char* hostnames[input_players-1];
for(int i=0; i < input_players -ttp_is_input_party; i++)
{
    if(i < (argc - 1))
        ips[i] = argv[i+1];
    else
        ips[i] = (char*) "127.0.0.1";
}
pthread_mutex_init(&mtx_connection_established, NULL);
pthread_mutex_init(&mtx_start_communicating, NULL);
pthread_cond_init(&cond_successful_connection, NULL);
pthread_cond_init(&cond_start_signal, NULL);
DATATYPE** inputs = new DATATYPE*[input_players]; //create n pointers, each to hold a player's input
int inputLength[] = INPUTSLENGTH;
for (int i = 0; i < input_players; i++) {
   inputs[i] = new DATATYPE[inputLength[i]]; // initialize arrays of each player with a size 
}


/* std::vector<DATATYPE> inputs[input_players]; */    
pthread_t threads[input_players - ttp_is_input_party];
thargs_t thrgs[input_players - ttp_is_input_party];
int ret;
/* printf("creating receiving servers\n"); */
for(int t=0;t<(input_players-ttp_is_input_party);t++) {
    thrgs[t].num_players = input_players - ttp_is_input_party;
    thrgs[t].inputs = (char*) inputs[t+ttp_is_input_party];
    thrgs[t].inputs_size = sizeof(DATATYPE) * inputLength[t+ttp_is_input_party];
    thrgs[t].player_id = t+ttp_is_input_party;
    thrgs[t].ip = ips[t];
    thrgs[t].hostname = (char*)"hostname";
    thrgs[t].port = (int) base_port + (t+ttp_is_input_party);
    /* std::cout << "In main: creating thread " << t << "\n"; */
    ret = pthread_create(&threads[t], NULL, receiver, &thrgs[t]);
    if (ret){
        printf("ERROR; return code from pthread_create() is %d\n", ret);
        exit(-1);
        }
}

// waiting until all threads connected

/* printf("m: locking conn \n"); */
pthread_mutex_lock(&mtx_connection_established);
/* printf("m: locked conn \n"); */
while (num_successful_connections < (input_players - ttp_is_input_party)) {
/* printf("m: unlocking conn and waiting \n"); */
pthread_cond_wait(&cond_successful_connection, &mtx_connection_established);
}
/* printf("m: done waiting, modifying conn \n"); */
num_successful_connections = -1; 
pthread_cond_broadcast(&cond_start_signal); //signal all threads to start receiving
printf("All clients connected sucessfully, starting protocol and timer! \n");
pthread_mutex_unlock(&mtx_connection_established);
/* printf("m: unlocked conn \n"); */

std::chrono::high_resolution_clock::time_point c1 =
        std::chrono::high_resolution_clock::now();
clock_t time_application_start = clock ();


 


// read inputs of TTP if it is an input party
if(ttp_is_input_party)
    readInputFromFile(inputs,0,inputLength[0]);


//wait until received data from all players
/* while (num_data_received < (input_players -1)) { */
/* pthread_cond_wait(&cond_data_received, &mtx_data_received); */
/* } */


/* for(int t=1;t<input_players;t++) { */
/* receiveInputFromNetwork(inputs[t],t); */
/* } */

// receive inputs of the other players
/* for(int i = 1; i < input_players; i++) */
/*    inputs[i] = receiveInputFrom(i,inputs,numInputs); */

/* inputs = receiveInputs() */

                

/* printf("m: attempting join \n"); */
for(int t=0;t<(input_players-ttp_is_input_party);t++) {
    pthread_join(threads[t],NULL);
}
clock_t time_data_received = clock ();
//printf("Player 0: Received all data, starting computation \n");

performFunction(inputs);
clock_t time_computation_finished = clock ();
double time = std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::high_resolution_clock::now() - c1)
                     .count();
printf("Time measured to read and receive inputs: %fs \n", double((time_data_received - time_application_start)) / CLOCKS_PER_SEC);
printf("Time measured to perform computation: %fs \n", double((time_computation_finished - time_data_received)) / CLOCKS_PER_SEC);
printf("Time measured in total (Clock_t): %fs \n", double((time_computation_finished - time_application_start)) / CLOCKS_PER_SEC);
printf("Time measured in total (Chrono): %fs \n", time / 1000000);
pthread_mutex_destroy(&mtx_connection_established);
pthread_mutex_destroy(&mtx_start_communicating);
pthread_cond_destroy(&cond_successful_connection);



return 0;
}
