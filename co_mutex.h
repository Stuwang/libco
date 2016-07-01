#ifndef _CO_MUTEX_H_
#define _CO_MUTEX_H_

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
};

}

#endif