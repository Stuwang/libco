
include define.mk

OBJS=coroute.o Task.o
TARGET=libco.a

.PHONY:all

all:$(OBJS)
	$(AR) -v -q $(TARGET) $(OBJS)
$(OBJS): %.o: %.cpp
	$(CXX) -c $< $(CXXFLAG)

clean:
	rm *.o
