#include <iostream>

#include "Task.h"
#include "taskshduler.h"
#include "co_mutex.h"
#include "co_condition.h"

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

void test0() {
	p.addTask(lock_test<4>);

	p.addTask(unlock_test < -1 > );

	p.run();

	std::cout << "end" << std::endl;
}


void test1() {
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
};

bool c = true;
co::co_condition cond;
co::co_mutex m_test2;

void test2() {
	p.addTask([]() {
		std::unique_lock<co::co_mutex> lk(m_test2);
		std::cout << "start wait" << std::endl;
		while (c) {
			cond.wait(lk);
		};
		std::cout << "after wait" << std::endl;
	});

	p.addTask([]() {
		std::unique_lock<co::co_mutex> lk(m_test2);
		std::cout << "start notify" << std::endl;
		c = false;
		cond.notify_all();
		std::cout << "after notify" << std::endl;
	});

	std::cout << "begin " << p.size() << std::endl;
	p.run();
	std::cout << "end " << p.size()  << std::endl;
}

int main() {
	test2();
}