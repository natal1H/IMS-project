CPP=g++
SOURCES=sir.cpp data.cpp main.cpp
EXECUTABLE=ims_project

all: build

build: $(SOURCES)
	$(CPP) $(SOURCES) -o $(EXECUTABLE)

run: $(SOURCES) compile
	./$(EXECUTABLE) $(ARGS)
	
clean: $(EXECUTABLE)
	rm $(EXECUTABLE)

