#ifndef _CO_MUTEX_H_
#define _CO_MUTEX_H_ 

#include "Task.h"

namespace co{

class co_mutex{
public:
	inline void lock(){

	};
	inline void unlock(){

	};
private:
	safelist<Task> tasklist_;
};

}

#endif