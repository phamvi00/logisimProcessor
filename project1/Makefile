CC = g++        # the compiler to use
LD = $(CC)      # command used to link objects

INCDIR = -I../  # additional directories to look for include files

CCFLAGS = -Wall -std=c++17 $(INCDIR) -g -c  # compiler options
LDFLAGS = -Wall -std=c++17 -g               # linker options

OBJS = main.o command.o
EXECS = ASSEMBLE

all: $(EXECS)
ASSEMBLE: $(OBJS)
	$(LD)  $(LDFLAGS) $(OBJS) -o ASSEMBLE

main.o: main.cpp command.h
	$(CC)  $(CCFLAGS) main.cpp

command.o: command.cpp command.h
	$(CC)  $(CCFLAGS) command.cpp

clean:
	/bin/rm -f $(OBJS) $(EXECS) 
