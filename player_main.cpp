#include <fstream>
#include <string>
#include <pthread.h>
#include "programs.hpp"
#include "server.c"
#include "sockethelper.h"
#include "time.h"
void readInputFromFile(DATATYPE inputs[],int playerID,int input_length)
{
    std::ifstream playerinput("Player-Data/Input-P" + std::to_string(playerID) + "-0");
    if (!playerinput.is_open())
        std::cout << "Error reading from file \n";

    int i = 0;
    DATATYPE single_input;
    while (playerinput >> single_input)
    {
        if(i == input_length)
            break;
        inputs[i] = single_input;
        i++;
    }
    if(i < input_length) {
        printf("ERROR; Not enough inputs in player file.");
        playerinput.close();
        exit(-5);
        }
  
   playerinput.close();
}


int main(int argc, char *argv[])
{
int player_id = atoi(argv[1]);


int inputLength[] = INPUTSLENGTH;
DATATYPE* inputs = new DATATYPE[inputLength[player_id]]; 

clock_t time_application_start = clock ();
readInputFromFile(inputs,player_id,inputLength[player_id]);
clock_t time_input_read = clock ();
thargs_p thrgs;
thrgs.inputs = (char*) inputs;
thrgs.inputs_size = sizeof(DATATYPE) * inputLength[player_id];
thrgs.port = base_port + player_id;

sender(&thrgs);
clock_t time_computation_finished = clock ();
printf("Time measured to read player input: %fs \n", double((time_input_read - time_application_start)) / CLOCKS_PER_SEC);
printf("Time measured to send player input: %fs \n", double((time_computation_finished - time_input_read)) / CLOCKS_PER_SEC);
printf("Time measured in total: %fs \n", double((time_computation_finished - time_application_start)) / CLOCKS_PER_SEC);
return 0;
}
