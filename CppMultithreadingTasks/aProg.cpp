#include <iostream>
#include <mutex>
#include <thread>


using namespace std;

mutex mtx;



void worker(int start, int end, int d, int &sum){
        lock_guard<mutex> lg(mtx);
        for(int i = start; i < end; i++){
            sum += d;
        }


}

int main() {
    int a_0 = 5;
    int sum = a_0;
    thread th1 = thread(worker, 0, 3, 2, ref(sum));
    thread th2 = thread(worker, 3, 6, 2, ref(sum));
    th1.join();
    th2.join();
    cout << "The sum is: "<<sum << endl;
}