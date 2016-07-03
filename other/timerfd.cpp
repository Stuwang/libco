#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <functional>

using namespace std;

#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void print_elapsed_time(void)
{
	static struct timespec start;
	struct timespec curr;
	static int first_call = 1;
	int secs, nsecs;

	if (first_call) {
		first_call = 0;
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
			return;
	}

	if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
		return;

	secs = curr.tv_sec - start.tv_sec;
	nsecs = curr.tv_nsec - start.tv_nsec;
	if (nsecs < 0) {
		secs--;
		nsecs += 1000000000;
	}

	cout << secs << '.' << ((nsecs + 500000) / 1000000) << endl ;
}

class mytimer {
public:
	typedef std::function<void()> timer_fun_t;

	mytimer(const timer_fun_t& fun_, struct timespec time_):
		m_fun(fun_),
		time(time_)
	{
	};

	~mytimer() {
		close(fd);
	};
	void run() {

		struct timespec cur;
		if (clock_gettime(CLOCK_MONOTONIC, &cur) == -1)
			handle_error("clock_gettime");

		struct timespec first_time {0, 0};
		// first_time.tv_sec += cur.tv_sec + 1;
		// first_time.tv_nsec += cur.tv_nsec + 100000;

		first_time.tv_sec += 1;
		first_time.tv_nsec = 0;

		new_value.it_value = first_time;
		new_value.it_interval = time;

		// new_value.it_interval.tv_sec = 2;
		// new_value.it_interval.tv_nsec = 0;

		// new_value.it_value.tv_sec = 2;
		// new_value.it_value.tv_nsec = 0;



		fd = timerfd_create(CLOCK_MONOTONIC, 0);
		print_elapsed_time();



		timerfd_settime(fd, 0, &new_value, NULL);
		print_elapsed_time();


		int i = 0;
		bool flag = true;
		while (true) {

			uint64_t exp;
			auto s = read(fd, &exp, sizeof(uint64_t));
			if (s != sizeof(uint64_t)) {
				handle_error("error in first");
				continue;
			}
			if (m_fun) {
				m_fun();
			}

			// new_value.it_interval.tv_sec += 2;
			// timerfd_settime(fd, 0, &new_value, NULL);

			if (flag) {
				timerfd_gettime(fd, NULL);

				new_value.it_interval = time;
				new_value.it_interval.tv_sec += 2;

				new_value.it_value = time;
				new_value.it_value.tv_sec = 2;

				timerfd_settime(fd, 0, &new_value, NULL);
			}

		}
	};
private:
	const timer_fun_t m_fun;
	int fd;
	struct itimerspec new_value;
	struct timespec time;
};

void fun() {
	print_elapsed_time();
	cout << "what the fuck !" << endl;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	struct timespec time {1, 0};
	mytimer m(fun, time);
	m.run();
}