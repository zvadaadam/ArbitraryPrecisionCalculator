EXEC = ./zvadaada
CXX = g++
CXXFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11
RM = rm -rf
DXFILE = Doxyfile
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all:
	make compile
	make doc

compile: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)
run:
	$(EXEC)
test:
	$(EXEC) examples/01_in
	$(EXEC) examples/02_in
	$(EXEC) examples/03_in
	$(EXEC) examples/04_in
	$(EXEC) examples/05_in
run_file:
	$(EXEC) examples/$$FILE_NAME

doc:
	cd src
	doxygen $(DXFILE)

clean:
	$(RM) $(OBJS) $(EXEC) doc/ html/ latex/
