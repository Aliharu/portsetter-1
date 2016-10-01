/*
    portsetter test
    8-Sep-16
    Robert Stoddard

    Purpose: Allows the user to test inputs given to portsetter
                conditions to test are hardcoded.
     
    Exit codes:
        0 - Successful
        1 - One or more of the tests failed
        
    Note: ./portsetter is called directly because it is a more reliable path to call than navigating via some alias
*/

#include <iostream>
#include <string>

using namespace std;

const string OBJECT_NAME = "./portsetter";
const string ALIAS_NAME = "setport";

bool test(string, int, string);

int main(int argc, char* args[]){
    
    bool successful = true;
    
    //if(test fails) throw fail flag
    //happy paths
    if(!test(OBJECT_NAME, 0, "help.txt")) successful = false;
    if(!test(OBJECT_NAME + " -h", 0, "help.txt")) successful = false;
    if(!test(OBJECT_NAME + " -?", 0, "help.txt")) successful = false;
    if(!test(OBJECT_NAME + " --help", 0, "help.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p 1010", 0, "port1010.txt")) successful = false;
    if(!test(OBJECT_NAME + " --port -e", 0, "port8080.txt")) successful = false;
    if(!test("export MY_PORT=4040 && " + OBJECT_NAME + " --port -e MY_PORT", 0, "port4040.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p -e", 0, "port8080.txt")) successful = false;
    if(!test("export MY_PORT=4040 &&" + OBJECT_NAME + " -p -e MY_PORT", 0, "port4040.txt")) successful = false;
    if(!test(OBJECT_NAME + " --about", 0, "about.txt")) successful = false;
    if(!test(OBJECT_NAME + " -!", 0, "about.txt")) successful = false;
    if(!test(OBJECT_NAME + " --version", 0, "version.txt")) successful = false;
    if(!test(OBJECT_NAME + " -v", 0, "version.txt")) successful = false;
    
    //test that spanish works
    if(!test("export LANG=es && " + OBJECT_NAME + " --port -e", 0, "es8080.txt")) successful = false;
    
    
    //sad paths
    if(!test(OBJECT_NAME + " help", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -help", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " --h", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -h --help", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -hs", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p --port 9", 1, "badPortArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p 77 33", 1, "badPortArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p -21", 1, "badPort.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p 0", 1, "badPort.txt")) successful = false;
    if(!test(OBJECT_NAME + " --port", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p 90642", 1, "badPort.txt")) successful = false;
    if(!test(OBJECT_NAME + " -x 45321", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -P 714", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -version", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -about", 1, "badArgs.txt")) successful = false;
    if(!test(OBJECT_NAME + " -p -e NOT_AN_ENVAR", 1, "notAnEnVar.txt")) successful = false;
    if(!test("export BAD_ENVAR=-234 && " + OBJECT_NAME + " -p -e BAD_ENVAR", 1, "enVarBadPort.txt")) successful = false;
    if(!test("export BAD_ENVAR=465465 && " + OBJECT_NAME + " -p -e BAD_ENVAR", 1, "enVarBadPort.txt")) successful = false;
    if(!test("export BAD_ENVAR=Hello && " + OBJECT_NAME + " -p -e BAD_ENVAR", 1, "enVarNotNumber.txt")) successful = false;
    
    //test to make sure that the alias works
    if(!test(ALIAS_NAME, 0, "help.txt")){
      successful = false;
      cout << "program not successfully running via alias: " << ALIAS_NAME << " Check that you've updated the profile to point to the bin file"<< endl;
    } 
    
    //remove the test file (no longer needed)
    system("rm test.txt");
    
    if(successful){
        cout << "All Tests Passed Successfully" << endl;
        return 0;
    }
    else{
        cout << "\n\nOne or more tests failed, see above for details" << endl;
        return 1;
    }
    
}


/*
    test
    Allows a standardized way method to test the program with parameters
    Parameters:
        command: A string representing the command that would be entered into the command line
        expectedStatus: An int representing the status that the command is expected to return
        expectedFileName: The name of the file that contains the text that the command is expected to output to the console
    Returns:
        true - if the command was executed has both the expected status and the expected output
        false - if the command fails or behaves unexpectedly in either its status or output
*/
bool test(string command, int expectedStatus, string expectedFileName){
    
    string inputTestCommand =  command + " > test.txt";
    string outPutTestCommand = "diff test.txt testData/" + expectedFileName;
    
    int status = system(inputTestCommand.c_str())/256;
    if(status != expectedStatus){
        cout << "ERROR: " << command << " returned status: " << status << " expected status: " << expectedStatus << endl;
        return false;
    } 
    
    if(system(outPutTestCommand.c_str()) != 0){
        cout << "ERROR: " << command << " has bad output: (see compared outputs directly above)\n" << endl;
        return false;
    } 
    
    return true;
}