ROOTDIR=/home/w/git/libco

AR=ar
CXX=clang++
INCLUDE=$(ROOTDIR)/


# ------

DEBUG=-g

OPTIMIZATION=-O0

WALL_INFO=-Wall
#-Wall
#-Werror

STDCPP=-std=c++11

CXXFLAG=-I$(INCLUDE) $(DEBUG) $(OPTIMIZATION) $(WALL_INFO) $(STDCPP)


#----

define make_subdir
	@for subdir in $(SUBDIRS) ; do \
	( cd $$subdir && make -j4 ) \
	done;
endef

define clean
	@for subdir in $(SUBDIRS) ; do \
	( cd $$subdir && make clean) \
	done;
endef
