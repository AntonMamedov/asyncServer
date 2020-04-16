#include "httpheader.h"

void send_header(int client_d, struct  request_HTTP_data* req_data, unsigned int content_lenght)
{

    write(client_d, "HTTP/1.1 200 OK\r\nServer: RoboCone \r\n",strlen("HTTP/1.1 200 OK\r\nServer: RoboCone \r\n"));
    if (strcmp(req_data->file_extension,"png") == 0 || strcmp(req_data->file_extension,"gif") == 0)
        write(client_d, "Content-Type: image/apng\r\n", strlen("Content-Type: image/apng\r\n"));
    else if (strcmp(req_data->file_extension,"jpg") == 0)
        write(client_d, "Content-Type: image/jpeg\r\n", strlen("Content-Type: image/jpeg\r\n"));
    else
        write(client_d, "Content-Type: text/html\r\n", strlen("Content-Type: text/html\r\n"));
    /*if (req_data->keep_alive > 0)
        write(client_d, "Connection: keep-alive\r\n", strlen("Connection: keep-alive\r\n"));*/
    write(client_d, "Content-Lenght: ", strlen("Content-Lenght: "));
    char lenght[6];
    sprintf(lenght,"%d", content_lenght);
    write(client_d, lenght, strlen(lenght));
    write(client_d, "\r\n\r\n", strlen("\r\n\r\n"));
}
