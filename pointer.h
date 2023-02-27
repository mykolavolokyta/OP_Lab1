#ifndef POINTER_H
#define POINTER_H

//Режим FilePointer

char* get_name(const char*);								           //Введення імені файлу
void create_file(const char*);								           //Створення файлу та запис змісту до нього
char* get_text(const char*, int&);							           //Зчитування інформації з файлу в один рядок
void rewrite_word_strings(char**, char**, int);						   //Перезапис інформації з файла в рядки зі словами(без ком, крапок з комою та зайвих пробілів)
char** get_data(char*, int);								           //Розбиття інфорації з файлу по рядкам
void put_shortest_word(char**, int);								   //Форматування даних відповідно до умови
char** divide_into_words(char*, int);								   //Розбиття рядка в масив слів
char* find_smallest_word(char**, int);								   //Знаходження найкоротшого слова
void write_data(const char*, char**, int);						       //Запис даних в файл
void print_file(const char*);										   //Виведення інформації з файлу
void free_memory(const char*, const char*, char**, int);               //Звільнення пам'яті

#endif