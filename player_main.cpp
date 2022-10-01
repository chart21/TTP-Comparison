#include <fstream>
#include <string>
#include <pthread.h>
#include "programs.hpp"
#include "server.c"
#include "sockethelper.h"
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
        printf("ERROR; Not enoguh inputs in player file.");
        playerinput.close();
        exit(-5);
        }
  
   playerinput.close();
}


int main(int argc, char *argv[])
{
int player_id = atoi(argv[1]);


int inputLength[] = INPUTSLENGTH;
DATATYPE* inputs = new DATATYPE[inputLength[1]]; //create n pointers, each to hold a player's input

readInputFromFile(inputs,player_id,inputLength[1]);

thargs_p thrgs;
thrgs.inputs = (char*) inputs;
thrgs.inputs_size = sizeof(DATATYPE) * inputLength[1];
thrgs.port = base_port + player_id;

sender(&thrgs);

return 0;
}
