###############################################################################################
Portsetter

Sets a port to listen on via a bash terminal

###############################################################################################
Initial Setup
Setting Needed Aliases in Cloud9
    1. Copy the bin folder to ~/workspace
        * you may need to update the .profile file in ~/ to read your bin file
            Make sure that your .profile contains the following:
                > if [ -d "$HOME/workspace/bin" ] ; then
                > PATH="$HOME/workspace/bin:$PATH"
                > fi
            
    2. Copy the portsetter folder to ~/workspace

Building the executable
    1. Open a new terminal
    2. cd into ~/workspace/portsetter
    3. run the command `make`


Running the tests (while in ~/workspace/portsetter)
    In the command line, run:
        >`tests`
    Note that the testing command requires the following line to be appended to the end of ~/.bashrc
        > echo MYPORT=4040
        
Setting the env variables
    There is not currently a .env file for the project
    Consider these two methods for setting envvars:
        1. If you want a session only env var
            Run the command before running the program
            >export KEY=value
        2. If you want a persistent envar
            in ~/.bashrc append to the end of file a line
            >export KEY=value

###############################################################################################
Running the Program (while in ~/workspace/portsetter)
    In the command line, type: 
        >`setport [options] [arguments]`

    No options/arguments will display the usage screen
        >
        > Usage: portsetter [options] [arguments]
        >
        > Options:
        >  -p, --port   	sets a port to listen on, must be followed by a valid port number
        >      -e [VAR_NAME]  used in conjuction with port to specify what env variable to draw the portnumber from
        >  -h, --help, -?	shows help interface
        >  -!, --about     displays a message about the developer
        >  -v, --version   displays the version number of this program
        >
        > Examples:
        >
        >   portsetter -p -e
        >   portsetter -p -e ENVAR_NAME
        >   portsetter --port 8080
        >   portsetter -p 8080
        >   portsetter --help
        >   portsetter -h
           
        > Exit codes:
        >   0 - Successful
        >   1 - Error in user input
        >   2 - Internal error
    
