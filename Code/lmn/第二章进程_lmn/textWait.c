#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int waitprocess();

int main(){
    waitprocess();

    return 0;
}

int waitprocess(){
    pid_t pid;
    int status;

    pid = fork();
    if(pid == -1){
        printf("Creation process failed\n");
        return -1;
    }
    else if(pid > 0){
        printf("Pareant process is running, wait Child process, pid = %d\n", getpid());
        wait(&status);
    }
    else{
        printf("Child process is running, pid = %d, ppid = %d\n", getpid(), getppid());
        exit(5);
    }

    printf("Child exit status is %d\n", WEXITSTATUS(status));
    printf("process end with from pid = %d\n", getpid());

    return 1;
}