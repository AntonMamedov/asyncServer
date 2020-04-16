#include "secondaryfunctions.h"


#include <fcntl.h>
#include <unistd.h>



int str_search_symbol(const char *str, const char symbol) // поиск символа в строке
{
    unsigned int count = 0;
    unsigned long size = strlen(str);
    while (str[count] != symbol && count < size )
        count++;
    if (count != size)
        return (int)count;
    return -1;
}


int str_index_symbol_search(const char *str,const char symbol, const unsigned int index) // поиск символа начиная с конкретного индекса
{
    unsigned int count = index;
    unsigned long size = strlen(str);
    while (str[count] != symbol && count < size )
        count++;
    if (count != size)
        return (int)count;
    return -1;
}


char* copy_str_range(char *str, unsigned int start, unsigned int end)
{
    int size = (int)(end - start + 1);
    if (size < 0)
        return NULL;
    else
    {
        char *receiving_ctr = (char*)malloc((unsigned int)(size + 1) * sizeof(char));
        for (int i =0; i < size; i++)
        {
            receiving_ctr[i] = str[start];
            start++;
        }
        receiving_ctr[size] = '\0';
        return receiving_ctr;
    }
}



char* concat(char *s1, char *s2) {

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = (char*)malloc(len1 + len2 + 1);

    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);

    return result;
}


unsigned int file_size(int fd)
{
    struct stat st;
    fstat(fd, &st);
    return (unsigned int)st.st_size;
}


void pcreate(char* com, int* fdin_, int* fdout_)
{
    pid_t pid;
    int pipe_in[2];
    int pipe_out[2];
    pipe(pipe_in);
    pipe(pipe_out);
    pid = fork();
    if (pid > 0)
    {
        close(pipe_in[0]);
        close(pipe_out[1]);
        *fdin_ = dup(pipe_in[1]);
        *fdout_ = dup(pipe_out[0]);
    }
    else if (pid == 0 )
    {
        close(pipe_in[1]);
        close(pipe_out[0]);
        dup2(pipe_in[0], 0);
        dup2(pipe_out[1], 1);

        int size = 2;
        int comlenght = (int)strlen(com);
        for (int i = 0; i < comlenght; i++)
        {
            if (com[i] == ' ')
                size++;
        }
        char* args[size];
        comparse(com, args, size);
        if (execvp(args[0], args) < 0)
            _exit(0);
    }
}



void comparse(char* com, char* args[], int comlenght)
{

    long del = 0;

    char *com1 = com;
    char *com2 = com1;
    for (int i = 0; i < comlenght - 1; i++)
    {
        com2 = strstr(com1, " ");
        if (com2 == NULL)
            del = (long)strlen(com1);
        else
            del = com2 - com1;
        args[i] =(char*) malloc((unsigned)(del+1) * sizeof (char));
        args[i][del] = '\0';
        strncpy(args[i], com1, (unsigned)del);
        com1 = com2 + 1;

    }
    args[comlenght - 1] = NULL;
}


void binary_representation(char* bits, char bit)
{
    for (ssize_t i = 0; i < 8; i++)
        bits[i] = '0';

    unsigned temp = bit & 0xFF;
    int count = 7;
    do
    {
        bits[count] = ('0' + (temp % 2));
        temp = temp / 2;
        count--;

    }while(temp > 0);
}
