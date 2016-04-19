#include "taskshduler.h"

void taskshduler::addTask(std::function<void()> const & fn)
{
	Task * p = new Task(fn);
	tasklist_.put(p);
};

void taskshduler::addTask(Task *p)
{
	tasklist_.put(p);
};

void taskshduler::cancleTask(Task *p)
{
	tasklist_.pop(p);
};

void run(){
	while(!empty()){
		auto p = getTask();	
		p->SwapIn();
	}
};
