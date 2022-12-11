#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 128
// global file descriptor for input and output

int fd_in = -1;
int fd_out = -1;

// global buffer for input and output

char buffer_in[BUFFER_SIZE];
char buffer_out[BUFFER_SIZE];

// global buffer position for input and output

int buffer_in_pos = 0;
int buffer_out_pos = 0;

// declare a global file name for input and output

char fname_in[256];
char fname_out[256];

// the buf_in function reads 16 bytes from the input file and stores them in the buffer_in array and returns each byte one by one

char buf_in()
{
    if (buffer_in_pos == 0)
    {
        read(fd_in, buffer_in, BUFFER_SIZE);
    }
    char c = buffer_in[buffer_in_pos];
    buffer_in_pos = (buffer_in_pos + 1) % BUFFER_SIZE;
    return c;
}

// the buf_out function stores the data in the buffer_out array and writes the array to the output file when the array is full

void buf_out(char data)
{
    buffer_out[buffer_out_pos] = data;
    buffer_out_pos++;
    if (buffer_out_pos == BUFFER_SIZE)
    {
        write(fd_out, buffer_out, BUFFER_SIZE);
        for (int i = 0; i < sizeof(buffer_in); i++)
        {
            buffer_in[i] = '\0';
        }
        buffer_out_pos = 0;
    }
}

// the buf_flush function writes the remaining data in the buffer_out array to the output file

void buf_flush()
{
    write(fd_out, buffer_out, buffer_out_pos);
    buffer_out_pos = 0;
}

int main(int argc, char *argv[])
{
    // test for the buf_in function

    strcpy(fname_in, "test.txt");
    fd_in = open(fname_in, O_RDONLY);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%c", buf_in());
    }
    printf("\n");
    close(fd_in);

    // test for the buf_out function

    strcpy(fname_out, "test_out.txt");
    fd_out = open(fname_out, O_WRONLY | O_CREAT, 0644);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buf_out('a' + i);
    }
    buf_flush();
    close(fd_out);

    // copying and writing to a file using the buf_in and buf_out functions

    strcpy(fname_in, argv[1]);
    fd_in = open(fname_in, O_RDONLY);
    if (fd_in == -1)
    {
        printf("Error opening input file %s for reading \n", fname_in);
        exit(1);
    }
    strcpy(fname_out, argv[2]);
    fd_out = open(fname_out, O_WRONLY | O_CREAT, 0644);
    if (fd_out == -1)
    {
        printf("Error opening output file %s for writing \n", fname_out);
        exit(1);
    }
    while (1)
    {
        char c = buf_in();
        if (c == '\0')
        {
            break;
        }
        buf_out(c);
    }
    buf_flush();
    close(fd_in);
    close(fd_out);

    return 0;
}
