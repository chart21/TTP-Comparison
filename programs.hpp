#include <iostream>
#include <vector>
#define num_inputs 32
#define DATATYPE int
#define input_players 2
#define performFunction psearch
#define op +
#define INPUTSLENGTH {100,1}

void psearch(DATATYPE* inputs[input_players])
{
    DATATYPE result = 0;
    for(int i = 1; i < num_inputs; i++)
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
    for(int i = 1; i < num_inputs; i++) {
        result = inputs[0][i];
        for (int j = 0; j < input_players; j++) {
            
        result op inputs[j][i];        
        }
        std::cout << result << "\n";
    }
}
