#include <iostream>
#include <string>
#include "mode.h"
#include "pointer.h"
#include "stream.h"

int main(int argc, char* argv[]) {
	switch (set_mode(argc, argv)) {

	//Неправильний ввід
	case 0:
		std::cout << "[ERROR] Usage: lab1.exe -mode [FilePointer | FileStream]\n";
		break;

	//Режим FilePointer 
	case 1:                                                                                                                         
	{
		std::cout << "FilePointer mode activated\n\n";
		const char* filename{ get_name("Enter name of file you want to create(if file exists, it will be appended): ") };
		create_file(filename); 
		int rows{ 0 };
		char* text = get_text(filename, rows);
		char** data = get_data(text, rows);
		put_shortest_word(data, rows);
		const char* result{ get_name("\nEnter name of file with results: ") };
		write_data(result, data, rows);
		print_file(filename);
		print_file(result);
		free_memory(filename, result, data, rows);
		break;
	}

	//Режим FileStream
	case 2:                                                                                                                         
	{
		std::cout << "FileStream mode activated\n";
		std::string message("Enter name of file you want to create(if file exists, it will be appended): ");
		std::string filename{ get_name(message) };
		create_file(filename);
		int rows{ 0 };
		std::string text = get_text(filename, rows);
		std::string* data = get_data(text, rows);
		put_shortest_word(data, rows);
		message = "\nEnter name of file with results: ";
		std::string result{ get_name(message) };
		write_data(result, data, rows);
		print_file(filename);
		print_file(result);
		delete[] data;
	}
	}
	return 0;
}