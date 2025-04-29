#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    char *Nombre_Pipe = "pipe.txt";
    
	int	pid, n;
	char    buff[100];

        int state = mknod(Nombre_Pipe, 0666 | S_IFIFO, (dev_t)0);
        if(state < 0)
            perror("Crear Pipe Error");

        int fd = open(Nombre_Pipe, O_RDWR);
        if(fd < 0)
            perror("Open Pipe Error");

        pid = fork();
        if(pid == 0)
        {
            // Hijo
            if((n=read(fd, buff, sizeof(buff))) <=0) //Leo desde el pipe
            {
                perror("read error");
            }
            printf("Mensaje: %s", buff);   
        }
        else
        {
                // Padre
            if(write(fd, "Hola", 5) != 5) // Escribo el pipe
                perror("write error");
        }
        
  	close(fd);
        
	return -1;
}