#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    fprintf(stderr, "Start %d\n", (int)getpid());
    if (fork() < 0 || fork() < 0 || fork() < 0 || fork() < 0)
    {
        fprintf(stderr, "Fork failure in pid %d\n", (int)getpid());
        exit(1);
    }
    fprintf(stderr, "i am %d, my parent is %d\n",
            (int)getpid(), (int)getppid());
    while (wait(0) > 0)
        ;
    fprintf(stderr, "Exit %d\n", (int)getpid());
    return(0);
}
