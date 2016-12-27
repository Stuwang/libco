#ifndef DEFINE_H__
#define DEFINE_H__

#define DISABLE_COPY(type)\
	type(const type&) = delete;\
	type& operator=(const type&) = delete;

#define DISABLE_MOVE(type)\
	type(type&&) = delete;\
	type& operator=(type&&) = delete;

#define DISABLE_COPY_MOVE(type)\
	DISABLE_MOVE(type)\
	DISABLE_COPY(type)

#endif