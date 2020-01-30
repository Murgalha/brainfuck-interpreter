#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define NCELLS 30000
#define cell_t unsigned int

// enum for command line arguments
enum {
	PROGNAME,
	FILENAME,
	NARGS
};

int signal_of(int n) {
	if(n < 0)
		return -1;
	return 1;
}

void print_n(std::vector<cell_t> tape, int n) {
	for(int i = 0; i < n; i++) {
		std::cout << tape[i] << " ";
	}
	std::cout << std::endl;
}

void goto_matching_bracket(std::string::iterator &it) {
	char ref, target;
	int balance_counter = 0, inc;

	if(*it == '[') {
		ref = '[';
		target = ']';
		inc = 1;
	}
	else {
		ref = ']';
		target = '[';
		inc = -1;
	}

	while(true) {
		if(*it == ref)
			balance_counter++;
		else if(*it == target)
			balance_counter--;

		if(balance_counter == 0) {
			// found the matching bracket
			return;
		}
		// goes forward if looking for ']'
		// goes backward if looking for '['
		it += inc;
	}
	return;
}

void parse_file(std::string file_content) {
	std::string::iterator it = file_content.begin();

	std::vector<cell_t> tape(NCELLS, 0);
	int pointer = 0, offset;

	while(it != file_content.end()) {
		switch(*it) {
		case '>':
			pointer++;
			break;
		case '<':
			pointer--;
			break;
		case '+':
			tape[pointer]++;
			break;
		case '-':
			tape[pointer]--;
			break;
		case '.':
			std::cout << (char)tape[pointer];
			break;
		case ',':
			char c;
			std::cin.get(c);
			tape[pointer] = c;
			break;
		case '[':
			if(tape[pointer] == 0) {
				goto_matching_bracket(it);
			}
			break;
		case ']':
			if(tape[pointer] != 0) {
				goto_matching_bracket(it);
			}
			break;
		default:
			break;
		}
		it++;
	}
}

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

	parse_file(file);
}
