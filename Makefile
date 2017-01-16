
include define.mk

OBJS=coroute.o Task.o taskshduler.o co_mutex.o co_condition.o
TARGET=libco.a

.PHONY:all

all:$(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAG) -c $< 

clean:
	$(call clean) \
	rm main *.o *.out ${OBJ} -rf
