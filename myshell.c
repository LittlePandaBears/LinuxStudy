#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define PARAMETER_NUM 100
#define ARGLEN 256
#define normal  0   //一般的命令
#define out_readirect   1   //输出重定向
#define in_readdirect 2     //输入重定向
#define have_pipe   3   //命令中有管道
/*函数的声明*/
void print_prompt();
void input_command(char *buf);
void explain_command(char *buf, int *argNum, char argList[][ARGLEN]);
void do_command(int argNum, char argList[][ARGLEN]);
int find_command(char *command);

int main(char argc, char *argv[])
{
    int argNum;
    char argList[PARAMETER_NUM][ARGLEN];
    char *buf = NULL;

    /*为储存命令的arg分配空间*/
    buf = (char *)malloc(sizeof(char) * ARGLEN);
    if (buf == NULL)
    {
        printf("malloc failed.\n");
        exit(1);
    }

    while (1)
    {
        /*清空argList和buf中的内容,把argNum置为０*/
        argNum = 0;
        memset(buf, '\0', sizeof(buf));
        for (int i = 0; i < PARAMETER_NUM; i++)
        {
            memset(argList[i], '\0', sizeof(argList[i]));
        }

        /*打印myshell的提示符*/
        print_prompt();
        /*输入命令*/
        input_command(buf);

        /*判断命令是否为exit或者为logout*/
        if (strcmp(buf, "exit\n") == 0 || strcmp(buf, "logout\n") == 0)
        {
            break;
        }

        /*分析命令*/
        explain_command(buf, &argNum, argList);
        /*执行命令*/
        do_command(argNum, argList);
    }

    /*释放内存，free(buf)*/
    if (buf != NULL)
    {
        free(buf);
        buf = NULL;
    }
    return 0;
}

void print_prompt()
{
    printf("MyShell$$: ");

    return;
}

void input_command(char *buf)
{
    char ch;
    int i;
    ch = getchar();
    for (i = 0; i < ARGLEN && ch != '\n'; i++)
    {
        buf[i] = ch;
        ch = getchar();
    }
    if (i == ARGLEN)
    {
        printf("Command is to long!\n");
        exit(1);
    }
    buf[i] = '\n';
    buf[++i] = '\0';

    return;
}

void explain_command(char *buf, int *argNum, char argList[][ARGLEN])
{
    int number = 0;
    char *p, *q;
    p = q = buf;
    while (1)
    {
        if (p[0] == '\n')
        {
            break;
        }
        else if (p[0] == ' ')
        {
            p++;
        }
        else
        {
            q = p;
            number = 0;
            while ((q[0] != ' ') && (q[0] != '\n'))
            {
                q++;
                number++;
            }
            strncpy(argList[*argNum], p, number + 1);
            argList[*argNum][number] = '\0';
            (*argNum)++;
            p = q;
        }
    }

    return;
}

/*"exec"函数要求第二参数要求以NULL结尾*/
void do_command(int argNum, char argList[][ARGLEN])
{
    int flag = 0;
    int how = normal;    //用于只是命令中是否含有> 、 < 、 |
    int background = 0;     //标识命令中是否有后台运行的标示符
    int status;
    int i;
    int fd;
    char *arg[argNum + 1];
    char *argnext[argNum + 1];
    pid_t pid;
    char *file;
    //将命令取出
    for(i = 0; i < argNum; i++)
    {
        arg[i] = argList[i];
    }
    arg[argNum] = NULL;

    //查看命令行是否有后台运行符
    for(i = 0; i < argNum; i++)
    {
        if(strncmp(arg[i], "&", 1) == 0)
        {
            if(i == argNum - 1)
            {
                background = 1;
                arg[argNum - 1] = NULL;
                break;
            }
            else
            {
                printf("wrong command\n");
                return ;
            }
        }
    }

    for(i = 0; arg[i] != NULL; i++)
    {
        if(strcmp(arg[i], ">") == 0)
        {
            flag++;
            how = out_readirect;
            if(arg[i + 1] == NULL)
            {
                flag++;
            }
        }
        if(strcmp(arg[i], "<") == 0)
        {
            flag++;
            how = in_readdirect;
            if(i == 0)
            {
                flag++;
            }
        }
        if(strcmp(arg[i], "|") == 0)
        {
            flag++;
            how = have_pipe;
            if(arg[i+1] == NULL)
            {
                flag++;
            }
            if(i == 0)
            {
                flag++;
            }
        }
    }
    //flag大于1,说明命令中含有多个> < |符号，本程序是不支持这样的命令的，或命令格式不对
    if(flag > 1)
    {
        printf("wrong command\n");
        return ;
    }

    if(how == out_readirect)
    {
        //命令只含有一个输出重定向符号
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], ">") == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }

    if(how == in_readdirect)
    {
        //命令只含有一个输入重定向
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], "<") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(how == have_pipe)
    {
        //命令只有一个管道符号，把管道符后面的部分存入argnext中，管道后面的部分是一个可执行的shell命令
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], "|") == 0)
            {
                arg[i] = NULL;
                int j;
                for(j = i + 1; arg[j] != NULL; j++)
                {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = arg[j];
                break;
            }
        }
    }


    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        return ;
    }

    switch(how)
    {
        case 0:
        //pid为0说明是子进程，在子进程中执行输入的命令
        //输入的命令中不含> < |
        if(pid == 0)
        {
            if(!(find_command(arg[0])))
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            execvp(arg[0], arg);
            exit(0);
        }
        break;

        case 1:
        //输入的命令中含有输出重定向符
        if(pid == 0)
        {
            if( !(find_command(arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
            dup2(fd, 1);
            execvp(arg[0], arg);
            exit(0);
        }
        break;

        case 2:
        //输入的命令中含有输入重定向<
        if(pid == 0)
        {
            if( !(find_command (arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDONLY);
            dup2(fd, 0);
            execvp(arg[0], arg);
            exit(0);
        }
        break;

        case 3:
        //输入的命令中含有管道符|
        if(pid == 0)
        {
            int pid2;
            int status2;
            int fd2;

            if( (pid2 = fork()) < 0 )
            {
                printf("fork2 error\n");
                return ;
            }
            else if(pid2 == 0)
            {
                if( !(find_command(arg[0])) )
                {
                    printf("%s : command not found\n", arg[0]);
                    exit(0);
                }
                fd2 = open("/tmp/youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC, 0644);
                dup2(fd2, 1);
                execvp(arg[0], arg);
                exit(0);
            }
            if(waitpid(pid2, &status2, 0) == -1)
            {
                printf("wait for child process error\n");
            }
            if( !(find_command(argnext[0])) )
            {
                printf("%s : command not found\n", argnext[0]);
                exit(0);
            }
            fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
            dup2(fd2, 0);
            execvp (argnext[0], argnext);

            if( remove("/tmp/youdonotknowfile") )
            {
                printf("remove error\n");
            }
            exit(0);
        }
        break;

        default:
        break;
    }

    //若命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if(background == 1)
    {
        printf("process id %d \n", pid);
        return ;
    }

    //父进程等待子进程结束
    if(waitpid(pid, &status, 0) == -1)
    {
        printf("wait for child process error\n");
    }

}
int find_command(char *command)
{
    DIR *dir;
    struct dirent *dirp;
    char *path[] = {"./", "/bin", "/usr/bin", NULL};

    /*是当前目录下的程序可执行*/
    if (strncmp(command, "./", 2) == 0)
    {
        command += 2;
    }
    /*在当前目录，/bin目录和/usr/bin目录查找要执行的程序*/
    for (int i = 0; path[i] != NULL; i++)
    {
        if ((dir = opendir(path[i])) == NULL)
        {
            perror("can not open /bin dir\n");
        }
        while ((dirp = readdir(dir)) != NULL)
        {
            if (strcmp(dirp->d_name, command) == 0)
            {
                //printf("%s in the dir: %s", command, path[i]);
                closedir(dir);
                return 1;
            }
        }
        closedir(dir);
    }

    return 0;
}