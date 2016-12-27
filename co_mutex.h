#ifndef _CO_MUTEX_H_
#define _CO_MUTEX_H_

#include "define.h"

#include "Task.h"
#include "list.h"
#include "taskshduler.h"

#include <assert.h>

#include <mutex>
#include <iostream>

namespace co {

class co_mutex {
public:
	co_mutex();
	~co_mutex();
	void lock() ;
	bool locked();
	void unlock();
private:
	safelist<Task> tasklist_;
	bool locked_;
	spinlock lock_;

	DISABLE_COPY_MOVE(co_mutex);
};

class co_unique_lock {
public:
	co_unique_lock(co_mutex& mutex): m_lock(&mutex) {
		m_lock->lock();
	};

	~co_unique_lock() {
		if (m_lock->locked()) {
			m_lock->unlock();
		}
	};

	void lock() {
		assert(!m_lock->locked());
		m_lock->lock();
	};

	bool locked() {
		return m_lock->locked();
	};

	void unlock() {
		assert(m_lock->locked());
		m_lock->unlock();
	};

	DISABLE_COPY_MOVE(co_unique_lock);
private:
	co_mutex * m_lock;
};

}

#endif