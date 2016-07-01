#include "taskshduler.h"

#include <assert.h>

#include <iostream>

namespace co {

void taskshduler::addTask(std::function<void()> const & fn)
{
	Task * p = new Task(fn);
	tasklist_.put(p);
};

void taskshduler::addTask(Task *p)
{
	tasklist_.put(p);
};

Task *taskshduler::getTask() {
	return tasklist_.get();
};

void taskshduler::cancleTask(Task *p)
{
	tasklist_.pop(p);
};

void taskshduler::yield() {
	use_->SwapOut();
};

void taskshduler::run() {
	while (!empty()) {	
		use_ = getTask();
		use_->SwapIn();
		switch (use_->getState()) {
		case TaskState::Init:
			addTask(use_);
			break;
		case TaskState::Runnable:
			addTask(use_);
			break;
		case TaskState::Sysblock:
			// std::cout << "system block " << size() << std::endl ;
			break;
		case TaskState::Done:
			delete use_;
			break;
		case TaskState::Fatal:
			assert(false);
			break;
		default:
			assert(false);
		}
	};
};

taskshduler & gettaskinstense() {
	static taskshduler taskl_;
	return taskl_;
};

void yield() {
	auto & p = gettaskinstense();
	p.yield();
};

}