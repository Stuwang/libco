#include "taskshduler.h"

namespace co{

void taskshduler::addTask(std::function<void()> const & fn)
{
	Task * p = new Task(fn);
	tasklist_.put(p);
};

void taskshduler::addTask(Task *p)
{
	tasklist_.put(p);
};

Task *taskshduler::getTask(){
	return tasklist_.get();
};

void taskshduler::cancleTask(Task *p)
{
	tasklist_.pop(p);
};

void taskshduler::yield(){
	use_->SwapOut();
};

void taskshduler::run(){
	while(!empty()){
		use_ = getTask();	
		use_->SwapIn();
		if(use_->getState() == TaskState::Done){
			delete use_;
		}else{
			addTask(use_);
			use_ = NULL;
		}
	};
};

taskshduler & gettaskinstense(){
	static taskshduler taskl_;
	return taskl_;
};

void yield(){
	auto & p = gettaskinstense();
	p.yield();
};

}