PROGNAME=brainfuck-interpreter
SRC_DIR=src

all:
	@echo "Compiling interpreter..."
	@c++ -o $(PROGNAME) $(SRC_DIR)/*.cpp
	@echo "Done"
run:
	@echo "Usage: ./$(PROGNAME) <FILENAME>"
