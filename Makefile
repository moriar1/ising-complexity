CC = clang
CXX = clang++
CXXFLAGS = -Wall -Wextra -pedantic -O3 -I include
.PHONY: all clean

SRCDIR := src
OBJDIR := obj
INCDIR := include
BINDIR := bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)  # Automatically find .cpp files in src
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES)) # Convert src/*.cpp to obj/*.o
EXECUTABLE := ising_complexity

all: $(BINDIR)/$(EXECUTABLE)

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
