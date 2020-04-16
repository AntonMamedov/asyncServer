
#include "core.h"
#include "httpparser.h"
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv2/imgcodecs.hpp>
#include <signal.h>
#include <thread>
#include <sys/epoll.h>
#include <errno.h>


using namespace std;

int main()
{
    int server_d = create_socket("8000"); // создаю сервер

    int epfd = epoll_create(100);
    fcntl(server_d, F_SETFL, O_NONBLOCK);
    epoll_event serv_ev;
    epoll_event events[100];
    serv_ev.events = EPOLLIN;
    serv_ev.data.fd = server_d;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_d, &serv_ev) < 0)
    {
     perror("Epoll fd add");
     return -1;
    }

     printf("HTTP server created!\n");
     while(1)
     {
         int size = epoll_wait(epfd, events, 100, -1);
         for (int i = 0; i < size; i++)
         {
             if (events[i].data.fd == server_d)
             {
                 int client_d =  create_client(server_d);
                 fcntl(server_d, F_SETFL, O_NONBLOCK);
                 epoll_event client_ev;
                 client_ev.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
                 client_ev.data.fd = client_d;
                 epoll_ctl(epfd, EPOLL_CTL_ADD, client_d, &client_ev);
             }
             else
             {
                 int client_d = events[i].data.fd;
                 char* request = get_request(client_d);
                 printf("%s \n", request);
                 struct request_HTTP_data current;
                 parse_HTTP_message(request, &current);
                 free(request);
                 request_processing_http(client_d, &current);
                 free_request_data(&current);
                 close(client_d);
             }
         }

     }

     return 0;
 }

