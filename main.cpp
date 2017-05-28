#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <future>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

atomic<bool> isReady{false};
mutex mtx;
condition_variable condvar;
map<string, int> mapper;

string line;
vector<string> block;
size_t line_index = 0;
int block_size = 100;
int limit_chars = 100;

int c = 0;

deque<vector<string>> dq;

void Producer() {
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
                        cout << i << " Output I  " << i+ adding + addCount << endl;
                        cout << "EXPRESSION: "<< line.substr(i, i+ adding + addCount) << endl;   //to del
                        block.push_back(line.substr(i, i + adding+ addCount));
                        cout << i << "I" << endl;
                        i = (i + adding + addCount);
                        cout << i << "I" <<" " <<adding <<" "<< addCount <<endl;
                        ++line_index;;
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
                    c++;
                    cout << c << endl;
                    {
                        lock_guard<mutex> guard(mtx);
                        //cout << "Producing message: " << x << " th" << endl;
                        dq.push_back(block);
                    }
                    line_index = 0;
                    block.clear();


                }
                condvar.notify_one();


            }
            cout << "Producer completed" << endl;
            isReady = true;
            // for (unsigned i = 0; i < block.size(); ++i) cout << ' ' << block[i];
            //  cout << '\n';

            //this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void Consumer() {
    while (true) {
        unique_lock<mutex> lk(mtx);
        if (!dq.empty()) {
            vector<string> & i = dq.front();
            dq.pop_front();
            lk.unlock();
            cout << "Consuming: " << i.data() << " th" << endl;
        } else {
            if(isReady){
                break;
            }
            else {
                condvar.wait(lk);
                cout << "There are no messages remained from producer" << endl;
            }

        }

        cout << "\nConsumer is done" << endl;
    }
}
int main() {
    //cout << "Hello, World!" << endl;
    auto t1 = async(launch::async, Producer);
    auto t2 = async(launch::async, Consumer);
    //auto t3 = async(launch::async, Consumer);
    t1.get();
    t2.get();
    //t3.get();
    return -1;
}