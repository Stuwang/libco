#ifndef _CO_CONDITION_H_
#define _CO_CONDITION_H_

#include "define.h"
#include "co_mutex.h"

namespace co {

class co_condition {
public:
	co_condition();
	~co_condition();
	void wait(std::unique_lock<co_mutex>& lock);
	void wait(co_unique_lock& lock);
	void wait(co_mutex& lock);
	void notify_one();
	void notify_all();

	DISABLE_COPY_MOVE(co_condition);
private:
	safelist<Task> tasklist_;
	std::unique_lock<co_mutex> *u_lock;
	co_unique_lock *u_culock;
	co_mutex *u_m_lock;
	spinlock lock_;
};

}

#endif