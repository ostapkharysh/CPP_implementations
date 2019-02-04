#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <bits/ios_base.h>
#include <ios>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/bind.hpp>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <map>

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
    cout << argv[1] <<endl;
    if (string(argv[1]) == " "){
        cout << "no arguments" << endl;
    }

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

int myLs(char** argv){
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
   /* DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;
    dp = opendir((const char*)curr_dir);
    cout << "start " << argv[1] <<  endl;
    if(NULL == dp)
    {
        printf("\n ERROR : Could not open the working directory\n");
        return -1;
    }

    // order by SIZE
    else if (string(argv[1]) == "-S") {
            int data = printf("%s  ", dptr->d_name);
            cout << data;
        map<int, string> mapOffiles;
        struct stat filestatus;
        cout << "HERE"<< endl;
        for (int i = 2; argv[i] != NULL; i++) {
            if (opendir((const char *) argv[i]) != NULL || fopen((const char *) argv[i], "r") != NULL) {
                stat(argv[i], &filestatus);
                mapOffiles.insert(make_pair(filestatus.st_size, argv[i]));
            }
        }
        for (map<int, string>::iterator ii = mapOffiles.begin(); ii != mapOffiles.end(); ++ii) {
            cout << (*ii).second << endl;
        }
    }
    // simple LS
        //cd home/ostap/D
    else{
    for(count = 0; NULL != (dptr = readdir(dp)); count++) {
        // Check if the name of the file/folder begins with '.'
        // If yes, then do not display it.
        if (dptr->d_name[0] != '.')
            //cout << dptr;
            printf("%s  ", dptr->d_name);
        //printf("%s  ",dptr->d_name);

    }

    }



    return 0;
}
*/

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
            char *cmd = (char *) myLs(argv);
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
            //execvp ("/home/ostap/CLionProjects/myPWD/myRm", argv);
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

/*hjsbdjsdfjsdhfjsdkhflgjhdflkjglkdjgldkfjgldfjgkldsfjglsdjkfskdfjsldf*/
bool is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

int rewrite_check() {
    cout << "Do you want to rewrite? [y/n]";
    char answ[16];
    cin.getline(answ, 16);
    char *ans = strtok(answ, " ");
    char first = ans[0];
    cout << ans << endl;
    if (first == 'y') {
        return 0;
    }
    return -1;
}

int inside_copy(char** argv, int source, int dest) {
    ifstream f1 (argv[source], fstream::binary);
    ofstream f2 (argv[dest], fstream::trunc|fstream::binary);
    f2 << f1.rdbuf();
    return 0;
}

int inside_copy_dir(char** argv, int numb) {
    int i=1;
    std::string additive(argv[1]);
    if (additive == "-f") {i=2;}
    while (i !=numb) {
        std::string name(argv[numb]);
        char str[128];

        strcpy (str, argv[i]);                                                //start of splitting
        char * token = std::strtok(str, "/");
        char* temp = token;
        while (token != NULL) {
            temp=token;
            token = strtok(NULL, "/");
        }
        cout << " filename "<< temp << endl;
        const char* spl = "/";
        name += spl;
        name+= temp;
        const char* nName = name.c_str();
        int ch = 0;
        if (is_file(nName) && (additive != "-f")) {
            int check = rewrite_check();
            if (check == -1) {ch = -1;}
        }
        if ((ch==0) || (additive == "-f") ||!(is_file(temp))) {
            ifstream f1 (argv[i], fstream::binary);                               //start copying file
            ofstream f2 (nName, fstream::trunc|fstream::binary);
            f2 << f1.rdbuf();
        }
        i++;

    }}

int cp_help(){
    cout << "Usage: cp [-f] SOURCE DEST \n or:  cp [-f] SOURCE... DIRECTORY \n Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY. \n -f - rewrite existing files without asking" << endl;
    return 0;
}

int myCP(int a, char** argv) {
    struct stat st;
    int i=1;
    std::string name(argv[1]);
    if (name=="-h"|| name=="--help") {return cp_help();}
    if (name == "-f") {i=2;}
    while (i!=sizeof(argv))   {
        if (argv[i+1] == NULL) {                                    // pointer is on the last argument
            if ((i!=1) && (is_dir(argv[i]))) {                     //spec. option for copying few f into dir
                return inside_copy_dir(argv, i);
            }
            else if (((i==1)&&((name!="-h")||(name != "--help"))) ||
                     ((i>2)&&(name != "-f"))||((i>3)&&(name == "-f"))) {
                                                                                                 return -1;
            }
            else if (((((i==2)&&(stat(argv[i],&st) == -1))||
                       ((i==3)&&(stat(argv[i],&st) == 0)&&(name == "-f"))))) {
                return inside_copy(argv, i-1, i);
            }
            else if((i=2) && (stat(argv[i],&st) == 0)){
                if (rewrite_check()==0) {
                    return inside_copy(argv, i-1, i);
                }
                else{return -1;}
            }}

        else {                                             //for all files except the last one
            if (stat(argv[i],&st) != 0) {                 //checking for existance of each file we want to rewrite
                cout << "NO SUCH FILE"<<endl;
                return -1; }}
        i++; }}


/*hjsbdjsdfjsdhfjsdkhflgjhdflkjglkdjgldkfjgldfjgkldsfjglsdjkfskdfjsldf*/

int doSize(char* prog, char** argv) {
    DIR *dp;
    struct dirent *dir;
    vector<string> dirlist;
    int i = 0;
    map<int,string> mapOffiles;
    struct stat filestatus;
    dp = opendir((const char *) curr_dir);
    if (dp) {
        while ((dir = readdir(dp)) != NULL) {
            i++;
            //cout<<dir->d_name<<endl;
            dirlist.push_back(dir->d_name);
        }

        closedir(dp);
    }

    for (int i = 0; i < dirlist.size(); i++){
        //cout << dirlist[i] << endl;
        stat((const char *) dirlist[i], &filestatus); //// трешак тут на тому крешиться
        mapOffiles.insert(make_pair(filestatus.st_size, dirlist[i]));

}
    for( map<int,string>::iterator ii=mapOffiles.begin(); ii!=mapOffiles.end(); ++ii)
    {
        cout  << (*ii).second << ":  "<<(*ii).first<< endl;
    }

  return 0;
}

int doCP(char* prog, char** argv){
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
        char *cmd = (char *) myCP(1, argv);
        // abo mozna she tak v'ibaty:
        //execvp (*cmd, argv);

        //const char *papka = (const char *) ('/home/ostap/CLionProjects/myPWD/' + char(argv[1]));
        //execvp ("/home/ostap/CLionProjects/myPWD/myRm", argv);
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
        else if((string(prog)=="mcd")){
            cd(argv);
            //doLS(prog, argv);
        }

        else if((string(prog)=="mcp")){
            doCP(prog, argv);
            //doLS(prog, argv);
        }

        else if(string(prog) == "mrm"){
            doRM(prog, argv);
        }

        else if(string(prog) == "msize"){
            doSize(prog, argv);
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
