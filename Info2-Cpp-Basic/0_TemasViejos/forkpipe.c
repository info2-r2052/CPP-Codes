#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	int	pid, n;
	int     pipefd[2];
        char    buff[100];

 	if (pipe(pipefd) < 0)       // create a pipe
		perror("pipe error");

        pid = fork();
        if(pid == 0)
        {
            // Hijo
            if((n=read(pipefd[0], buff, sizeof(buff))) <=0) //Leo desde el pipe
            {
                perror("read error");
            }
            printf("Mensaje: %s", buff);   
        }
        else
        {
                // Padre
            sleep(10);
            
            if(write(pipefd[1], "Hola", 5) != 5) // Escribo el pipe
                perror("write error");
        }
        
  	close(pipefd[0]);
	close(pipefd[1]);
        
	return -1;
}