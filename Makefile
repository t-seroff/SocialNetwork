CXX = g++

CXXFLAGS = -x c++ -g -Wall -Werror -Wextra

BINARIES = prog3

all: $(BINARIES)

prog3: Main.o Network.o ProfileManager.o BPlusTree.o FriendshipGraph.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f $(BINARIES) *.o profileData.txt

