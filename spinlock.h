#include <atomic>

#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_ 

namespace co{

class spinlock {
public:
	spinlock() {
		flag_.clear();
	}

	inline void lock() {
		while (std::atomic_flag_test_and_set_explicit(&flag_, std::memory_order_acquire))
			;
	}

	inline bool trylock() {
		return std::atomic_flag_test_and_set_explicit(&flag_, std::memory_order_acquire);
	}
	inline void unlock() {
		std::atomic_flag_clear_explicit(&flag_, std::memory_order_release);
	}
private:
	std::atomic_flag flag_;
};

};

#endif
