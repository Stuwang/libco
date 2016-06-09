#include <iostream>

#include "Task.h"
#include "taskshduler.h"
#include "co_mutex.h"

auto & p = co::gettaskinstense();

co::co_mutex m;

template<int i>
void lock_test() {
	std::cout << i << " lock " << p.size()  << std::endl;
	m.lock();
	std::cout << i << " lock endl " << p.size()  << std::endl;
};

template<int i>
void unlock_test() {
	std::cout << i << " unlock " << p.size()  << std::endl;
	m.unlock();
	std::cout << i << " unlock endl" << p.size()  << std::endl;
};



int main() {
	p.addTask(lock_test<1>);
	p.addTask(lock_test<2>);
	p.addTask(lock_test<3>);
	p.addTask(lock_test<4>);

	p.addTask(unlock_test < -1 > );
	p.addTask(unlock_test < -2 > );
	p.addTask(unlock_test < -3 > );
	p.addTask(unlock_test < -4 > );

	// p.addTask(lock_test);

	// p.addTask(unlock_test);

	std::cout << "begin " << p.size() << std::endl;
	p.run();
	std::cout << "end " << p.size()  << std::endl;
}