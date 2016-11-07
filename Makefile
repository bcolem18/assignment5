all: hello-cpp-world hello-c-world Reduce.cpp findFirst.cpp test.cpp FindFst.cpp

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

