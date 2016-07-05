CC     = g++
CFLAGS = -std=c++11 -Wall -g -Wno-unused-function -Wno-unused-variable -Wno-sign-compare
LFLAGS = -Wl,--no-as-needed -lprofiler -Wl,--as-needed
SRCS   = $(wildcard *.cpp)
BINS   = $(patsubst %.cpp, %, $(SRCS))

test : $(BINS)
	CPUPROFILE=cpu.profile ./$<
	google-pprof --text ./$< cpu.profile | c++filt

% : %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)

clobber :
	rm -f $(BINS)
	rm -f *.bak
	rm cpu.profile

archive : clobber
	@echo $(SRCS)
	mv *.cpp Archive
	mv *.html Archive

.PHONY : test clobber archive
