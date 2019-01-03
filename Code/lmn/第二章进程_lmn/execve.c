#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

/*调用execve函数来执行新程序*/
int main(int argc, char *argv[], char **environ){
    pid_t pid;
    int status;
    printf("Exec example\n");
    pid = fork();
    if(pid == -1){
        printf("Process createde failed\n");
        exit(0);
    }
    else if(pid > 0){
        printf("Parent process is running, parentpid = %d\n", getpid());
        wait(&status);
    }
    else{
        printf("Child process is running, child pid = %d, ppid = %d\n", getpid(), getppid());
        printf("uid = %d, gid = %d\n", getuid(), getgid());
        execve("processimage", argv, environ);
        printf("Process never go there\n");
        exit(0);
    }

    printf("The status of Child is %d\n", WEXITSTATUS(status));
    printf("Process end from %d\n", getpid());
}