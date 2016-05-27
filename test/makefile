include ../define.mk
CXXFLAG_LINK+= -lco -I.. -L..

all:main.o
	$(CXX) $< -o test.out $(CXXFLAG_LINK)

main.o:main.cpp
	$(CXX) -c $< $(CXXFLAG)

clean:
	$(call clean) \
	rm main *.o *.out ${OBJ} -rf