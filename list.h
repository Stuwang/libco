#ifndef _LIST_H_
#define _LIST_H_

#include <list>
#include <mutex>
#include <algorithm>
#include "spinlock.h"

namespace co {

template<class T>
class safelist {
public:
	T* get() {
		T *ret = nullptr;
		{
			std::lock_guard<co::spinlock> l(lock_);
			if (list_.size()) {
				ret = *list_.begin();
				list_.erase(list_.begin());
			}
		}
		return ret;
	};

	void pop(T *p) {
		std::lock_guard<spinlock> l(lock_);
		// auto i = list_.find(p);
		// auto i = std::find(begin(list_),end(list_),p);
		auto i = std::find(list_.begin(), list_.begin(), p);
		if (i != list_.end())
			list_.erase(i);
	};

	void put(T *t) {
		std::lock_guard<spinlock> l(lock_);
		list_.push_back(t);
	};
	bool empty() {
		std::lock_guard<spinlock> l(lock_);
		return list_.empty();
	};
	size_t size() {
		std::lock_guard<spinlock> l(lock_);
		return list_.size();
	}
private:
	std::list<T*> list_;
	spinlock lock_;
};

}

#endif
