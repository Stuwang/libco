#include "co_condition.h"

namespace co {

co_condition::co_condition(): u_lock(nullptr) {};

co_condition::~co_condition() {};

void co_condition::wait(std::unique_lock<co_mutex>& lock) {
	u_lock = & lock;

	{
		std::unique_lock<spinlock> lk(lock_);
		auto cur_task = gettaskinstense().getCurTask();
		tasklist_.put(cur_task);
		cur_task->SetState(TaskState::Sysblock);
	}

	u_lock->unlock();

	gettaskinstense().yield();

	// std::cout << "test what the fuck 1 !!! " << std::endl;

	u_lock->lock();
	// std::cout << "----" << std::endl;

};

void co_condition::wait(co_unique_lock& lock) {
	u_culock = & lock;

	{
		std::unique_lock<spinlock> lk(lock_);
		auto cur_task = gettaskinstense().getCurTask();
		tasklist_.put(cur_task);
		cur_task->SetState(TaskState::Sysblock);
	}

	u_culock->unlock();

	gettaskinstense().yield();

	// std::cout << "test what the fuck 1 !!! " << std::endl;

	u_culock->lock();
	// std::cout << "----" << std::endl;

};

void co_condition::wait(co_mutex& lock) {
	u_m_lock = & lock;

	{
		std::unique_lock<spinlock> lk(lock_);
		auto cur_task = gettaskinstense().getCurTask();
		tasklist_.put(cur_task);
		cur_task->SetState(TaskState::Sysblock);
	}

	u_m_lock->unlock();

	gettaskinstense().yield();

	// std::cout << "test what the fuck 1 !!! " << std::endl;

	u_m_lock->lock();
	// std::cout << "----" << std::endl;

};


void co_condition::notify_one() {
	std::unique_lock<spinlock> lk(lock_);
	if (tasklist_.size()) {
		auto p = this->tasklist_.get();
		p->SetState(TaskState::Runnable);
		gettaskinstense().addTask(p);
	}
};

void co_condition::notify_all() {
	std::unique_lock<spinlock> lk(lock_);
	while (tasklist_.size()) {
		auto p = this->tasklist_.get();
		p->SetState(TaskState::Runnable);
		gettaskinstense().addTask(p);
	}
};

}
