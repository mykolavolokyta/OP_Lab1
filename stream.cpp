#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "stream.h"


std::string get_name(std::string message) {
	std::cout << message;
	std::string filename;
	std::getline(std::cin, filename);
	return filename;
}


void create_file(std::string filename) {
	//Перевірка на існування файлу
	bool file_exists = false;
	{
		std::ifstream check;
		check.open(filename);
		if (check) file_exists = true;
	}

	//Неможливо створити/відкрити файл
	std::ofstream outf(filename, std::ios::app);
	if (!outf) {
		std::cout << "[ERROR] Can`t create/open file.\n";
		exit(0);
	}

	if (file_exists) {
		std::cout << "File \"" << filename << "\" will be appended\n\n";
	}
	else {
		std::cout << "File \"" << filename << "\" was successfully created\n\n";
	}

	std::cout << "Enter text. Type \"cocojambo\" on new line to stop.\n\n";

	//Введення даних в файл
	std::string temp;
	while (true) {
		std::getline(std::cin, temp);
		if (temp == "cocojambo") break;
		outf << temp << '\n';
	}

	std::cout << "\nText was successfully added to file.\n";
}


std::string get_text(std::string filename, int& rows) {
	std::string text{ "" };
	std::ifstream inf(filename);

	//Зчитування інформації з файлу
	while (inf)
	{
		char ch;
		inf >> std::noskipws >> ch;
		if (ch == '\n') {
			text += ' ';
		}
		else {
			text += ch;
			if (ch == '.') {
				rows++;
			}
		}
	}
	return text;
}


std::string* get_data(std::string text, int rows) {
	std::string* data = new std::string[rows];
	std::string temp;
	std::stringstream ss;
	ss << text;

	std::cout << "\nSentences in file:\n\n";

	for (int i = 0; i < rows; i++) {
		std::getline(ss, temp, '.');
		if (i != 0) temp.erase(temp.begin());
		data[i] = temp;
		std::cout << data[i] << ".\n";
	}
	return data;
}


void put_shortest_word(std::string* data, int rows) {
	std::string* word_strings = new std::string[rows];
	rewrite_word_strings(data, word_strings, rows);
	int* word_count = new int[rows] {};

	for (int i = 0; i < rows; i++) {
		word_count[i] = 1;
		for (int j = 0; j < word_strings[i].length(); j++) {
			if (word_strings[i][j] == ' ') {
				word_count[i]++;
			}
		}
	}

	//Додавання найменшого слова до масиву data
	std::cout << "\nShortest words in sentencences:\n\n";

	for (int i = 0; i < rows; i++) {
		std::string* words = divide_into_string(word_strings[i], word_count[i]);
		std::string smallest_word = find_smallest_word(words, word_count[i]);
		data[i] = data[i] + ". " + std::to_string(smallest_word.length()) + " - " + smallest_word;
		std::cout << data[i] << '\n';

		delete[] words;
	}

	delete[] word_strings;
	delete[] word_count;
}


void rewrite_word_strings(std::string* data, std::string* word_strings, int rows) {
	for (int i = 0; i < rows; i++) {
		word_strings[i] = "";
		for (int j = 0; j < data[i].length(); j++) {
			if (data[i][j] != ',' && data[i][j] != ';') {
				if (!(data[i][j] == ' ' && data[i][j + 1] == ' ')) {
					word_strings[i] += data[i][j];
				}
			}
		}
	}
}


std::string* divide_into_string(std::string str, int count) {
	std::string* words = new std::string[count];
	std::stringstream ss;
	ss << str;
	for (int i = 0; i < count; i++) {
		std::getline(ss, words[i], ' ');
	}
	return words;
}


std::string find_smallest_word(std::string* words, int count) {
	std::string smallest_word = words[0];
	for (int i = 0; i < count; i++) {
		if (words[i].length() < smallest_word.length()) {
			smallest_word = words[i];
		}
	}
	return smallest_word;
}


void write_data(std::string filename, std::string* data, int rows) {
	{
		std::ifstream check;
		check.open(filename);
		if (check) {
			check.close();
			std::cout << "[ERROR] File already exists.\n";
			exit(0);
		}
	}

	std::ofstream outf(filename);
	if (!outf) {
		std::cout << "[ERROR] Can`t create file.\n";
		exit(0);
	}
	for (int i = 0; i < rows; i++) {
		outf << data[i] << '\n';
	}

	std::cout << "Successfully created and filled file \"" << filename << "\"\n";
}


void print_file(std::string filename) {
	std::cout << '\n' << filename << ":\n";
	std::ifstream inf(filename);
	while (inf)
	{
		std::string str;
		std::getline(inf, str);
		std::cout << str << '\n';
	}
}