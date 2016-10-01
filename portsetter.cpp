/*
    portsetter
    30-Aug-16
    Robert Stoddard
    Actual development time (2.5hrs)
     
    Exit codes:
        0 - Successful
        1 - Error in user input
        2 - Internal error (not implemented)
        
    Change Log:
        8 SEP 16
            - Added tests to accompany the program
            - Added readME to explain to user how to change the way that the program is called
            - Corrected status code on Bad Arguments fail case
        15 SEP 16
            - Added enum for constant values
            - Added logical routes for new paramters
                -? -! --about -v --version -e
            - seperated the usage and about screens into seperate txt files
            - added test case
*/

#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdlib.h>


using namespace std;

enum{
    //the following are stored values for constants
    SUCCESS = 0,
    ERROR = 1,
    NOT_FOUND = -1,
    NON_NUMBER = -2,
    BAD_PORT = -3,
    MIN_PORT_NUMBER = 1,
    MAX_PORT_NUMBER = 65535,
    //the following are for langauge standardization
    LISTENING_MSG = 0,
    BAD_ARGS_MSG = 1,
    BAD_PORT_MSG = 2,
    NOT_NUMBER_MSG = 3,
    UNEXPECTED_MSG = 4,
    VERSION_MSG = 5,
    CANT_OPEN_MSG = 6,
    CANT_PRINT_MSG = 7,
    ERROR_PRE_MSG = 8,
    ENVAR_RET_ERR = 9,
    ENVAR_NOT_NUM = 10,
    ENVAR_BAD_PORT = 11,
    USAGE_LOC = 12,
    ABOUT_LOC = 13
};

string en[] = {
    "listening on port ",
    "Bad arguments passed in, please see usage below",
    "The port you specified is not a valid port number",
    "invlaid port number entered",
    "Bad arguments passed in, unexpected parameter after -p/--port",
    "\nversion: 1.1.3a",
    "couldn't open file", 
    "couldn't print file",
    "ERROR: ",
    "Couldn't retrieve envar value",
    "envar value is not a number",
    "envar contains an invalid port number",
    "displays/portsetter.usage_en.txt",
    "displays/portsetter.about_en.txt"
};

string es[] = {
    "escuchando en el puerto ",
    "argumentos malas pasadas, por favor ver más abajo para el uso",
    "El puerto que ha especificado no es un puerto válido",
    "valor introducido no es un número",
    "Malos argumentos pasados, hay un parámetro inesperado",
    "\nversión: 1.1.3a",
    "No pudo abrir el archivo", 
    "No se puede imprimir el archivo",
    "ERROR: ",
    "No se pudo recuperar el valor de envar",
    "valor del envar no es un número",
    "envar contiene un número de puerto no válido",
    "displays/portsetter.usage_es.txt",
    "displays/portsetter.about_es.txt"
};


void usage();
void about();
void version();
void error(string);
void printFile(string);
bool getEnvPort(string, int&);
bool connect(int);
void printEnVarError(int);
string* setLanguage();

string* msg = setLanguage();

int main(int argc, char* args[]){
    if(argc == 1){
        usage();
        return SUCCESS;
    }
    if(argc > 4){
        error(msg[BAD_ARGS_MSG]);
        return ERROR;
    }
    string value = args[1];
    if((value == "--help" || value == "-h" || value == "-?") && argc == 2){
        usage();
        return SUCCESS;
    }
    if((value == "--about" || value == "-!") && argc == 2){
        about();
        return SUCCESS;
    }
    if((value == "--version" || value == "-v") && argc == 2){
        version();
        return SUCCESS;
    }
    int port;
    if((value == "--port" || value == "-p")){
        if(argc == 3){
            value = args[2];
            if(value == "-e")
            {
                if(getEnvPort("PORT", port)){
                    connect(port);
                    return SUCCESS;
                }
                else{
                    printEnVarError(port);
                    return ERROR;
                }
            }
            else{
                try{
                    port = stoi(value);
                    if(port < MIN_PORT_NUMBER || port > MAX_PORT_NUMBER) throw msg[BAD_PORT_MSG].c_str();
                    connect(port);
                    return SUCCESS;
                }
                catch(const char *e){
                    error(e);
                    return ERROR;
                }
                catch(const std::exception& e){
                    error(msg[NOT_NUMBER_MSG]);
                    return ERROR;
                }
            }
        }
        if(argc == 4){
            value = args[2];
            if(value == "-e"){
                value = args[3];
                if(getEnvPort(value, port)){
                    connect(port);
                    return SUCCESS;
                 }else{
                     printEnVarError(port);
                     return ERROR;
                 }
            }else{
                error(msg[UNEXPECTED_MSG]);
                return ERROR;
            }
        }
    }
    error(msg[BAD_ARGS_MSG]);
    return ERROR;
}

/*
    connect
    Purpose: connects the promram to the port
    Postconditions: prints a message as if the program connected to the specified port
    returns:    true - if successfully connected
                false - if failed to connect to the port
*/
bool connect(int port){
    //TODO: Connect to the port specified by the user
    cout << msg[LISTENING_MSG] << port << endl;
}

/*
    usage
    Purpose: provides user instructions on how to use the program
    Postconditions: An instruction menu is printed to the user on how to use the program
*/
void usage(){
    printFile(msg[USAGE_LOC]);
}

/*
    usage
    Purpose: provides user information about this program
    Postconditions: displays the about screen
*/
void about(){
    printFile(msg[ABOUT_LOC]);
}

/*
    version
    Purpose: provides user information about the version number of this project
    Postconditions: the version number is printed
*/
void version(){
    cout << msg[VERSION_MSG] << endl;
}

/*
    printFile
    Purpose: prints the contents of a text file out to the user
    Parameters:
        fileName - the name of the file to be printed (including relative path)
    Postconditions: The text file is echoed out to the console
*/
void printFile(string fileName){
    try{
        ifstream file;
        string x;
        
        file.open(fileName);
        if(!file){
            error(msg[CANT_OPEN_MSG]);
        }
        while(getline(file, x)){
            cout << x << endl;
        }
        file.close();
    }
    catch(exception e){
        error(msg[CANT_PRINT_MSG]);
    }
}

/*
    error
    Purpose: provides a standardized error output
    Parameters:
        message - the string that you would like to be displayed as the message for the error
    Postconditions: An error message is printed, followed by the usage screen
*/
void error(string message){
    cout << msg[ERROR_PRE_MSG] << message << endl;
    usage();
}

/*
    getEnvPort
    Purpose: retrieves the numeric value stored in the given enVar
    Parameters:
        varName: the name of the variable the value is stored in
        val: the reference to the number to be set
    Return: a bool telling if the value was successfully set or not
    Postconditions: 
        if successful - return true, val set to the value in the enVar
        if failed - return false & val set to NOT_FOUND for couldn't retrieve
                                              NON_NUMBER for bad value in envar
                                              BAD_PORT for not in valid port range
*/
bool getEnvPort(string varName, int& val){
    char* value = getenv(varName.c_str());
    if(value == NULL || value[0] == '\0'){
        val = NOT_FOUND;
        return false;
    }
    try{
        val = stoi(value);
        if(val < MIN_PORT_NUMBER || val > MAX_PORT_NUMBER) throw msg[BAD_PORT_MSG].c_str();
        return true;
    }
    catch(const char *e){
        val = BAD_PORT;
        return false;
    }
    catch(const std::exception& e){
        val = NON_NUMBER;
        return false;
    }
}

/*
    prinEnVarError
    Purpose: prints out what went wrong when trying to retrieve the envar
    Parameters: the int code representing the error that occured
    Postconditions: the cooresponding message is printed to the user for the given error code
*/
void printEnVarError(int errorCode){
    if(errorCode == NOT_FOUND){
        error(msg[ENVAR_RET_ERR]);
        return;
    }
    if(errorCode == NON_NUMBER){
        error(msg[ENVAR_NOT_NUM]);
        return;
    }
    if(errorCode == BAD_PORT){
        error(msg[ENVAR_BAD_PORT]);
        return;
    }
}

/*
    setLanguage
    purpose: checks the environment variables for the language to use
    postconditions: a language is selected and a message displayed if there were errors
        if any errors occur, english is selected
*/
string* setLanguage(){
    string varNames[] = {
      "LANGUAGE",
      "LC_ALL",
      //"LC_MESSAGES",
      "LANG"
    };
    int NUM_VARS = 3;
    
    std::regex re("^([a-z]{2})(_[A-Z]{2})?(.UTF-8)?$");
    std::smatch match;
    
    string locale = "";
    int pos = 0;
    while((locale == "" || locale == "C" || locale == "C.UTF-8") && pos < NUM_VARS){
        try{
            locale = getenv(varNames[pos].c_str());
            const auto &line = locale;
            if(std::regex_search(line.begin(), line.end(), match, re)){
                if(match[1] == "en") return en;
                if(match[1] == "es") return es;
                cout << match[1] << " translation not recognized, defaulting to english" << endl;
                return en;
            }
            else{
                if (locale != "" && locale != "C" && locale != "C.UTF-8"){
                    cout << "Bad language specification in environment variable " << varNames[pos] << "=" << locale << " Using English." << endl;
                    return en;
                }
            }
        }catch(exception e){
            //do nothing
        }
        pos++;
    }
    
    cout << "No locale value, defaulting to english" << endl;
    return en;
    
    return en;
}