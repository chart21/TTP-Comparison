#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -b base_port -n num_inputs -t datatype -p num_input_players -f function_name -o operator -i input_length"
   echo -e "Only arguments you want to change have to be set."
   echo -e "\t-b base_port: Needs to be the same for all players for successful networking (e.g. 6000)"
   echo -e "\t-n Number of elements of party 0 (e.g. 100)"
   echo -e "\t-t Datatype of the inputs (e.g. int/float/...)"
   echo -e "\t-p Number of players submitting inputs (e.g. 3)"
   echo -e "\t-f Name of the function to execute (e.g. pSearch)"
   echo -e "\t-o Operator to use for some functions (e.g. +/*)"
   echo -e "\t-i Number of elements per party in order if not the same as -n (e.g. 100,1)"
   exit 1 # Exit script after printing help
}

while getopts "b:n:t:p:f:o:i:" opt
do
   case "$opt" in
      b ) base_port="$OPTARG" ;;
      n ) num_inputs="$OPTARG" ;;
      t ) datatype="$OPTARG" ;;
      p ) num_input_players="$OPTARG" ;;
      f ) function_name="$OPTARG" ;;
      o ) operator="$OPTARG" ;;
      i ) input_length="$OPTARG" ;;
      ? ) helpFunction ;; # Print helpFunction in case parameter is non-existent
   esac
done

# Print helpFunction in case parameters are empty
# if [ -z "$parameterA" ] || [ -z "$parameterB" ] || [ -z "$parameterC" ]
# then
#    echo "Some or all of the parameters are empty";
#    helpFunction
# fi

# Begin script in case all parameters are correct

if [ ! -z "$base_port" ]
then
    sed -i -e "s/\(base_port \).*/\1$base_port/" config.h
fi
if [ ! -z "$num_inputs" ]
then
    sed -i -e "s/\(num_inputs \).*/\1$num_inputs/" config.h
fi
if [ ! -z "$datatype" ]
then
    sed -i -e "s/\(DATATYPE \).*/\1$datatype/" config.h
fi
if [ ! -z "$num_input_players" ]
then
    sed -i -e "s/\(input_players \).*/\1$num_input_players/" config.h
fi
if [ ! -z "$function_name" ]
then
    sed -i -e "s/\(performFunction \).*/\1$function_name/" config.h
fi
if [ ! -z "$operator" ]
then
    sed -i -e "s/\(op \).*/\1$operator/" config.h
fi
if [ ! -z "$input_length" ]
then
    sed -i -e "s/\(INPUTSLENGTH \).*/\1\{$input_length\}/" config.h
fi

