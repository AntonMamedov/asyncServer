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
#pragma once
#include <sys/stat.h>
#include "httpparser.h"
#define REQUEST_BUFFER_SIZE 65536
#include "secondaryfunctions.h"
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define SERVER_PORT    "8000"
#define MAX_CONNECTION 1000


int sort_addr(struct addrinfo *servinfo); // перебирает структуру servinfo и находит нужный элемент для создания соккета
int create_socket(const char *Port); // создает серверный сокет




void free_request_data(struct  request_HTTP_data* req_data); // очистка структуры


int create_client(const int server_d); // создает клиентский соккет



char* get_request(int client_d); // читает сообщение из соккета




void request_processing_http(int client_d,struct request_HTTP_data* req_data);

//void WSsend(int client_d, char* buf, WSdatatype opcode, int fin);
void sendall(int client_d, char* buf, unsigned long size);
