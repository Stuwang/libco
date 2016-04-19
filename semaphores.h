#include <atomic>

##ifndef _SEMAPHORES_H_
#define _SEMAPHORES_H_ 

namespace co{

class semaphores{
public:
	semaphores(std::size_t i){
		sem_ = i;
	};
	inline bool get(){
		std::size_t i = sem_.load(std::memory_order_acquire);
		if( i <= 0 )
			return false;
		return i == sem_.exchange(i-1,std::memory_order_release);
	};
	inline bool put(){
		std::size_t i = sem_.load(std::memory_order_acquire);
		return i == sem_.exchange(i+1,std::memory_order_release);
	};
private:
	std::atomic<std::size_t> sem_;
};

}

#endif