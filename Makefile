CC     = g++
CFLAGS = -std=c++11 -Wall
SRCS   = $(wildcard *.cpp)
BINS   = $(patsubst %.cpp, %, $(SRCS))

test : $(BINS)
	./$<

% : %.cpp
	$(CC) $(CFLAGS) $< -o $@

clobber :
	rm -f $(BINS)
	rm -f *.bak

archive : clobber
	@echo $(SRCS)
	mv *.cpp Archive
	mv *.html Archive

.PHONY : test clobber archive
