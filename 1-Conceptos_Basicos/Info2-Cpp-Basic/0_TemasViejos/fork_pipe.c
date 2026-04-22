#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
	int	pid;
	int     pipefd[2];
        char    buff[100];

 	if (pipe(pipefd) < 0)       // create a pipe
		perror("pipe error");

        pid = fork();
        if(0 == pid)
        {
            // Hijo
            if ((n=read(pipefd[0], buff, sizeof(buff))) <=0) //Leo desde el pipe
                            perror("read error");
            printf(“Mensaje: %s”, buff);   
        }
        else
        {
                // Padre
            if (write(pipefd[1], “Hola\n”, 5) != 5) // Escribo el pipe
                            perror("write error");
        }
        
  	close(pipefd[0]);
	close(pipefd[1]);
	exit(0);
}