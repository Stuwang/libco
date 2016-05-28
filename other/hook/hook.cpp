#include <cstring>
#include <cstdlib>
#include <dlfcn.h>

typedef size_t(*read_t)(int,void *,size_t);
static read_t read_f = NULL;

typedef size_t(*write_t)(int, const void *, size_t);
static write_t write_f = NULL;

void hook_init(){
	
	static bool inited = false;
	if(inited) return;

	read_f = (read_t)dlsym(RTLD_NEXT, "read");
	write_f = (write_t)dlsym(RTLD_NEXT, "write");

	inited = true;

};

size_t read(int fd,void * data,size_t size){
	if(!read_f) hook_init();

	const char * msg_read_begin = 	"begin read\n";
	const char * msg_read_end = 	"end read\n";

	write_f(1,msg_read_begin,strlen(msg_read_begin));
	size_t ret = read_f(fd,data,size);
	write_f(1,msg_read_end,strlen(msg_read_end));
	return ret;
};

size_t write(int fd,const void * data,size_t size){
	if(!read_f) hook_init();

	const char * msg_read_begin = "begin write\n";
	const char * msg_read_end = "end write\n";

	write_f(1,msg_read_begin,strlen(msg_read_begin));
	size_t ret = write_f(fd,data,size);
	write_f(1,msg_read_end,strlen(msg_read_end));
	return ret;
};

int main(){
	const char * p = "hello\n";
	write(1,p,6);
}