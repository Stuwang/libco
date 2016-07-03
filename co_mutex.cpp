#include "co_mutex.h"

namespace co {

co_mutex::co_mutex(): locked_(false) {};

co_mutex::~co_mutex() {
	std::cout << "tasklist_ " << tasklist_.size() << std::endl;
	assert(0 == tasklist_.size());
}

void co_mutex::lock() {
	std::cout << "lock " << std::endl;
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

bool co_mutex::locked() {
	std::unique_lock<spinlock> lk(lock_);
	return locked_;
}

void co_mutex::unlock() {
	std::cout << "unlock " << std::endl;
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

}