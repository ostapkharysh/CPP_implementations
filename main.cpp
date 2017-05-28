#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <future>
#include <map>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

atomic<bool> isReady{false};
mutex mtx;
condition_variable condvar;
map<string, int> mapper;
deque<vector<string>> dq;

string punctuationOut(string wrd){


    for (int i = 0, len = wrd.size(); i < len; i++)
    {
        if (ispunct(wrd[i]))
        {
            wrd.erase(i--, 1);
            len = wrd.size();
        }
    }
    return wrd;
}

void Producer() {
    string line;
    vector<string> block;
    size_t line_index = 0;
    int block_size = 100;
    int limit_chars = 100;
    std::cout << " Producer " << std::endl;
    fstream fl("/home/ostap/CLionProjects/WordsCount2/file.txt"); //full path to the file
    if (!fl.is_open()) {
        cout << "error reading from file" << endl;
    }
    else {
        cout << "SUCCESS!!!" << endl;
        while (getline(fl, line) && line_index < block_size) {
            if (line.find_first_not_of(' ') != string::npos) {   // Checks whether it is a non-space.
                // There's a non-space.
                cout<< "linesize: " << line.length() << endl;
               if (line.length() / limit_chars > 1.4) {

                    int divider = (int) (line.length() / limit_chars);
                    int adding = (int) line.length()/divider;
                   //попробуй поміняти на while все через addCount
                    int addCount = 0;
                    int i = 0;
                    cout <<"divider" << divider<<endl;
                    while ( i < line.length()){
                        while (line[i + adding + addCount] != ' ') {addCount+=1;}
                        cout << i << " Output I  " << i + adding + addCount << endl;
                        cout << "EXPRESSION: " << line.substr(i, adding + addCount) << endl;   //to del
                        block.push_back(line.substr(i, adding +addCount));
                        cout << i << " I" << endl;
                        i = i + adding + addCount;
                        cout << i << "I" <<" " <<adding <<" "<< addCount <<endl;
                        ++line_index;
                        addCount = 0;
                        cout << "was here OST" << endl;
                    }
                    }

                 else {
                    ++line_index;;
                    block.push_back(line);
                    cout << "Line: " << line << endl;
                }


                if (line_index >= block_size) {
                    {
                        lock_guard<mutex> guard(mtx);
                        //cout << "Producing message: " << x << " th" << endl;
                        dq.push_back(block);
                    }
                    line_index = 0;
                    block.clear();


                }



            }
            cout << "Producer completed" << endl;

            // for (unsigned i = 0; i < block.size(); ++i) cout << ' ' << block[i];
            //  cout << '\n';

            //this_thread::sleep_for(chrono::seconds(1));
        }

    }
    condvar.notify_one();
    isReady = true;

}

void Consumer() {
    while (true) {
        cout << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ";
        unique_lock<mutex> lk(mtx);
        if (!dq.empty()) {
            cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << endl;
            vector<string> & v = dq.front();
            dq.pop_front();
            lk.unlock();
            string word;
            for(int i = 0; i < v.size(); i++) {
                cout<<v[i]<<endl;
                cout<<v[i].size()<<endl;
                istringstream iss(v[i]);
                while(iss >> word){

                   //word = punctuationOut(word);
                    cout << word << endl;
                }
                if(word !="") {
                    lock_guard<mutex> lg(mtx);
                    ++mapper[word];
                }
            }
        } else {
            cout << "Finish!";
            if(isReady)
                break;
            else
                condvar.wait(lk);
        }
}


   }


int main() {
    //cout << "Hello, World!" << endl;
//    auto t1 = (Producer);
//    auto t2 = thread(Consumer);
//    auto t3 = async(launch::async, Consumer);
//    t1.join();
//    t2.join();
//    t3.get();

    auto t1 = async(launch::async, Producer);
    auto t2 = async(launch::async, Consumer);
    t1.get();
    t2.get();
    return -1;
}