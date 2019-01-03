#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    pid_t pid;
    char *msg;
    int k;
    printf("Process creation study\n");
    pid = fork();
    switch(pid){
        case 0 : 
            msg = "Parent process is running";
            k = 3;
            break;
        case -1 : 
            k = 0;
            perror("process creation failed\n");
            break;
        default : 
            msg = "Child process is running";
            k = 5;
            break;    
    }

    while(k > 0){
        printf("%s\n", msg);
        usleep(1000000); //以微秒为单位
        k--;
    }

    return 0;
}