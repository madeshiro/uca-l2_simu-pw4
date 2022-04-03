# Validation of Monte Carlo's Simulation #
> IT Project - Simulation - Practical Work #4 <br/>
>**vers. 1.0 pre-release (no gui implemented)**
* * *
*by Rin Baudelet | L2 Info* <br/>

## Program's guideline
The project is separate in multiple folders:
- src/ - contains all sources files
- include/ - contains all headers files
- webgui/ - contains all html/css/js sources for the application's web GUI
- report/ - contains Latex sources
- ./ - root of the project, Makefile, readme...

Compile the program using the makefile as usual
> **Compile**: `make`

> **Compile in debug-mode**: `make -e DEBUG=true`


## Launch the program
(default launch: witness run for the report)
> ./projectsi_pw4

(available under version 1.0 release (Gui))
> ./projectsi_pw4 [CMD] [OPTION...]

 
### Program's command
- `<default> [OPTIONS...]`
  - default options :
      - gui enable
- `run [month_duration=240] [replication=30] [OPTIONS...]`
  - default options :
    - gui disable
### Program's arguments
- `--help, -h`
  - display all available commands like decribe in this readme.md
- `--no-gui`
  - force disabling the Web GUI (mode console)
- `--gui, -g`
  - force enabling the Web GUI
- `--output, -o <output_folder>`
  - specify the output folder path (absolute or relative). Per default, the output folder will be [experience-uid] <br/> where `experience-uid` is a 128-bit Unique Identifier based on the initial state {duration, replication, MT init, SIM init}
- `--init, -i <init_file.json>`
  - specify the initial state or an eventual previously began simulation. <br/> The argument [month_duration] and [replication] will be ignored (already specified in the .json file)
- `--request, -r <male> <female>`
  - specify the number of male and female rabbits to use at N=0. If not specified through this option nor `--init` option, the application will ask you to specify it using WebGUI or console input.
- `--export, -e [month|year|final]`
  - (default : final)
  - specify the statistical file cache to export. e.g: `-e month,year` to export both month and year statistical values. <br/>per default, export format will be `application/json`; other format is a compressed file.
- `--read, -d <binfile>`
  - this argument should be used only to read a fully done experiment which you would like to export others statistical data that you may have forgotten. Per default and everytime, the application will create a binary "state file" that fully transcribe the simulation (each step, month by month)
  - incompatible with command:run !
- `--format, -f [format]` 
  - (default : application/json)
  - Format available :
    - `application/json`
    - `application/octet-stream`
- `--directory, -w <working_directory>`

### Example
- `projectsi_pw4 run 240 30 --r 4 4 -g`
  - run a simulation with 4 males and 4 females at N=0, making 30 replications of a 240 months lasting simulation. <br/> GUI Enable ! (your browser should open automatically displaying the overview index html page)
- `projectsi_pw4 --init "my_init.json"`
  - initialize the simulation using the file specified. The Web GUI should be opened automatically using an internet browser (firefox), displaying the apps overview html page. You can launch the simulation using the start button. 