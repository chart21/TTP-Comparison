#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -b base_port -n num_inputs -t datatype -p num_input_players -f function_name -o operator -i input_length"
   echo -e "\t-a Description of what is parameterA"
   echo -e "\t-b Description of what is parameterB"
   echo -e "\t-c Description of what is parameterC"
   exit 1 # Exit script after printing help
}

while getopts "b:n:t:p:f:o:i:" opt
do
   case "$opt" in
      b ) base_port="$OPTARG" ;;
      n ) num_inputs="$OPTARG" ;;
      t ) datatype="$OPTARG" ;;
      p ) base_port="$OPTARG" ;;
      f ) num_inputs="$OPTARG" ;;
      o ) datatype="$OPTARG" ;;
      i ) base_port="$OPTARG" ;;
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
    sed -i -e "s/\(input_players \).*/\1$input_players/" config.h
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
    sed -i -e "s/\(INPUTSLENGTH \).*/\1$input_length/" config.h
fi

