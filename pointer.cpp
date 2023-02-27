#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "pointer.h"


char* get_name(const char* message) {
	std::cout << message;
	char* name = new char[256];
	std::cin.getline(name, 256);
	return name;
}

void create_file(const char* filename) {

	FILE* file;
	bool flag_created = false;

	//Файл вже створено
	if ((file = fopen(filename, "r")) != NULL) {
		fclose(file);
		flag_created = true;
	}

	//Неможливо створити/відкрити файл
	if ((file = fopen(filename, "a")) == NULL) {
		std::cout << "[ERROR] Can`t create/open file.\n";
		exit(0);
	}

	if (flag_created) {
		std::cout << "File \"" << filename << "\" will be appended\n\n";
	}
	else {
		std::cout << "File \"" << filename << "\" was successfully created\n\n";
	}

	std::cout << "Enter text. Type \"cocojambo\" on new line to stop.\n\n";

	//Введення даних в файл
	char* temp = new char[256];
	while (true) {
		std::cin.getline(temp, 255);
		if (strcmp(temp, "cocojambo") == 0) break;
		fprintf(file, "%s\n", temp);
	}
	delete[] temp;

	fclose(file);
	std::cout << "\nText was successfully added to file.\n";
}



char* get_text(const char* filename, int& rows) {
	FILE* file = fopen(filename, "r");
	char* text = new char[32768];

	//Зчитування інформації з файлу
	int i = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			text[i] = ' ';
		}
		else {
			text[i] = ch;
			if (ch == '.') {
				rows++;
			}
		}
		i++;
	}
	fclose(file);
	return text;
}


char** get_data(char* text, int rows) {
	char** data = new char* [rows];
	for (int i = 0; i < rows; i++) {
		data[i] = new char[1024];
	}

	//Розбиття рядка на речення
	char* token = strtok(text, ".");
	std::cout << "\nSentences in file:\n\n";
	for (int i = 0; i < rows; i++) {
		i == 0 ? strcpy(data[i], token) : strcpy(data[i], token + 1);
		std::cout << data[i] << ".\n";
		token = strtok(NULL, ".");
	}
	delete[] text;
	return data;
}


void put_shortest_word(char** data, int rows) {
	char** word_strings = new char* [rows];
	for (int i = 0; i < rows; i++) {
		word_strings[i] = new char[1024];
	}

	//Формування рядків з словами(без ком та крапок з комою)
	rewrite_word_strings(data, word_strings, rows);

	//Знаходження кількості слів в кожному рядку
	int* word_count = new int[rows] {};
	for (int i = 0; i < rows; i++) {
		word_count[i] = 1;
		for (int j = 0; word_strings[i][j] != '\0'; j++) {
			if (word_strings[i][j] == ' ') {
				word_count[i]++;
			}
		}
	}

	//Додавання найменшого слова до масиву data
	std::cout << "\nShortest words in sentencences:\n\n";
	for (int i = 0; i < rows; i++) {
		char** words = divide_into_words(word_strings[i], word_count[i]);
		char* smallest_word = find_smallest_word(words, word_count[i]);
		char* add_string = new char[32];
		sprintf(add_string, ". %d - %s", strlen(smallest_word), smallest_word);
		strcat(data[i], add_string);
		std::cout << data[i] << '\n';

		//Звільнення пам'яті
		for (int j = 0; j < word_count[i]; j++) {
			delete[] words[j];
		}
		delete[] words;
		delete[] smallest_word;
		delete[] add_string;
	}

	for (int i = 0; i < rows; i++) {
		delete[] word_strings[i];
	}
	delete[] word_strings;
	delete[] word_count;
}


void rewrite_word_strings(char** data, char** word_strings, int rows) {
	for (int i = 0; i < rows; i++) {
		int k = 0;
		for (int j = 0; j < strlen(data[i]); j++) {
			if (data[i][j] != ',' && data[i][j] != ';') {
				if (!(data[i][j] == ' ' && data[i][j + 1] == ' ')) {     //декілька пробілів підряд
					word_strings[i][k] = data[i][j];
					k++;
				}
			}
		}
		word_strings[i][k] = '\0';
	}
}


char** divide_into_words(char* str, int count) {
	char** words = new char* [count];
	for (int i = 0; i < count; i++) {
		words[i] = new char[32];
	}

	char* token = strtok(str, " ");
	for (int i = 0; i < count; i++) {
		strcpy(words[i], token);
		token = strtok(NULL, " ");
	}
	return words;
}


char* find_smallest_word(char** words, int count) {
	char* smallest_word = new char[32];
	strcpy(smallest_word, words[0]);
	for (int i = 1; i < count; i++) {
		if (strlen(words[i]) < strlen(smallest_word)) {
			strcpy(smallest_word, words[i]);
		}
	}
	return smallest_word;
}


void write_data(const char* filename, char** data, int rows) {
	FILE* file;
	if ((file = fopen(filename, "r")) != NULL) {             //Файл вже існує
		fclose(file);
		std::cout << "[ERROR] File already exists.\n";
		exit(0);
	}
	if ((file = fopen(filename, "w")) == NULL) {             //Неможливо створити файл
		std::cout << "[ERROR] Can`t create file.\n";
		exit(0);
	}
	for (int i = 0; i < rows; i++) {
		fprintf(file, "%s\n", data[i]);
	}
	fclose(file);

	std::cout << "Successfully created and filled file \"" << filename << "\"\n";
}


void print_file(const char* filename) {
	std::cout << '\n' << filename << ":\n";
	FILE* file = fopen(filename, "r");
	char ch;
	while ((ch = fgetc(file)) != EOF) {
		std::cout << ch;
	}
	fclose(file);
}


void free_memory(const char* filename, const char* result, char** data, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] data[i];
	}
	delete[] data;
	delete[] filename;
	delete[] result;
}