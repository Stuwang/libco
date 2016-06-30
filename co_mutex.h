#ifndef _CO_MUTEX_H_
#define _CO_MUTEX_H_

#include "Task.h"
#include <assert.h>

#include <iostream>

namespace co {

class co_mutex {
public:
	co_mutex(): locked_(false) {};
	inline void lock() {
		std::unique_lock<spinlock> lk(lock_);
		if (locked_) {
			auto cur_task = gettaskinstense().getCurTask();
			tasklist_.put(cur_task);
			cur_task->SetState(TaskState::Sysblock);
			lk.unlock();
			gettaskinstense().yield();
		} else {
			locked_ = true;
			lk.unlock();
			return;
		}
	};
	inline void unlock() {
		std::unique_lock<spinlock> lk(lock_);

		if (tasklist_.size()) {
			auto p = this->tasklist_.get();
			p->SetState(TaskState::Runnable);
			gettaskinstense().addTask(p);
		} else {
			if (!locked_) {
				assert(false);
			}
			locked_ = false;
		}
	};

	~co_mutex() {
		std::cout << "tasklist_ " << tasklist_.size() << std::endl;
		assert(0 == tasklist_.size());
	}
private:
	safelist<Task> tasklist_;
	bool locked_;
	spinlock lock_;
};

}

#endif