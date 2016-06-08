#include <iostream>

#include "Task.h"
#include "taskshduler.h"
#include "co_mutex.h"

auto & p = co::gettaskinstense();

co::co_mutex m;

void lock_test() {
	std::cout << "1 lock " << p.size()  << std::endl;
	m.lock();
	std::cout << "1 lock endl " << p.size()  << std::endl;
};

void unlock_test() {
	std::cout << "3 unlock " << p.size()  << std::endl;
	m.unlock();
	std::cout << "3 unlock endl" << p.size()  << std::endl;
};



int main() {
	p.addTask(lock_test);

	p.addTask(lock_test);

	p.addTask(unlock_test);
	
	// p.addTask(lock_test);

	// p.addTask(unlock_test);

	std::cout << "begin " << p.size() << std::endl;
	p.run();
	std::cout << "end " << p.size()  << std::endl;
}