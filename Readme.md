# Perform a Secure Mulitparty Computation using a Trusted Third Party (TTP)
This repository can be used as a benchmark to compare a Secure Mulitparty Computation protocol with a TTP solution. Player 0 acts as a TTP and receives inputs from the other players in parallel over network sockets. P0 then performs the computation in plaintext.

## Usage
First configure the program using config.sh then compile ttp_main.cpp and player_main.cpp. Local inputs of each player are fetched from the Player-Data folder.

### Configuaration
Run config.sh with your desired parameters.

```
Usage: ./config.sh -b base_port -n num_inputs -t datatype -p num_input_players -f function_name -o operator -i input_length
Only arguments you want to change have to be set.
        -b base_port: Multiple ports will be used for networking (e.g. 6000)
        -n Number of elements of party 0 (e.g. 100)
        -t Datatype of the inputs (e.g. int/float/...)
        -p Number of players submitting inputs (e.g. 3)
        -f Name of the function to execute (e.g. pSearch)
        -o Operator to use for some functions (e.g. +/*)
        -i Number of elements per party in order if not the same as -n (e.g. 100,1)
```

The following configuartion uses port 6000 as base port, uses 100 inputs, int as datatype, 2 input players (P0-P1), performs function psearch and uses the following number of elements 100 (P0),1 (P1). 
> ./config.sh -b 6000 -n 100 -t int -p 2 -f psearch -i 100,1

The following configuartion uses the previous configuration but performs function array_ops with operator + and 50 inputs per player.
> ./config.sh -n 50 -f array_ops -o +

The following configuartion uses the previous configuration but changes number of players to 3.
> ./config.sh -p 3

### Compilation
Compile TTP.
> g++ ttp_main.cpp -o ttp_main.o -lpthread

Compile player.
> g++ player_main.cpp -o player_main.o -g

### Execution
Execute P1 executable.
> ./player_main.o 1

Execute P2 executable.
> ./player_main.o 2

...

Execute P0 (TTP) executable. Not setting an ip address defaults to localhost.
> ./ttp_main.o ip_address_P1 ip_address_P2 ...

## Example

Config.
```C
#define base_port 6000
#define num_inputs 4
#define DATATYPE int
#define input_players 3
#define performFunction array_ops
#define op +
#define INPUTSLENGTH {4,4,4}
```

P0 output after execution.
```
Player 0: Attempting to connect to Player 1 ...
Player 0: Attempting to connect to Player 2 ...
Player 0: Connected to Player 2
Player 0: Connected to Player 1
All clients connected sucessfully, starting protocol and timer!
9 14 17 14
Time measured to read and receive inputs: 0.000359s
Time measured to perform computation: 0.000035s
Time measured in total: 0.000394s
```
### Features to be added
- SSL Encryption.
- Communication in network-byte order (Systems with different endianness are not supported currently).
