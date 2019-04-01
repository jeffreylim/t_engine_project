CC := g++

CXXFLAGS := -g -Wall -std=c++14 
LFLAGS := -O3 -march=native
DEPS := Shape.hpp

TARGET := project

SRCDIR := src
SRCEXT := cpp
OBJDIR := obj

all: $(TARGET)

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/Game.o
	$(CC) $(LFLAGS) -o $@ $^
	@echo ./$@ linked successfully...

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(SRCDIR)/$(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) -c -o $@ $<

tar:
	tar -cvzf $(TARGET).tar.gz *

clean :
	@echo "Cleaning up...";
	rm -r $(OBJDIR)
	rm ./$(TARGET)
	@echo "Completed cleaning." 
