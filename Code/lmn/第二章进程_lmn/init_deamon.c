#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>

int init_deamon(void){
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid_t pid;

    pid = fork();
    if(pid > 0){
        exit(0);
    }
    else if (pid == -1){
        printf("Deamon error.\n");
        return -1;
    }
    //使得子进程成为会话组长，以脱离所有终端
    setsid();
    //创建一个子进程，结束父进程，保证该进程不是进程组长，从而不能打开终端
    pid = fork();
    if(pid > 0){
        exit(0);
    }
    else if(pid == -1){
        printf("Deamon error.\n");
        return -1;
    }
    //关闭父进程的所有文件描述符
    for(int i = 0; i < NOFILE; i++){
        close(i);
    }
    //将当前目录改为根目录
    chdir("/");
    //将文件屏蔽字设置为０
    umask(0);
    //忽略SIGCHLD信号
    signal(SIGCHLD, SIG_IGN);

    return 0;
}

int main(){
    time_t now;
    init_deamon();
    syslog(LOG_USER|LOG_INFO, "测试守护进程\n");
    while(1){
        sleep(8);
        time(&now);
        syslog(LOG_USER|LOG_INFO, "系统时间 ：\t%s\t\t\n", ctime(&now));
    }

    return 0;
}