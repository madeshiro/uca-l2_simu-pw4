# Validation of Monte Carlo's Simulation #
> IT Project - Simulation - Practical Work #4
* * *
*by Rin Baudelet | L2 Info*

## Program's guideline
The project is separate in multiple folders:
- src/ - contains all sources files
- include/ - contains all headers files 
- report/ - contains Latex sources
- ./ - root of the project, Makefile, readme...

Compile the program using the makefile as usual
> **Compile**: `make`

> **Compile in debug-mode**: `make -e DEBUG=true`


## Launch the program
> projectsi_pw4 [CMD] [OPTION...]

### Program's command
- `<default> [OPTIONS...]`
  - default options :
      - gui enable
      - master
- `run [month_duration=24] [replication=10 000 000] [OPTIONS...]`
  - default options :
    - gui enable [simulation preview]
    - master
- `slave [master:ip] [master:port] [OPTIONS...]`
  - default options :
    - gui disable
    - slave
### Program's arguments
- `--help, -h`
- `--no-gui`
- `--gui, -g`
- `--slaves, -s=[ip:port,...]` // possibility to add slaves during simulation process