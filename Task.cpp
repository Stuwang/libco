#include "Task.h"

namespace co {

Task::Task(std::function<void()> const& fun)
	: state_(TaskState::Init),
	  fun_(fun),
	  p_cou_(new Coroute(
	             (Coroute::Functor) & task_fun_, this) )
{};

bool Task::SwapIn() {
	return p_cou_->SwapIn();
};

bool Task::SwapOut() {
	return p_cou_->SwapOut();
};

void Task::task_fun_(Task *self)
{
	(self->fun_)();
	self->state_ = TaskState::Done ;
	self->SwapOut();
};

}
