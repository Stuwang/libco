#ifndef _TASK_H_
#define _TASK_H_

#include <ucontext.h>
#include <functional>
#include <memory>

#include "coroute.h"


namespace co{
enum class TaskState{
	Init,
	Runnable,
	Sysblock,
	IOBlock,
	Done,
	Fatal,
};

class Coroute;
class Task{
public:
	/**
	 * @Synopsis use for new a task,
	 *  attention ,must alloc in heap memory
	 *
	 * @Param fun
	 */
	Task(std::function<void()> const & fun)	;

	/**
	 * @Synopsis begin to run
	 *
	 * @Returns   
	 */
	bool SwapIn();

	/**
	 * @Synopsis sleep , and must use in neibu 
	 *
	 * @Returns   
	 */
	bool SwapOut();

	TaskState getState(){return state_;};

	void SetState(TaskState state){state_ = state;};

	/**
	 * @Synopsis   func in ucontext,*
	 *
	 * @Param self
	 */
	static void task_fun_(Task * self);

private:
	TaskState state_;
	std::function<void()> fun_;
	std::shared_ptr<Coroute> p_cou_;
};

} // co

#endif
