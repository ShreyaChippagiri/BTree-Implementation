#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static pid_t fork_ok(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "Fork failure in pid %d\n", (int)getpid());
        exit(1);
    }
    return pid;
}

static void new_level(int level, int n)
{
    if (level > n)
        return;
    if (fork_ok() == 0 || fork_ok() == 0)
        new_level(level+1,n);
    else
    {
        printf("i am %d, my parent is %d\n",
                (int)getpid(), (int)getppid());
        while (wait(0) > 0)
        ;
        printf("Exit %d\n", (int)getpid());
    

}
}

int main(void)
{
    printf("Start %d\n", (int)getpid());
    fflush(0);
    new_level(0,2);
    return(0);
}
