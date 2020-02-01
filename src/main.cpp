#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define NCELLS 30000
#define cell_t unsigned int

// enum for command line arguments
enum {
	PROGNAME,
	FILENAME,
	NARGS
};

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
		std::cerr << "ERROR: Could not open " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	// passing file content to string buffer
	std::stringstream buff;
	buff << file.rdbuf();
	file.close();

	// returning string containing whole file
	return buff.str();
}

void check_syntax(std::string file, bool strict) {
	int n = std::count(file.begin(), file.end(), '[');

	if(n != std::count(file.begin(), file.end(), ']')) {
		std::cerr << "ERROR: Unbalanced number of brackets"
				  << std::endl;
		exit(EXIT_FAILURE);
	}

	if(strict) {
		unsigned int n_line = 1, n_col;
		std::string line;
		std::stringstream ss(file);
		std::string valid(" \n\r\t<>.,+-[]");
		bool error = false;

		while(!ss.eof()) {
			getline(ss, line);
			n_col = 0;
			// iterate through each character
			for(auto c : line) {
				if(valid.find(c) == std::string::npos) {
					error = true;
					std::cerr << "ERROR: Invalid character '"
							  << c << "' in line " << n_line
							  << ", column " << n_col << std::endl;
				}
				n_col++;
			}
			n_line++;
		}
		if(error)
			exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	// error checking on number of arguments
	if(argc != NARGS) {
		std::cerr << "Usage: " << argv[PROGNAME]
				  << " <FILENAME> "<< std::endl;
		exit(EXIT_FAILURE);
	}

	std::string file = read_file(argv[FILENAME]);

	check_syntax(file, true);

	parse_file(file);
}
