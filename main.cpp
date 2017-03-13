//
// Created by ostap on 02.03.17.
//
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sstream>



using namespace std;
char *curr_dir = "/usr/bin";
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


    }



int ls(){
/*
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf( "%s\n", cwd); }

    */
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;
    /*
    if(NULL == curr_dir)
    {
        printf("\n ERROR : Could not get the working directory\n");
        return -1;
    }
    */
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

int main (int argc, char * const argv[]) {

    string input = "";
    char *ptr;


    while (true) {
        //string command;
       // char commandChar[1024];    // Will store the command entered by user in character array
       // char *argVector[10];    // Will store the arguments after they are tokenized
        //int argCount;        // Will store the number of arguments

        //char cwd[1024];
        //getcwd(cwd, sizeof(cwd));
        //printf( "%s$\n", cwd);

        cout << curr_dir << "$ ";
        getline(cin, input);
        //cout << input<< "    input" << endl;
        splitting(input);
        if (input == "pwd"){
            cout << curr_dir;
        }
        else if ( input == "ls"){
            ls();

        }
        else if(comm == "cd"){
            if(argum=="."){
                cout << "LASHARA. WONO NICHO NE ROBYT." << endl;
            }
            else if(argum == ".."){
                cout << "To previous directory" << endl;

            }
            else if(argum == "~" || argum == "") {
                cout << "Returnimg back to home dir" << endl;
            }

            
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

