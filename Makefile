CC = clang
CXX = clang++
CXXFLAGS = -Wall -Wextra -pedantic -O3
.PHONY: all clean

SOURCES = io.cpp ising_complexity.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ising_complexity

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
