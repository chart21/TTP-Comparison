#include <iostream>
#include <vector>
#include "config.h"
int inputLength[] = INPUTSLENGTH;

//Always 2 input players
void psearch(DATATYPE** inputs)
{
    DATATYPE result = 0;
    for(int i = 0; i < inputLength[0]; i++)
    {
        if(inputs[0][i] == inputs[1][0])
            result = 1;
    }
    std::cout << result << "\n";
}

//Always 2 inputs players 
void set_intersection(DATATYPE* inputs[input_players])
{
    DATATYPE result[inputLength[0]] = {0};
    for(int i = 0; i < inputLength[0]; i++)
        {
            for(int j = 0; j < inputLength[1]; j++)
        {
            if(inputs[0][i] == inputs[1][j])
               result[i] = 1; 
        }
        std::cout << result[i] << ", ";
        }
    std::cout << "\n";
}

// N input players
void array_ops(DATATYPE* inputs[input_players])
{
    DATATYPE result;
    for(int i = 0; i < inputLength[0]; i++) {
        result = inputs[0][i];
        for (int j = 1; j < input_players; j++) {
            
        result = result op inputs[j][i];        
        }
        std::cout << result << " ";
    }
    std::cout << "\n";
}
