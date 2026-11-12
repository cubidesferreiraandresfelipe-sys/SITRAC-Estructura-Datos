CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = sitrac
SRCS = src/main.cpp src/Pasajero.cpp src/Cola.cpp src/Grafo.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: clean
