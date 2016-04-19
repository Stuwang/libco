#ifndef _TASKSHDULER_H_
#define _TASKSHDULER_H_ 

#include "list.h"

namespace co{

class taskshduler{
public:
	/**
	 * @Synopsis 添加一个任务 
	 *
	 * @Param fn
	 */
	void addTask(std::function<void()> const& fn);
	
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
	bool empty(){return tasklist_.empty();};
private:
	safelist<Task> tasklist_;
};

static taskshduler & gettaskinstense(){
	static taskshduler taskl_;
	return taskl_;
};

};

#endif
