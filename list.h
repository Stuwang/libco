#ifndef _LIST_H_
#define _LIST_H_

#include <list>
#include "spinlock.h"

namespace co{

template<class T>
class safelist{
public:
	T* get(){
		T *ret = nullptr;
		{
			lock_guard<spinlock> l(lock_);
			if(list_.size()){
				ret = *list_.begin();
				list_.erase(list_.begin());
			}
		}
		return ret;
	};

	void pop(T *p){
		lock_guard<spinlock> l(lock_);
		auto i = list_.find(p);
		if(p!= list_.end())
			list_.erase(p);
};

	void put(T *t){
		lock_guard<spinlock> l(lock_);
		list_.push_back(t);
	};
	bool empty(){
		lock_guard<spinlock> l(lock_);
		return list_.empty();
	};
private:
	std::list<T*> list_;
	spinlock lock_;
};

}

#endif
