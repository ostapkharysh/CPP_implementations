#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;



int grepHelp(){
    cout << "Search for PATTERN in each FILE or standard input.\n"
            "PATTERN is a word.\n"
            "Example: grep -i -v --file=test.txt acs \n"
            "Example: grep -i -v acs \n\n"
            "COMMANDS:\n"
            "-i or --ignore-case : ignore case while searching a PATTERN\n"
            "-v or --invert-match : search for all PATTERNS that don't match\n"
            "--file=  : search PATTERN from file\n"
            "-h or --help : instructions" << endl;

    return 0;
}

vector<string> ReadFromConsole(string UserInput) {
    vector<string> myVector;
    istringstream iss(UserInput);
    string output;
    while (iss >> output) {
        if (output != "") {
            myVector.push_back(output);
                    }
    }
    return myVector;
}


vector<string>  ReadFromFile(string Filename){
    cout << 1 << endl;
    vector<string> myVector;
    ifstream readFile;
    string data;
    string output;
    readFile.open(Filename);
    if (!readFile.is_open()){
       cerr << "No such file" << endl;

    }
    while(!readFile.eof()) // To get you all the lines.
    {   getline(readFile,data); // Saves the line in STRING.
        istringstream iss(data);
        while(iss >> output){
            if (output != "" ){
                myVector.push_back(output);
            }
        }
    }
    readFile.close();
    return myVector;


}

string toLower(string data) {
    for(int i=0; i<data.size();++i)
        data[i] = tolower(data[i]);
    return data;
}

int Greplication(vector<string> words, int IExists, int VExists, string toSearch){

    vector<string> filteredWords;
    if((IExists == 1)&&(VExists == 1)) {
        for(int i = 0; i < words.size(); i++){
            if ((toLower(words[i]).find(toLower(toSearch))) == string::npos) {
                cout << words[i] << " ";
                //filteredWords.push_back(words[i]);
                }
        }

    }
    else if(IExists == 1) {
        for(int i = 0; i < words.size(); i++){
            if (toLower(words[i]).find(toLower(toSearch)) != string::npos) {
                cout << words[i]<< " ";
                //filteredWords.push_back(words[i]);
            }

        }
    }
    else if (VExists == 1){
        for(int i = 0; i < words.size(); i++){
            if ((words[i]).find(toSearch) == string::npos) {
                cout << words[i]<< " ";
                //filteredWords.push_back(words[i]);
            }
        }
    }
    else{
        for(int i =0; i < words.size(); i++){
            if ((words[i]).find(toSearch) != string::npos){
                cout << words[i]<< " ";
                //filteredWords.push_back(words[i]);
            }
        }
    }
    return 0;
}


int main(int argc, char* argv[]) {
    int ignore_case_trigger = 0;
    int invert_trigger = 0;
    string file_trigger;
    int help_trigger = 0;
    string toSearch;
    string userString;

            for (int i = 1; i < argc; i++) {
                if ((string(argv[i]) == "-h") || (string(argv[i]) == "--help")) {
                    help_trigger = 1;
                } else if ((string(argv[i]) == "-v") || (string(argv[i]) == "--invert-match")) {
                    invert_trigger = 1;
                } else if ((string(argv[i]) == "-i") || (string(argv[i]) == "--ignore-case")) {
                    ignore_case_trigger = 1;
                } else if (((string(argv[i])).substr(0, 7) == "--file=")) {
                    file_trigger = (string(argv[i]).substr(7, string(argv[i]).size() - 7));
                }
                else {toSearch = string(argv[i]);
                }

            }

    if (help_trigger == 1){
        grepHelp();
        return 1;
    }
    if ((file_trigger =="") & (help_trigger ==0) &(ignore_case_trigger ==0) &(invert_trigger ==0)){
        cout<<"Usage: grep [OPTION]... PATTERN [FILE]...\n"
                "Try 'grep --help' for more information."<< endl;
        return 1;

    }
    if(file_trigger == "") {
        cout << "ENTER YOUR ARGUMENTS: ";
        getline(cin, userString);


    }
    if (toSearch == "") {
        cerr << "NO ARGUMENTS TO SEARCH INPUT" << endl;
        return -1;
    }
    vector<string> data;

    if (!(file_trigger == "")){
        data = ReadFromFile(file_trigger);
    }
    else if(file_trigger =="") {
        data = ReadFromConsole(userString);
    }
    Greplication(data, ignore_case_trigger, invert_trigger, toSearch);
        return 0;
        }


// http://radioskovoroda.com/music  always good music