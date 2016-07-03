#include <iostream>
#include <mutex>

using namespace std;

class my_lock {
public:
	my_lock(): locked_(false) {};

	void lock() {
		m_.lock();
		locked_ = true;
	};
	void unlock() {
		m_.unlock();
		locked_ = false;
	};
	bool locked() {
		return locked_;
	}
// private:
	mutex m_;
	bool locked_;
};

int main() {
	my_lock m;
	{
		std::unique_lock<my_lock> lk(m);
		lk.unlock();
		lk.lock();
	}
	cout << "locked :" << boolalpha << m.m_.try_lock() << endl;
}
