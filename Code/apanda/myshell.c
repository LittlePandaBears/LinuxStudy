#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

#define    normal          0
#define    out_redirect    1
#define    in_redirect     2
#define    have_pipe       3

/*获取用户输入*/
void get_input(char *buf) {
  int i;
  char c;

  c = getchar();
  for(i = 0; (i < 256) && (c != '\n'); i++) {   //当buf数组长度超出256, 或输入回车时, 跳出循环
    buf[i] = c;
    c = getchar();
  }

  if(i == 256)          //输入命令过长, 退出程序
    exit(-1);
  
  buf[i] = '\n';
  buf[++i] = '\0';      //buf数组以'\0'结束
}

/*解析用户输入*/
void explain_input(char *buf, int *argcount, char arglist[100][256]) {
  int number, i;
  *argcount = 0;

  if(strncmp(buf, "./", 2) == 0) {           //可以shell里运行程序
    buf += 2;
  }
  
  while(1) {
    number = 0;
    
    if(buf[0] == '\n')
      break;
    while(buf[0] == ' ') {
      buf++;
    }
    
    while( (buf[0] != ' ') && (buf[0] != '\n') ) {
      arglist[*argcount][number++] = buf[0];
      buf++;
    }
    arglist[*argcount][number] = '\0';    //每个参数都以 '\0' 结束
    *argcount += 1;
  }
  
  arglist[*argcount][0] = '\0';
}

/*查找命令*/
int find_command(char *command) {
  DIR             *dp;
  struct dirent   *dir;
  char            *path[] = {"./", "/bin", "/usr/bin", NULL};

  for(int i = 0; path[i] != NULL; i++) {           //依次打开上述目录, 进行查找
    if( (dp = opendir(path[i])) == NULL ) {
      printf("opendir(%s) failed!\n", path[i]);
      return 0;            //打开目录失败, 返回0
    }
    while( (dir = readdir(dp)) != NULL) {
      if(strcmp(dir->d_name, command) == 0) {
	closedir(dp);      //关闭目录流
	return 1;          //查找成功, 返回1
      }
    }
    closedir(dp);
  }
  return 0;                //遍历上述目录未果, 返回0
}

/*执行命令*/
void do_cmd(int argcount, char arglist[100][256]) {
  int flag = 0;                          //检查 '>' '<' '|' 个数,位置是否合法; 若flag 大于1, 则不合法 
  int how = normal;                      //标记 '>' '<' '|' 其中一个; 默认是普通命令, 不含重定向符和管道符
  int background = 0;                    //标记管道符
  int status;
  int fd;
  int i, j;
  char *arg[argcount+1];                 //申请指针数组用于指向每一个参数, 最后一个指针空间存放NULL, 用于控制循环
  char *argnext[argcount+1];             //用于指向管道后面的可执行命令
  char *file;                            //指向重定向的文件路径
  pid_t pid;
  
  for(i = 0; i < argcount; i++) {        //将命令取出
    arg[i] = (char*)arglist[i];          //字符数组强制转换成字符型指针
  }
  arg[i] = NULL;                         //置空, 控制循环
  
  for(i = 0; i < argcount; i++) {
    if(strcmp(arg[i], "&") == 0) {
      if(i == argcount-1) {              //如果有后台运行符 '&' 则一定是最后一个参数, 否则不合法
	background = 1;
	arg[argcount-1] == NULL;         //将指向 '&' 的指针置为空
	printf("found\n");
	break;
      }
      else {
	printf("wrong command!\n");
	return;
      }
    }
  }

  for(i = 0; arg[i] != NULL; i++) {
    if(strcmp(arg[i], ">") == 0) {         //参数中如果有输出重定向, 则flag加1
      flag++;
      how = out_redirect;
      if(arg[i+1] == NULL)                 //输出重定向符不能位于最后, 否则该命令不合法, flag加1
	flag++;
    }

    else if(strcmp(arg[i], "<") == 0) {    //参数中如果有输入重定向, 则flag加1
      flag++;
      how = in_redirect;
      if(i == 0)                           //输入重定向符不能位于最前, 否则该命令不合法, flag加1
	flag++;
    }

    else if(strcmp(arg[i], "|") == 0) {    //参数中如果有管道符号, 则flag加1
      flag++;
      how = have_pipe;
      if((arg[i+1] == NULL) || (i == 0))   //管道符号不能位于最前也不能位于最后, 否则该命令不合法, flag加1
	flag++;
    }

    if(flag > 1) {                         //flag大于1, 说明命令中含有多个> < | 符号, 本程序不支持; 或者是上述符号使用不合法
      printf("wrong command!\n");
      return;
    }
  }

  if(how == out_redirect) {
    for(i = 0; arg[i] != NULL; i++) {
      if(strcmp(arg[i], ">") == 0) {        
	file = arg[i+1];                   //输出重定向后面是文件名和路径, 用 指针file 指向该路径
	arg[i] = NULL;                     //将存放 '>' 的位置 置为空
      }
    }
  }

  if(how == in_redirect) {
    for(i = 0; arg[i] != NULL; i++) {        
      if(strcmp(arg[i], "<") == 0) {
	file = arg[i+1];                   //输入重定向后面是文件名和路径, 用 指针file 指向该路径
	arg[i] = NULL;                     //将存放 '<' 的位置 置为空
      }
    }
  }

  if(how == have_pipe) {
    for(i = 0; arg[i] != NULL; i++) {
      if(strcmp(arg[i], "|") == 0) {
	arg[i] = NULL;                        //将管道符位置 置为空
	for(j = i+1; arg[j] != NULL; j++) {   //管道符后面是可执行的命令, 用 argnext指针数组 指向它们
	  argnext[j-i-1] = arg[j];
	}
	argnext[j] = arg[j];                  //将argnext[j] 置为空, 便于控制循环
	break;
      }
    }
  }
  
  if( (pid = fork()) < 0) {                   //创建子进程, 在子进程中执行输入的命令
    printf("fork error\n");
    return;
  }

  switch(how) {
  case 0:                                    //普通命令, 不含 '>' '<' '|' 符号
    if(pid == 0) {
      if(find_command(arg[0]) == 0) {
	printf("%s : command not found\n", arg[0]);
	exit(0);
      }
      execvp(arg[0], arg);
      exit(0);
    }
    break;

  case 1:
    if(pid == 0) {
      if(find_command(arg[0]) == 0) {
	printf("%s : command not found\n", arg[0]);
	exit(0);
      }
      if((fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0) {
	printf("%s : open failed!\n", file);
	exit(0);
      }
      dup2(fd, 1);
      execvp(arg[0], arg);
      exit(0);
    }
    break;
    
  case 2:
    if(pid == 0) {
      if(find_command(arg[0]) == 0) {
	printf("%s : command not found\n", arg[0]);
	exit(0);
      }
      if((fd = open(file, O_RDONLY)) < 0) {
	printf("%s : open failed!\n", file);
	exit(0);
      }
      dup2(fd, 0);
      execvp(arg[0], arg);
      exit(0);
    }
    break;
    
  case 3:
    if(pid == 0) {
      int pid2;
      int status2;
      int fd2;

      if( (pid2 = fork()) < 0 ) {
	printf("fork2 error\n");
	return;
      }
      
      if(pid2 == 0) {
	if(find_command(arg[0]) == 0) {
	  printf("%s : command not found\n", arg[0]);
	  exit(0);
	}
	fd2 = open("/tmp/onefile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd2, 1);
	execvp(arg[0], arg);
	exit(0);
      }

      if(waitpid(pid2, &status2, 0) == -1)
	printf("wait for child process error\n");
      
      if(find_command(argnext[0]) == 0) {
	printf("%s : command not found\n", argnext[0]);
	exit(0);
      }

      fd2 = open("/tmp/onefile", O_RDONLY);
      dup2(fd2, 0);
      execvp(argnext[0], argnext);

      if(remove("/tmp/onefile"))
	printf("remove error\n");
      exit(0);
    }
    break;
    
  default:
    break;
  }

  if(background == 1) {                    //若命令中有后台运行符, 父进程直接返回, 不等待子进程结束
    printf("[process id %d]\n", pid);
    return;
  }
  if(waitpid(pid, &status, 0) == -1) {     //若没有, 则父进程等待子进程结束
    printf("wait for child process error\n");
  }
}

/*打印myshell符号*/
void print_myshell() {
  printf("MYSHELL@apandar$$:");
}

/*主函数*/
void main() {
  int argcount = 0;
  char arglist[100][256];
  char buf[256];

  while(1) {
    for(int i = 0; i < 256; i++) {         //初始化 buf数组
      buf[i] = '\0';
    }
    
    print_myshell();                       //打印 'MYSHELL$$' 符号
    get_input(buf);                        //获取用户输入
    
    if( (strcmp(buf, "exit\n") == 0) || (strcmp(buf, "logout\n") == 0) || (strcmp(buf, "quit\n") == 0))
      exit(0);                             //若用户输入 exit 或 quit 或 logout, 则退出shell
    
    explain_input(buf, &argcount, arglist);//解析用户输入命令, 存放在 arglist数组 中
    do_cmd(argcount, arglist);             //执行命令   
  }  
}
