#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ret;
    
    ret = fork();
    switch(ret)
    {
        case 0:
            // Hijo
            printf("HIJO");
            break;
        
        default:
            // Padre
            printf("PADRE");
            break;
    }
    
    return 0;
}

