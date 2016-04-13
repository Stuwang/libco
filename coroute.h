#ifndef _COROUTE_H_
#define _COROUTE_H_

#include <ucontext.h>
#include <functional>
#include <memory>
#include "Task.h"

namespace co{

class Task;
class Coroute{
public:
	typedef void(*Functor)();
	/**
	 * @Synopsis  new a Coroute
	 *
	 * @Param f
	 * @Param ptask
	 */
	Coroute(Functor f,Task * ptask);
	~Coroute();
	bool SwapIn();
	bool SwapOut();

	ucontext_t & GetThreadLocalContext();

	// no copy or move
	Coroute(const Coroute&) = delete;
	Coroute(Coroute &&) = delete;
	Coroute& operator = (const Coroute&) = delete;
	Coroute& operator = (Coroute&&) = delete;
private:
	std::unique_ptr<char[]> stack_;
	size_t stack_size_;
	ucontext_t ctx_;

	static const size_t STACK_SIZE = 1024*1024;
};

} // namespace co

#endif 
