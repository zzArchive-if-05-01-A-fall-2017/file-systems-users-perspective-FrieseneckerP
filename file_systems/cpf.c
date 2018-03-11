#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("destination / start file  is(are) missing!");
        return -1;
    }

    int file_desc_1 = open(argv[1],O_RDWR,S_IRUSR | S_IWUSR);
    int file_desc_2 = open(argv[2],O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);
    
    if(file_desc_1 < 0 || file_desc_2 < 0)
    {
        printf("ERROR\nTry again!");
        return -1;
    }

    int read_in = -1;
    char buffer[1];
    
    while(read_in != 0)
    {
        read_in = read(file_desc_1,buffer,1);
        write(file_desc_2,buffer,1);
    }

    close(file_desc_1);
    close(file_desc_2);
    
    return 0;
}
