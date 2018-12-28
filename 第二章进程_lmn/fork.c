#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(void){
    pid_t pid;
    printf("Process Creation Study\n");
    pid = fork();
    switch(pid){
        case 0 : 
            printf("Child process is running, Curpid is %d, Parentpid is %d\n", pid, getpid());
            break;
        case -1 : 
            printf("Process Creation failed\n");
            break;
        default :
            printf("Parent process is running, ChildPid is %d, Parentpid is %d\n", pid, getpid());        
            break;
    }
    return 0;
}