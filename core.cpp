#include "core.h"
#include <string.h>
#include <stdio.h>
#include <httpheader.h>
#define READ_BUFFER_SIZE 1024


// ------------------------ FREE------------------------//

void free_request_data(struct  request_HTTP_data* req_data)
{
   /* if (req_data->body != NULL)
        free(req_data->body);*/
    if (req_data->file_extension != NULL)
        free(req_data->file_extension);
    if (strcmp(req_data->file_name, "index.html") != 0)
        free(req_data->file_name);
}




// ------------------------ CLIENT-------------------------//
int create_client(int server_d)
{
    int client_d;
    struct sockaddr_storage client_addr;
    socklen_t s_size = sizeof(client_addr);
    client_d = accept(server_d, (struct sockaddr*)&client_addr, &s_size);
    return client_d;
}




char* get_request(int client_d)
{
    char* request = (char*)malloc(REQUEST_BUFFER_SIZE * sizeof(char));
    ssize_t bytes_recvd = recv(client_d, request, REQUEST_BUFFER_SIZE - 1, 0);
    if (bytes_recvd <= 0)
    {
        free(request);
        return NULL;
    }
    request[bytes_recvd] = '\0';
    return request;
}




//**************************Обработка запросов***********************///


void request_processing_http(int client_d, struct request_HTTP_data* req_data)
{
    char* test = concat("/home/anton/", req_data->file_name);
    int fd = open(test, O_RDONLY);
    free(test);
    if (fd > 0)
    {
        char buf[READ_BUFFER_SIZE];
        unsigned int msg_size = file_size(fd);
        send_header(client_d, req_data, msg_size);
        ssize_t size;
        while ((size = read(fd, &buf, READ_BUFFER_SIZE)) != 0)
            send(client_d, buf, size, 0);
        close(fd);
    }
    else
    {

    }
}

int create_socket(const char *apstrPort)
{

  struct addrinfo hints;
  struct addrinfo *servinfo;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE;

  int r = getaddrinfo(NULL, apstrPort, &hints, &servinfo);
  if( r != 0)
  {
    fprintf(stderr, "error getaddrinfo()\n");
    return -1;
  }
  int sock = sort_addr(servinfo);
  if (sock == -1)
  {
     fprintf(stderr, "error setsockopt\n");
     return -2;
  }
  if (sock == -2)
  {
     fprintf(stderr, "failed to find address\n");
     return -3;
  }
  freeaddrinfo(servinfo);


  if(listen(sock, MAX_CONNECTION) == -1)
  {
    fprintf(stderr, "error listen\n");
    return -4;
  }


  return sock;
}


int sort_addr(struct addrinfo *servinfo)
{
    struct addrinfo *p;
    int sock = 0;
    int yes;
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
      sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
      if(sock == -1)
        continue;

      if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
      {
        close(sock);
        freeaddrinfo(servinfo);
        return -1;
      }

      if(bind(sock, p->ai_addr, p->ai_addrlen) == -1)
      {
        close(sock);
        continue;
      }
      break;
    }
    freeaddrinfo(servinfo);
    if(p == NULL)
      return -2;
    return sock;
}
