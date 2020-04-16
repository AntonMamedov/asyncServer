#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "secondaryfunctions.h"



typedef enum
{
    UNKNOWN
   ,GET
   ,POST
}HTTPMethod;


struct request_HTTP_data // содержит необходимые данные о запросе
{
    int size;
    int keep_alive;
    char* body;
    char* file_name;
    char* file_extension;
    HTTPMethod type;
};





void parse_HTTP_message(char* request, struct  request_HTTP_data* req_data); // собирает функции ниже в кучу
void URL_parse(char* request, struct  request_HTTP_data* req_data); // парсит первую строчку запроса
void BODY_parse(char* request, struct  request_HTTP_data* req_data); //парсит тело запроса
void extension_parse(struct  request_HTTP_data* req_data); //парсит расширение файла
