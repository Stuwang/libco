#include "semaphores.h"
#include <iostream>
#include <thread>

using namespace std;

co::semaphores sem(1);

void fuck(int i) {
	// std::this_thread::yield();
	// lock_guard<spinlock> lk(l);
	while(!sem.get())
		;
	for (int j = 0; j < 10; j++) {
		cout << "hahhahhah " << i << endl;
		std::chrono::milliseconds dura( 2 );
		std::this_thread::sleep_for( dura );
	};
	sem.put();
}

int main() {
	std::thread t1{fuck,1};
	std::thread t2{fuck,2};
	t2.join();
	t1.join();
};