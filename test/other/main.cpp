#include <iostream>

#include "Task.h"

using namespace co;
using namespace std;

void test(){
	cout << "for test" << endl;
};

int main(){
	shared_ptr<Task> p {new Task(test)};
	p->SwapIn();
	cout << "good " << endl;
};
