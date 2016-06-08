#ifndef _TASKSHDULER_H_
#define _TASKSHDULER_H_ 

#include "list.h"
#include "Task.h"

namespace co{

class taskshduler{
public:
	/**
	 * @Synopsis 添加一个任务 
	 *
	 * @Param fn
	 */
	void addTask(std::function<void()> const& fn);
	
	// maybe nouse
	void addTask(Task *p);
	/**
	 * @Synopsis 获取一个任务 
	 *
	 * @Returns   
	 */
	Task *getTask();
	/**
	 * @Synopsis 取消任务 
	 *
	 * @Param p
	 */
	void cancleTask(Task * p);

	void yield();
	/**
	 * @Synopsis 运行一次 
	 */
	void run();
	/**
	 * @Synopsis 运行直到所有任务全部结束 
	 */
	void run2end();
	/**
	 * @Synopsis 是否为空 
	 *
	 * @Returns   
	 */

	Task * getCurTask(){
		return use_;
	};

	bool empty(){return tasklist_.empty();};

	size_t size(){return tasklist_.size();}
private:
	Task * use_;
	safelist<Task> tasklist_;
};

taskshduler & gettaskinstense();

void yield();

};

#endif
