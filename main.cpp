#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <future>

using namespace std;

atomic<bool> isReady{false};
mutex mtx;
condition_variable condvar;

deque<int> dq;

void Producer()
{
    std::cout << " Producer " << std::endl;

    for (auto x = 0; x < 5; x++)
    {
        {
            lock_guard<mutex> guard(mtx);
            //cout << "Producing message: " << x << " th" << endl;
            dq.push_back(rand());
        }
        condvar.notify_one();

        //this_thread::sleep_for(chrono::seconds(1));
    }
    isReady = true;


    for (auto y = 0; y < dq.size();y++){
        cout << dq[y] << endl;
    }
    cout << "Producer completed" << endl;

}

void Consumer() {
    while (true) {
        unique_lock<mutex> lk(mtx);
        if (!dq.empty()) {
            int i = dq.front();
            dq.pop_front();
            lk.unlock();
            cout << "Consuming: " << i << " th" << endl;
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
    cout << "Hello, World!" << endl;
    auto t1 = async(launch::async, Producer);
    auto t2 = async(launch::async, Consumer);
    t1.get();
    t2.get();
    return -1;
}