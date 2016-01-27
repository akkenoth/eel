CXX=g++
CXXFLAGS=-std=gnu++11 -Wall -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter
LFLAGS=-lglut -lGLEW -lGL -lpng -lz

SRC=$(wildcard eel/*/*.cpp) eel/main.cpp
OBJECTS=$(patsubst eel/%,Obj/%,$(SRC:.cpp=.o))
DEPS=$(OBJECTS:.o=.d)

generate_deps = $(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $< | sed -n "H;$$ {g;s@.*:\(.*\)@$< := \$$\(wildcard\1\)\n$*.o $@: $$\($<\)@;p}" > $@'
-include $(DEPS)

run: Bin/eel
	@ cd ./eel; ../Bin/eel; cd ..

all: Bin/eel

Bin/eel: $(OBJECTS) $(DEPS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o Bin/eel

Obj/%.d: eel/%.cpp
	mkdir -p $(@D)
	@echo -n $(@D) > $@
	@echo -n "/" >> $@
	$(CXX) -MM $(CXXFLAGS) $< >> $@

Obj/%.o: eel/%.cpp Obj/%.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) $(DEPS) Bin/eel

.PHONY: all clean

