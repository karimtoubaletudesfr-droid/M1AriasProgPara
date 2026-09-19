CXX = mpic++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -DOMPI_SKIP_MPICXX

hello: hello.cpp
	$(CXX) $(CXXFLAGS) hello.cpp -o hello

clean:
	rm -f hello