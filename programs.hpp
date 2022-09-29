#include <iostream>
#include <vector>
#include "config.h"
void psearch(DATATYPE** inputs)
{
    DATATYPE result = 0;
    for(int i = 0; i < num_inputs; i++)
    {
        if(inputs[0][i] == inputs[1][0])
            result = 1;
    }
    std::cout << result << "\n";
}

void set_intersection(DATATYPE* inputs[input_players])
{
    DATATYPE result[num_inputs] = {0};
    for(int i = 0; i < num_inputs; i++)
        {
            for(int j = 0; j < num_inputs; j++)
        {
            if(inputs[0][i] == inputs[1][j])
               result[i] = 1; 
        }
        std::cout << result[i] << "\n";
        }
}

void array_ops(DATATYPE* inputs[input_players])
{
    DATATYPE result;
    for(int i = 0; i < num_inputs; i++) {
        result = inputs[0][i];
        for (int j = 1; j < input_players; j++) {
            
        result = result op inputs[j][i];        
        }
        std::cout << result << "\n";
    }
}
