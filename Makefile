CPP=g++
SOURCES=discreteSIR.cpp data.cpp main.cpp
EXECUTABLE=ims_project

all: compile

compile: $(SOURCES)
	$(CPP) $(SOURCES) -o $(EXECUTABLE)

run: $(SOURCES) compile
	./$(EXECUTABLE)
	
clean: $(EXECUTABLE)
	rm $(EXECUTABLE)

