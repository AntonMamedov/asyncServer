#pragma once
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>



int str_search_symbol(const char *str,const char symbol); // возвращает индекс заданного символа
int str_index_symbol_search(const char *str,const char symbol, const unsigned int index); // производит поиск элемента начиная от заданного индекса и возвращает индекс найденного элемента
char* copy_str_range(char *ctr, unsigned int start, unsigned int end); //коипирует кусок строки в другую строку
char* concat(char *s1, char *s2); //конкатенация строк


unsigned int file_size(int fd);
void comparse(char* com, char* arg[], int comlenght);
void pcreate(char* com, int* fdin_, int* fdout_);


void binary_representation(char* bits, char bit);


