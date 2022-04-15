CXXFLAGS += -O3 -std=c++17 -Wall -Wextra -pedantic-errors

all: build/main

build/main: build/main.o build/util.o build/neuron.o build/net.o build/journey.o build/environment.o build/net_k_server_decoder.o
	$(CXX) $(CXXFLAGS) -o build/main build/*.o

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

build/util.o: src/util.cpp
	$(CXX) $(CXXFLAGS) -c src/util.cpp -o build/util.o

build/neuron.o: src/neuron.cpp
	$(CXX) $(CXXFLAGS) -c src/neuron.cpp -o build/neuron.o

build/net.o: src/net.cpp
	$(CXX) $(CXXFLAGS) -c src/net.cpp -o build/net.o

build/journey.o: src/journey.cpp
	$(CXX) $(CXXFLAGS) -c src/journey.cpp -o build/journey.o

build/environment.o: src/environment.cpp
	$(CXX) $(CXXFLAGS) -c src/environment.cpp -o build/environment.o

build/net_k_server_decoder.o: src/net_k_server_decoder.cpp
	$(CXX) $(CXXFLAGS) -c src/net_k_server_decoder.cpp -o build/net_k_server_decoder.o

clean:
	$(RM) build/*.o build/main