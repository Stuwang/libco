#include <iostream>              // std::cout
#include <atomic>                // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>                // std::thread, std::this_thread::yield
#include <vector>                // std::vector
#include <mutex>

using namespace std;

class spinlock {
public:
	spinlock() {
		flag_.clear();
	}

	inline void lock() {
		while (atomic_flag_test_and_set_explicit(&flag_, memory_order_acquire))
			;
	}

	inline bool trylock() {
		return atomic_flag_test_and_set_explicit(&flag_, memory_order_acquire);
	}
	inline void unlock() {
		atomic_flag_clear_explicit(&flag_, memory_order_release);
	}
private:
	atomic_flag flag_;
};

int num = 0;

spinlock l;

void fuck(int i) {
	// std::this_thread::yield();
	// lock_guard<spinlock> lk(l);
	for (int j = 0; j < 10; j++) {
		cout << "hahhahhah " << i << endl;
		std::chrono::milliseconds dura( 2 );
		std::this_thread::sleep_for( dura );
	};
}

int main() {
	std::thread t1{fuck,1};
	std::thread t2{fuck,2};
	t2.join();
	t1.join();
};