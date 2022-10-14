# Perform a Secure Mulitparty Computation using a Trusted Third Party (TTP)
This repository can be used as a benchmark to compare a Secure Mulitparty Computation protocol with a TTP solution. The TTP receives inputs from the other players in parallel over network sockets. It then performs the computation in plaintext. The TTP can be either an external party or hold its own inputs as P0.

## Usage
First configure the program using config.sh then compile ttp_main.cpp and player_main.cpp. Local inputs of each player are fetched from the Player-Data folder.

### Configuaration
Run config.sh with your desired parameters. You can also manually edit the config.h file.

```
Usage: ./config.sh -b base_port -t ttp_is_input_party -d datatype -p num_input_players -f function_name -o operator -i input_length
Only arguments you want to change have to be set.
        -b base_port: Needs to be the same for all players for successful networking (e.g. 6000)
        -t 1 -> TTP is Player 0 and supplies inputs, 0 -> TTP is external party
        -d Datatype of the inputs (e.g. int/float/...)
        -p Number of players submitting inputs (e.g. 3)
        -f Name of the function to execute (e.g. pSearch)
        -o Operator to use for some functions (e.g. +/*)
        -i Number of elements per party in order (e.g. 100,1)
```

The following configuration uses port 6000 as base port, uses the TTP as an external party, int as datatype, 2 input players (P0,P1), performs function psearch and uses the following number of elements 100 (P0),1 (P1). 
> ./config.sh -b 6000 -t 0 -d int -p 2 -f psearch -i 100,1

The following configuration uses the previous configuration but performs function array_ops with operator + and 50 inputs per player.
> ./config.sh -f array_ops -o + -i 50,50

The following configuration uses the previous configuration but changes number of players to 3.
> ./config.sh -p 3 -i 50,50,50

The following configuration uses the previous configuration but lets the TTP act as Player 0 (supplying its own inputs).
> ./config.sh -t 1

### Compilation
Compile TTP.
> g++ ttp_main.cpp -o ttp_main.o -lpthread -Ofast

Compile player.
> g++ player_main.cpp -o player_main.o -Ofast

### Execution
Execute P0 executable. (Assuming TTP is set to external via -t 0)
> ./player_main.o 0

Execute P1 executable.
> ./player_main.o 2

...

Execute TTP executable. Not setting an IP address defaults to localhost.
> ./ttp_main.o ip_address_P0 ip_address_P1 ...

## Example

Config.

```C
#define base_port 6000
#define ttp_is_input_party 1
#define DATATYPE int
#define input_players 3
#define performFunction array_ops
#define op +
#define INPUTSLENGTH {4,4,4}
```

P0 output after execution.

```
TTP: Acting as input party P0
TTP: Attempting to connect to Player 1 ...
TTP: Attempting to connect to Player 2 ...
TTP: Connected to Player 1
TTP: Connected to Player 2
All clients connected sucessfully, starting protocol and timer!
92 59 83 98
Time measured to read and receive inputs: 0.000364s
Time measured to perform computation: 0.000034s
Time measured in total: 0.000398s
```

After running `config.sh -t 0` and executing.

```
TTP: Acting as an external party
TTP: Attempting to connect to Player 0 ...
TTP: Attempting to connect to Player 1 ...
TTP: Attempting to connect to Player 2 ...
TTP: Connected to Player 1
TTP: Connected to Player 0
TTP: Connected to Player 2
All clients connected sucessfully, starting protocol and timer!
92 59 83 98
Time measured to read and receive inputs: 0.000412s
Time measured to perform computation: 0.000036s
Time measured in total: 0.000448s
```

### Features to be added

- SSL Encryption.
- Communication in network-byte order (Systems with different endianness are not supported currently).

