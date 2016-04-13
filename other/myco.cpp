#include <iostream>
#include <functional>
#include <cstdlib>
#include <ucontext.h>

using namespace std;

typedef std::function<void()> StdFun;
typedef void(*Functor)();

static ucontext_t local;

class Task{
public:
	Task(const StdFun f):fun_(f){
		getcontext(&ctx_);
		ctx_.uc_stack.ss_sp = (char*)malloc(1024*1024);
		ctx_.uc_stack.ss_size = 1024*1024;
		ctx_.uc_link = NULL;
		makecontext(&ctx_,(Functor)&task_func_,1,this );
	};

	~Task(){
		free(ctx_.uc_stack.ss_sp);
	}

	void run(){
		swapcontext(&local,&ctx_);
	};

	static void task_func_(Task *self){
		(self->fun_)();
		swapcontext(&self->ctx_,&local);
	}
private:
	ucontext_t ctx_;
	StdFun fun_;
};

void test(){
	cout << "okok " << endl;
}

int main(){
	std::function<void()> help (test);
	Task *p = new Task(test);
	p->run();
	cout << "good " << endl;
}