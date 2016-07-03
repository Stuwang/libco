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

struct TestDes {
	TestDes() {
		std::cout << "constructor" << std::endl;
	}
	~TestDes() {
		std::cout << "destructor" << std::endl;
	}
};

void test2_help() {
	p.addTask([]() {
		{
			TestDes _;
			m_test2.lock();

			std::cout << "Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			while (c) {
				cond.wait(m_test2);
			};
			std::cout << "Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			m_test2.unlock();
		}
		std::cout << "after wait 1 except false : " << std::boolalpha << m_test2.locked() << std::endl;
	});

	p.addTask([]() {
		{
			m_test2.lock();

			std::cout << "22 Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			while (c) {
				cond.wait(m_test2);
			};
			std::cout << "22 Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			m_test2.unlock();
		}
		std::cout << "22 after wait  except false : " << std::boolalpha << m_test2.locked() << std::endl;
	});

	p.addTask([]() {
		{
			std::unique_lock<co::co_mutex> lk(m_test2);
			std::cout << "start notify" << std::endl;
			c = false;
			cond.notify_all();
			std::cout << "after notify 	" <<  std::boolalpha << m_test2.locked() << std::endl;
		}
		std::cout << "after notify--" << std::boolalpha << m_test2.locked() << std::endl;
	});

	// std::cout << "begin " << p.size() << std::endl;
	p.run();
	// std::cout << "end " << p.size()  << std::endl;
}

void test2_help2() {
	p.addTask([]() {
		{
			TestDes _;
			// m_test2.lock();
			std::unique_lock<co::co_mutex> lk(m_test2);

			std::cout << "Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			while (c) {
				cond.wait(m_test2);
			};
			std::cout << "Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			// m_test2.unlock();
		}
		std::cout << "after wait 1 except false : " << std::boolalpha << m_test2.locked() << std::endl;
	});

	p.addTask([]() {
		{
			// m_test2.lock();
			std::unique_lock<co::co_mutex> lk(m_test2);

			std::cout << "22 Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			while (c) {
				cond.wait(m_test2);
			};
			std::cout << "22 Except true 	" << std::boolalpha << m_test2.locked() << std::endl;
			// m_test2.unlock();
		}
		std::cout << "22 after wait  except false : " << std::boolalpha << m_test2.locked() << std::endl;
	});

	p.addTask([]() {
		{
			std::unique_lock<co::co_mutex> lk(m_test2);
			std::cout << "start notify" << std::endl;
			c = false;
			cond.notify_all();
			std::cout << "after notify 	" <<  std::boolalpha << m_test2.locked() << std::endl;
		}
		std::cout << "after notify--" << std::boolalpha << m_test2.locked() << std::endl;
	});

	// std::cout << "begin " << p.size() << std::endl;
	p.run();
	// std::cout << "end " << p.size()  << std::endl;
}

void test2() {
	p.addTask([]() {
		{
			TestDes _;
			std::unique_lock<co::co_mutex> lk(m_test2);

			auto p = lk.mutex();
			std::cout << "start wait 1 " << std::boolalpha << p->locked() << std::endl;
			while (c) {
				cond.wait(lk);
			};
			std::cout << "Except true 	" << std::boolalpha << p->locked() << std::endl;
		}
		std::cout << "after wait 1 except false : " << std::boolalpha << m_test2.locked() << std::endl;
	});

	p.addTask([]() {
		{
			std::unique_lock<co::co_mutex> lk(m_test2);
			auto p = lk.mutex();
			std::cout << "start wait 2 " << std::boolalpha << p->locked() << std::endl;
			while (c) {
				cond.wait(lk);
			};
		}
		std::cout << "after wait 2 " << std::boolalpha << m_test2.locked() << std::endl;
	});

	p.addTask([]() {
		{
			std::unique_lock<co::co_mutex> lk(m_test2);
			std::cout << "start notify" << std::endl;
			c = false;
			cond.notify_all();
			std::cout << "after notify 	" <<  std::boolalpha << m_test2.locked() << std::endl;
		}
		std::cout << "after notify--" << std::boolalpha << m_test2.locked() << std::endl;
	});

	// std::cout << "begin " << p.size() << std::endl;
	p.run();
	// std::cout << "end " << p.size()  << std::endl;
}

co::co_mutex m_test3;

void test3() {

	p.addTask([]() {
		std::unique_lock<co::co_mutex> lk(m_test3);
		std::cout << "1 start " << std::endl;
		co::yield();
		std::cout << "1 end " << std::endl;
	});

	p.addTask([]() {
		std::unique_lock<co::co_mutex> lk(m_test3);
		std::cout << "2 start " << std::endl;
		std::cout << "2 end " << std::endl;
	});

	std::cout << "begin " << p.size() << std::endl;
	p.run();
	std::cout << "end " << p.size()  << std::endl;
};

int main() {
	test2();
}