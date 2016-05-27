#include <iostream>

#include "Task.h"
#include "taskshduler.h"

auto & p = co::gettaskinstense();

void testf1();
void testf2();

void testf1(){
	static int i = 0;
	int tmp = i++;

	p.addTask(testf2);
	std::cout << "AAAAA " << tmp << " start" << std::endl;
	co::yield();
	std::cout << "AAAAA " << tmp << " end" << std::endl;
};

void testf2(){
	static int i = 0;
	int tmp = i++;

	p.addTask(testf1);
	std::cout << "BBBBB " << tmp << " start" << std::endl;
	co::yield();
	std::cout << "BBBBB " << tmp << " end" << std::endl;
}

int main(){
	p.addTask(testf1);

	std::cout << "begin " << p.size() << std::endl;
	p.run();
	std::cout << "end " << p.size()  << std::endl;
}