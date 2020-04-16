#include "httpparser.h"






void parse_HTTP_message(char* request, struct  request_HTTP_data* req_data)
{
    if (request[0] == 'G' && request[1] == 'E' && request[2] == 'T' )
    {
        req_data->type = GET;
        URL_parse(request, req_data);

    }
    else if (request[0] == 'P' && request[1] == 'O' && request[2] == 'S' && request[3] == 'T')
    {
        req_data->type = POST;
        URL_parse(request, req_data);
        BODY_parse(request, req_data);
    }
    else
    {
        req_data->type = UNKNOWN;
        return;
    }
    extension_parse(req_data);
    if (strstr(request, "keep-alive") != NULL)
        req_data->keep_alive = 1;
    else
        req_data->keep_alive = 0;
}


void URL_parse(char* request, struct  request_HTTP_data* req_data)
{
    int start = str_search_symbol(request, '/') + 1;
    int end = str_index_symbol_search(request, ' ', (unsigned int)start);
    if (end == start)
        req_data->file_name = "index.html";
    else
    {
        char *url_data = copy_str_range(request, (unsigned int)start,(unsigned int) end - 1);
        char* body = strstr(url_data, "?");
        if (body == NULL)
        {
            req_data->file_name = url_data;
            if (req_data->type == GET)
                req_data->body = NULL;
        }
        else
        {
            long index = body - url_data;
            req_data->file_name = (char*)malloc((unsigned long)(index + 1) * sizeof (char)); // все что до '?'
            req_data->file_name = copy_str_range(url_data, 0, (unsigned int)index);
            req_data->file_name[index] = '\0';
            req_data->body = body + 1; // все что после '?'
            free(url_data);
        }
    }
}



void BODY_parse(char* request, struct  request_HTTP_data* req_data)
{
    char* body_size_symbol = strstr(request, "Content-Length:");
    if (body_size_symbol == NULL)
       req_data->body = NULL;
    else
    {
        long start = body_size_symbol - request + (long)strlen("Content-Length:");
        long end = start;
        char nums[5];
        int count = 0;
        for (; request[end] != '\n'; count++ && end++)
            nums[count] = request[end];
        nums[count] = '\0';
        int body_len = atoi(nums);
        req_data->body =(char*) malloc((unsigned int)(body_len+1) * sizeof (char));
        unsigned long reqsize = strlen(request);
        unsigned long j = reqsize - (unsigned int)body_len - 1;
        for (int i = 0; i < body_len; i++)
        {
            req_data->body[i] = request[j];
            j++;
        }
        req_data->body[body_len] = '\0';
      }
}



void extension_parse(struct  request_HTTP_data* req_data)
{
    char* ext = strstr(req_data->file_name, ".");
    if (ext == NULL)
    {
        req_data->file_extension = NULL;
        return;
    }
    unsigned int size = (unsigned int)strlen(ext);
    req_data->file_extension = (char*)malloc(size * sizeof(char));
    strcpy(req_data->file_extension, ext + 1);
}
