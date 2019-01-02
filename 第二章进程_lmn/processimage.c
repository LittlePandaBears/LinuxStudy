#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[], char **environ){
    printf("I am a process image\n");
    printf("My pid = %d, parentPid = %d\n", getpid(), getppid());
    printf("uid = %d, gid = %d\n", getuid(), getgid());

    for(int i = 0; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}