

CXX=arm-linux-gnueabihf-g++

TARGETPATH=../build/arm

INCLUDEDIR:=-I../src/
LIBDIR:=-L$(TARGETPATH)
LIBS:=-lDriver -pthread



.PHONY:test

all:test 

CXXFLAGS = $(INCLUDEDIR) -std=c++11 
TESTCXXFLAGS = $(INCLUDEDIR) $(LIBDIR) -std=c++11 -Wl,--rpath=./ $(LIBS)

testobj = t_zserialport t_calculateweight
testobjtemp := $(testobj:%=$(TARGETPATH)/%)
test:$(testobjtemp)

$(TARGETPATH)/t_zserialport:t_zserialport.o
	$(CXX) $^ -o $@ $(TESTCXXFLAGS) 


$(TARGETPATH)/t_calculateweight:t_calculateweight.o
	$(CXX) $^ -o $@ $(TESTCXXFLAGS) 

clean:
	rm *.o -f
