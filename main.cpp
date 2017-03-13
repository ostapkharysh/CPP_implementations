#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;

#define PATH_MAX 4096

char *curr_dir = (char *) "/usr/bin";
/*
string comm;
string argum;
int splitting(string l) {
    string arr[3];
    int i = 0;
    stringstream ssin(l);
    while (ssin.good() && i < 3) {
        ssin >> arr[i];
        ++i;
        if(i == 3){
            printf("ERROR : TU DAUN! TAK NE MOZNA PYSATY.");
            return -1;
        }
    }
    comm = arr[0];
    argum = arr[1];
    cout << comm << endl;
    cout << argum;
    return 0;
}*/

string command;
string args;
void splitString( string line){
    int i = 0;
    while(i != sizeof(line)){
        if(line[i] == ' '){
            command = line.substr(0,i);
            args = line.substr(i+1, sizeof(line));
            break;
        }else{
            command = line;
        }
        i++;
    }}

int cd(){
    string command;
    string args;
    chdir(args.c_str());
    curr_dir += 'args';

    return 0;

}

int Myls(){

    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;

    dp = opendir((const char*)curr_dir);
    if(NULL == dp)
    {
        printf("\n ERROR : Could not open the working directory\n");
        return -1;
    }

    for(count = 0; NULL != (dptr = readdir(dp)); count++)
    {
        // Check if the name of the file/folder begins with '.'
        // If yes, then do not display it.
        if(dptr->d_name[0] != '.')
            printf("%s  ",dptr->d_name);
    }

    return 0;
}


int doLS(){

    // Show prompt.
    cout << curr_dir << "$";
    char command[128];
    cin.getline( command, 128 );

    vector<char*> args;
    char* prog = strtok( command, " " );
    char* tmp = prog;
    while ( tmp != NULL )
    {
        args.push_back( tmp );
        tmp = strtok( NULL, " " );
    }

    char** argv = new char*[args.size()+1];
    for ( int k = 0; k < args.size(); k++ )
        argv[k] = args[k];

    argv[args.size()] = NULL;


    if ( strcmp( command, "exit" ) == 0 )
    {
        return 0;
    }
    else
    {
        if (!strcmp (prog, " ") & (argv[1] == NULL))
        {
            Myls();

        }
        else
        {
            pid_t kidpid = fork();

            if (kidpid < 0)
            {
                perror( "Internal error: cannot fork." );
                return -1;
            }
            else if (kidpid == 0)
            {
                // I am the child.
                cout << "Oles 5 cm" << endl << prog << endl;
                execvp (prog, argv);

                // The following lines should not happen (normally).
                perror( command );
                return -1;
            }
            else
            {
                // I am the parent.  Wait for the child.
                if ( waitpid( kidpid, 0, 0 ) < 0 )
                {
                    perror( "Internal error: cannot wait for child." );
                    return -1;
                }
            }
        }
    }


    return 0;

}


int main(int argc, char* argv[], char**env)
{
/*
    pid_t pid = fork();
    if (pid == -1)
    {
        cout << "ERROR" << &endl;
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
    }
    else {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        //printf( "%s\n", cwd);
        execve("/bin/ls", argv, env);
        _exit(EXIT_FAILURE);
    }*/
    string input = "";

    while(true)  {
        //string command;
        // char commandChar[1024];    // Will store the command entered by user in character array
        // char *argVector[10];    // Will store the arguments after they are tokenized
        //int argCount;        // Will store the number of arguments

        //char cwd[1024];
        //getcwd(cwd, sizeof(cwd));
        //printf( "%s$\n", cwd);

        cout << curr_dir << "$ ";
        //vector<char*> args;

        //string v = string(prog);
        //cout<<args[1];
        //cout<<command<<endl;
        //cout<<args;
        //cout << *arg;
        //string input = " ";
        getline(cin , input);


        if ("pwd" == input){

            cout << curr_dir;
        }
        else if ( input == "Myls"){
            doLS();

        }
        else if(input == "cd"){
            splitString(input);
            cd();

        }else if(input== "exit"){
            break;
        }

        cout << "\n";


        //cout << input << endl;



        /*
        ptr = strtok(commandChar, " ");
        argVector[argCount] = ptr;
        argCount++;
        while (ptr != NULL)
        {
            ptr = strtok(commandChar, " ");
            cout << ptr << " " << argCount << "\n";
            argVector[argCount] = ptr;
            argCount++;
            //execvp(argvec[0], argvec);
            //fatal("exec failed");
        }
*/
    }

    return 0;

}