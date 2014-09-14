CC     = g++
CFLAGS = -std=c++11 -Wall -g
LFLAGS = -Wl,--no-as-needed -lprofiler -Wl,--as-needed
SRCS   = $(wildcard *.cpp)
BINS   = $(patsubst %.cpp, %, $(SRCS))

test : $(BINS)
	PUPROFILE=cpu.profile ./$<
	google-pprof --text ./$< cpu.profile 

% : %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)

clobber :
	rm -f $(BINS)
	rm -f *.bak

archive : clobber
	@echo $(SRCS)
	mv *.cpp Archive
	mv *.html Archive

.PHONY : test clobber archive
