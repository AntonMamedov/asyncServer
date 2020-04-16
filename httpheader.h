#pragma once
#include "httpparser.h"


void send_header(int client_d,struct  request_HTTP_data* req_data, unsigned int content_lenght);
void send_error404(int clietn_d);
