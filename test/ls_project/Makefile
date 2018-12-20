CXXFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++11
CXX=g++

.PHONY: clean
all:	ls1 ls2 ls3 ls4 ls5
	@echo "ls_project is up-to-date."
ls1:	ls1.cpp
	mkdir -p ls1
	$(CXX) -o ls1/ls ls1.cpp $(CXXFLAGS)
ls2:	ls2.cpp
	mkdir -p ls2
	$(CXX) -o ls2/ls ls2.cpp $(CXXFLAGS)
ls3:	ls3.cpp
	mkdir -p ls3
	$(CXX) -o ls3/ls ls3.cpp $(CXXFLAGS)
ls4:	ls4.cpp
	mkdir -p ls4
	$(CXX) -o ls4/ls ls4.cpp $(CXXFLAGS)
ls5:	ls5.cpp
	mkdir -p ls5
	$(CXX) -o ls5/ls ls5.cpp $(CXXFLAGS)

clean:
	rm -rf ls?
