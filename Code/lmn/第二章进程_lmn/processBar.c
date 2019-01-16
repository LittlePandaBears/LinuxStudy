#include <stdio.h>
#include <unistd.h>

void processBar(){
    int rate = 0;
    char bar[100];
    bar[0] = '\0';
    while(rate < 100){
        printf("[%-100s]\r", bar);
        fflush(stdout);
        bar[rate] = '#';
        bar[++rate] = '\0';
        usleep(100000);
    }
}

int main(){
    processBar();
    return 0;
}