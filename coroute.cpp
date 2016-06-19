#include "coroute.h"

namespace co {

Coroute::Coroute(Functor f, Task * ptask)
{
	stack_size_ = STACK_SIZE;
	stack_.reset( new char[STACK_SIZE] );
	getcontext(&ctx_);
	ctx_.uc_stack.ss_sp = static_cast<char*>(stack_.get()) ;
	ctx_.uc_stack.ss_size = stack_size_;
	ctx_.uc_link = NULL;
	makecontext(&ctx_, f, 1, ptask );
};

Coroute::~Coroute() {};

ucontext_t & Coroute::GetThreadLocalContext()
{
	static thread_local ucontext_t local;
	return local;
};

bool Coroute::SwapIn()
{
	return 0 == swapcontext(&GetThreadLocalContext(), &ctx_);
};

bool Coroute::SwapOut()
{
	return 0 == swapcontext(&ctx_, &GetThreadLocalContext() );
};

}//
