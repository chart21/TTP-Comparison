//server (TTP) code
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <pthread.h>
#include "programs.hpp"
#include "networking.hpp"
#include "sockethelper.h"
void receiveInputFromNetwork(std::vector<DATATYPE> inputs, int playerID)
{

}

void readInputFromFile(DATATYPE inputs[],int playerID)
{
    std::ifstream playerinput("Player-Data/Input-P" + std::to_string(playerID) + "-0");
    if (!playerinput.is_open())
        std::cout << "Error reading from file";

    int i = 0;
    while (playerinput >> inputs[i])
    {
        i++;
    }
    playerinput.close();
}


int main()
{

DATATYPE** inputs = new DATATYPE*[input_players]; //create n pointers, each to hold a player's input
int inputLength[] = INPUTSLENGTH;
for (int i = 0; i < input_players; i++) {
   inputs[i] = new DATATYPE[inputLength[i]]; // initialize arrays of each player with a size 
}


/* std::vector<DATATYPE> inputs[input_players]; */    
pthread_t threads[input_players];
thargs_t thrgs[input_players];
int ret;
printf("creating receiving servers\n");
for(int t=0;t<(input_players-1);t++) {
    thrgs[t].inputs = (char*) &inputs[t];
    thrgs[t].inputs_size = sizeof(DATATYPE) * inputLength[t-1];
    thrgs[t].threadID = t;
    thrgs[t].client = (char*)"127.0.0.1";
    thrgs[t].hostname = (char*)"hostname";
    std::cout << "In main: creating thread " << t << "\n";
    ret = pthread_create(&threads[t], NULL, receiver, &thrgs[t]);
    if (ret){
        printf("ERROR; return code from pthread_create() is %d\n", ret);
        exit(-1);
        }
}

// waiting until all threads connected
while (num_successful_connections < (input_players -1)) {
pthread_cond_wait(&cond_successful_connection, &mtx_connection_established);
num_successful_connections = -1; //after condition variable is sucessful, not thread will lock the mutex
pthread_cond_signal(&cond_successful_connection); //signal threads to start receiving
        
}




// read inputs of player 0
readInputFromFile(inputs[0],0);


//wait until received data from all players
while (num_data_received < (input_players -1)) {
pthread_cond_wait(&cond_data_received, &mtx_data_received);
}


/* for(int t=1;t<input_players;t++) { */
/* receiveInputFromNetwork(inputs[t],t); */
/* } */

// receive inputs of the other players
/* for(int i = 1; i < input_players; i++) */
/*    inputs[i] = receiveInputFrom(i,inputs,numInputs); */

/* inputs = receiveInputs() */



performFunction(inputs);

pthread_mutex_destroy(&mtx_connection_established);
pthread_cond_destroy(&cond_successful_connection);
pthread_mutex_destroy(&mtx_data_received);
pthread_cond_destroy(&cond_data_received);



return 0;
}
