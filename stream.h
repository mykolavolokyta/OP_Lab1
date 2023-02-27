#ifndef STREAM_H
#define STREAM_H

//Режим FileStream

std::string get_name(std::string);                                     //Введення імені файлу
void create_file(std::string);								           //Створення файлу та запис змісту до нього
std::string get_text(std::string, int&);							   //Зчитування інформації з файлу в один рядок
std::string* get_data(std::string, int);						       //Перезапис інформації з файла в рядки зі словами(без ком, крапок з комою та зайвих пробілів)
void rewrite_word_strings(std::string*, std::string*, int);            //Розбиття інфорації з файлу по рядкам
void put_shortest_word(std::string*, int);							   //Форматування даних відповідно до умови
std::string find_smallest_word(std::string*, int);			           //Розбиття рядка в масив слів
std::string* divide_into_string(std::string, int);					   //Знаходження найкоротшого слова
void write_data(std::string, std::string*, int);				       //Запис даних в файл
void print_file(std::string);				                           //Виведення інформації з файлу

#endif