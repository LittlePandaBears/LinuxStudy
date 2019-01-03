#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>
#include <stdlib.h>

int init_daemon(void){
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid_t pid;

    pid = fork();
    if(pid > 0){
        exit(0);
    }
    else if(pid < 0){
        return -1;
    }
    setsid();  //建立一个新的进程组，在这个新的进程组中，子进程成为这个进程的首进程，以使该进程脱离所有终端
    /*再次新建一个子进程，退出父进程，保证该进程不是进程组长，同事让该进程不能再次打开一个新的终端*/
    pid = fork();
    if(pid > 0){
        exit(0);
    }
    else if(pid < 0){
        return -1;
    }
    /*关闭所有从父进程继承下来的文件描述符*/
    for(int i = 0; i < NOFILE; i++){
        close(i);
    }
    /*改变工作目录，使得进程不与任何文件系统联系*/
    chdir("/");
    /*将文件屏蔽字设置成0*/
    umask(0);
    /*忽略SIGCHLD信号*/
    signal(SIGCHLD, SIG_IGN);

    return 0;
}

int main(void){
    time_t now;
    init_daemon();
    syslog(LOG_USER|LOG_INFO,"测试守护进程!\n");
    while(1){
        sleep(8);
        time(&now);
        syslog(LOG_USER|LOG_INFO, "系统时间 ：\t%s\t\t\n", ctime(&now));
    }
    return 0;
}