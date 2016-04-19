#include <atomic>

#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_ 

namespace co{

class spinlock {
	using namespace std;
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

};

#endif
