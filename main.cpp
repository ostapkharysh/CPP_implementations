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
vector<char*> vectorOfPath;
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

int cd(char** argv){
    if (argv[1] == NULL)
    {
        chdir ("/");
        curr_dir = get_current_dir_name();
    }
    else{

        vectorOfPath.push_back(argv[1]);
        chdir (argv[1]);
        //cout<<get_current_dir_name();
        curr_dir = get_current_dir_name();
    }
    return 0;

}


void toRemove(const char* data){
    if (remove(data) != 0) {
        perror("Error deleting file");
    } else {
        puts("File successfully deleted");
    }
}

int myRm(char** argv){
    if(string(argv[1]) == "--help"){
        cout<<"Usage: rm [OPTION]... [FILE]...\n"
                "Remove (unlink) the FILE(s).\n"
                "\n"
                "  -f, --force           ignore nonexistent files and arguments, never prompt\n"
                "  -R, --recursive   remove directories and their contents recursively\n"
                "\n"
                "By default, rm does not remove directories.  Use the --recursive (-R)\n"
                "option to remove each listed directory, too, along with all of its contents.\n"
                "\n"
                "Note that if you use rm to remove a file, it might be possible to recover\n"
                "some of its contents, given sufficient expertise and/or time.  For greater\n"
                "assurance that the contents are truly unrecoverable, consider using shred.\n"
                "\n"
                "GNU coreutils online help: <http://www.teambest.org.ua/>\n"
                "Full documentation at: <http://www.teambest.org/software/coreutils/rm>\n";
    }

    else if (string(argv[1]) != "-f" & string(argv[1]) != "-R") {

        // The file exists, and is open for input

            for (int i = 1; argv[i] !=NULL; i++) {
                string usrInput;
                {
                    if (opendir((const char *) argv[i])) {
                        cout << string(argv[i]) << " is a directory!. Unable to delete" << endl;
                    } else if (fopen((const char *) argv[i], "r") != NULL) {
                        cout << "Do you wish to delete: " << string(argv[i]) << "? [y/n]  ";
                        getline(cin, usrInput);
                        if (string(usrInput) == "y") {
                            toRemove(argv[i]);
                        }
                    } else {
                        cout << string(argv[i]) << " does not exist" << endl;
                    }
                }
            }
    }
    else if(string(argv[1]) == "-f" || string(argv[1]) == "-R") {
        for (int i = 2; argv[i] !=NULL; i++) {
            if(((opendir((const char *) argv[i]) == NULL)
                                          & (fopen((const char *) argv[i], "r") == NULL))){
                cout << string(argv[i]) << " does not exist" << endl;
            }

            if (string(argv[1]) == "-R" & ((opendir((const char *) argv[i]) != NULL)
                                          || (fopen((const char *) argv[i], "r") != NULL))) {
                toRemove(argv[i]);

            }
            else if(string(argv[1]) == "-f" &(opendir((const char *) argv[i]) != NULL)) {
                cout << string(argv[i]) << " is a directory!. Unable to delete" <<endl;
            }
            else if (string(argv[1]) == "-f" &(fopen((const char *) argv[i], "r") != NULL)){
                toRemove(argv[i]);
            }

        }
    }
    return 0;
    }

int myLs(){
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


int doLS(char* prog, char** argv){

        pid_t kidpid = fork();

        if (kidpid < 0)
        {
            perror( "Internal error: cannot fork." );
            return -1;
        }
        else if (kidpid == 0)
        {
            // I am the child.
            //cout << "Oles 5 cm" << endl << prog << endl;
            char *cmd = (char *) myLs();
            // abo mozna she tak v'ibaty:
            //execvp (*cmd, argv);
            execvp (prog, argv);

            // The following lines should not happen (normally).
            //perror( command );
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


    return 0;

}

int doRM(char* prog, char** argv){
        pid_t kidpid = fork();

        if (kidpid < 0)
        {
            perror( "Internal error: cannot fork." );
            return -1;
        }
        else if (kidpid == 0)
        {
            // I am the child.
            //cout << "BLA BLA BLA" << endl << prog << endl;
            char *cmd = (char *) myRm(argv);
            // abo mozna she tak v'ibaty:
            //execvp (*cmd, argv);

            //const char *papka = (const char *) ('/home/ostap/CLionProjects/myPWD/' + char(argv[1]));
            execvp ("/home/ostap/CLionProjects/myPWD/myRm", argv);
            execvp (prog, argv);
            //execvp (cmd, argv);
            //cout << "est";

            // The following lines should not happen (normally).
            //perror( command );
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

    while(true)  {
        //string command;
        // char commandChar[1024];    // Will store the command entered by user in character array
        // char *argVector[10];    // Will store the arguments after they are tokenized
        //int argCount;        // Will store the number of arguments

        //char cwd[1024];
        //getcwd(cwd, sizeof(cwd));
        //printf( "%s$\n", cwd);

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

        char** argv = args.data();

        argv[args.size()] = NULL;


        if ((string(prog)=="pwd")){

            cout << curr_dir;
        }
        else if ((string(prog)=="mls")){
            //cout << "asv" <<endl;
            //  filesystem tut4.cpp  ---------------------------------------------------------------//
            doLS(prog, argv);

        }
        else if((string(prog)=="cd")){
            cd(argv);
            //doLS(prog, argv);
        }

        else if(string(prog) == "mrm"){
            doRM(prog, argv);
        }

        else if((string(prog)=="exit")){
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