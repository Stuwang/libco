#ifndef CHAN_H__
#define CHAN_H__

#include <tuple> //std::ignore
#include <queue>
#include <memory>

#include "define.h"
#include "co_mutex.h"
#include "co_condition.h"

namespace co {

namespace detail {

template<class T>
struct ChanImpl {
	DISABLE_COPY_MOVE(ChanImpl);

	explicit ChanImpl(int s): size(s) {};
	~ChanImpl() {};


	int size;
	std::queue<T> data_;
	// spinlock  m_;

	co_condition cond_;
	co_mutex mutex_;

	size_t size() const {
		std::unique<spinlock> lock(mutex_);
		return data_.size();
	};

	bool empty() const {
		std::unique<spinlock> lock(mutex_);
		return data_.empty();
	};

	void push(const T& data) {
		std::unique<spinlock> lock(mutex_);
		while (data_.size() == size) {
			cond_.wait(lock);
		}
		data_.push(data);
	};

	T pop() {
		std::unique<co_mutex> lk(mutex_);
		while (data_.size() == 0 ) {
			cond_.wait(lk);
		}
		T ret = data_.front();
		return ret;
	};

}; // detail

template<class T>
class Chan {
public:
	Chan() {
		impl_ .reset(new detail::ChanImpl<T>(16));
	};

	explicit Chan(int size) {
		assert(size > 0);
		impl_ .reset(new detail::ChanImpl<T>(size));
	};

	~Chan() {
		impl_.reset();
	}

	size_t size()const {
		return impl_->size();
	};
	bool empty()const {
		return impl_->empty();
	};

	friend Chan& operator<<(Chan& self, const T& data) {
		self.impl_->push(data);
		return self;
	};

	friend Chan& operator>>(Chan& self, T& data) {
		data = self.impl_->pop();
		return self;
	};

	friend Chan& operator>>(Chan& self, decltype(std::ignore) ) {
		data = self.impl_->pop();
		return self;
	};

private:
	std::shared_ptr<ChanImpl<T>> impl_;
};

template<>
class Chan<void> {
public:
	Chan() {
		impl_ .reset(new detail::ChanImpl<int>(16));
	};

	explicit Chan(int size) {
		assert(size > 0);
		impl_ .reset(new detail::ChanImpl<int>(size));
	};

	~Chan() {
		impl_.reset();
	}

	size_t size()const {
		return impl_->size();
	};
	bool empty()const {
		return impl_->empty();
	};

	friend Chan& operator<<(Chan& self, decltype(std::ignore)) {
		self.impl_->push(1);
		return self;
	};

	friend Chan& operator>>(Chan& self, decltype(std::ignore) ) {
		self.impl_->pop();
		return self;
	};

private:
	std::shared_ptr<ChanImpl<int>> impl_;
};

}// co

#endif