
include define.mk

OBJS=coroute.o Task.o taskshduler.o
TARGET=libco.a

.PHONY:all

all:$(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

$(OBJS): %.o: %.cpp
	$(CXX) -c $< $(CXXFLAG)

clean:
	$(call clean) \
	rm main *.o *.out ${OBJ} -rf
