#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<wait.h>
#define BUFFSIZE 256

int main(int argc,char*argv[])
{
pid_t pid1,pid2,pid,k;
int fd1,n,i,s;
char buf[BUFFSIZE];
printf("This is the parent process!\n");
fd1=open(argv[1],O_RDONLY|O_CREAT);
//printf("The file opened for reading is:%d\n",fd1);
perror("Open");
pid=fork();
perror("Fork1");
//pid2=fork();
//perror();
//k=getpid();
//perror();
if(pid==0)
{
pid1=getpid();
printf("\nWe are now in the first child process..\n");
perror("\nGetpid");
printf("\nThe process id is:%d\n",pid1);
//do the ps command here
}

else
{
printf("\nWe are now in the parent process..\n");
printf("\nWaiting for child process 1 to terminate..\n");
pid1=waitpid(pid1,&s,WNOHANG);
perror("\nWaitpid");
if(WIFEXITED(s))
printf("\nThe exit status of the first child process:%d\n",WEXITSTATUS(s));
pid=fork();
perror("\nFork2");
if(pid==0)
{
//char buf[BUFFSIZE];
//int n,i;
pid2=getpid();
printf("\nWe are now in the second child process..\n");
perror("\nGetpid");
printf("\nThe process id is:%d\n",pid2);
n=read(fd1,buf,BUFFSIZE);
if(n==0)
printf("End of file was reached\n");
else if(n>0)
{
printf("\nThe no of bytes read from the file are:%d\n",n);
i=write(STDOUT_FILENO,buf,n);
perror("\nWrite");
}
else
{
printf("\nThe read was unsuccessful\n");
perror("\nRead");
}
}
printf("\nWe are now in the parent process..\n");
//printf("Waiting for child process 1 to terminate..\n");
//pid1=waitpid(pid1,&s,WNOHANG);
//perror("Waitpid");
//if(WIFEXITED(s))
//printf("The exit status of the first child process:%d",WEXITSTATUS(s));
printf("\nWaiting for child process 2 to terminate..\n");
pid2=waitpid(pid2,&s,WNOHANG);
perror("\nWaitpid");
if(WIFEXITED(s))
printf("\nThe exit status of the second child process:%d\n",WEXITSTATUS(s));
printf("\nReading from the file now..\n");
n=read(fd1,buf,BUFFSIZE);
if(n==0)
printf("\nEnd of file was reached\n");
else if(n>0)
{
printf("\nThe no of bytes read from the file are:%d\n",n);
i=write(STDOUT_FILENO,buf,n);
perror("\nWrite");
}
else
{
printf("\nThe read was unsuccessful\n");
perror("\nRead");
}
}
}





