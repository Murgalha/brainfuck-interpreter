#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>

// enum for command line arguments
enum {
	PROGNAME,
	FILENAME,
	NARGS
};

std::string read_file(std::string filename) {
	// opening given file
	std::fstream file(filename, std::fstream::in);

	// check for error on opening file
	if(file.fail()) {
		std::cout << "ERROR: Could not open " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	// passing file content to string buffer
	std::stringstream buff;
	buff << file.rdbuf();
	file.close();

	// returning string containing whole file
	return buff.str();
}

int main(int argc, char *argv[]) {
	// error checking on number of arguments
	if(argc != NARGS) {
		std::cout << "Usage: " << argv[PROGNAME]
				  << " <FILENAME> "<< std::endl;
		exit(EXIT_FAILURE);
	}

	std::string file = read_file(argv[FILENAME]);
}
