#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define PARAM_NONE       0                          //无参
#define PARAM_A          1                          //-a
#define PARAM_L          2                          //-l
#define PARAM_R          4                          //-R
#define LINE_MAX_LEN     150                        //每行能显示的最大长度
#define STANDARD_LEN     256                        //一个目录下能存放的文件或目录总数,或文件名的最大字符数

typedef struct QueueNode{
  char string[256];
  struct QueueNode *next;
}Node;

typedef struct LinkQueue{
  Node *front;
  Node *rear;
}Link;

int maxLen;                                         //最长目录名的长度  (全局变量)
int lenLeft;                                        //每行剩余可显示长度  (全局变量)
Link *Q;                                            //队列头尾指针 (全局变量)
char buf_string[256];                               //储存出队元素 (全局变量)

/*错误定位函数*/
void my_err(char *err_string, int line){
  printf("line %d:\n", line);
  perror(err_string);
  exit(1);
}

/*字符串进队*/
void InQueue(Link *Q, char inString[256]){
  Node *s = (Node*)malloc(sizeof(Node));
  if(s == NULL)
    my_err("Node malloc", __LINE__);
  strcpy(s->string, inString);
  Q->rear->next = s;
  Q->rear = s;
  s->next = NULL;
}

/*字符串出队*/
void OutQueue(Link *Q, char buf_string[256]){
  if(Q->front == Q->rear)
    return;
  Node *p =(Node*)malloc(sizeof(Node));
  if(p == NULL)
    my_err("Node malloc", __LINE__);
  p = Q->front->next;
  Q->front->next = p->next;
  if(p == Q->rear)
    Q->rear = Q->front;
  strcpy(buf_string, p->string);
  free(p);
}

/*判断队空*/
int IsEmpty(Link *Q){
  if(Q->front == Q->rear)
    return 1;
  else
    return 0;
}

/*建立队列并初始化*/   
Link* EstQueue(Link *Q){
  Q = (Link*)malloc(sizeof(Link));
  if(Q == NULL)
    my_err("Link malloc", __LINE__);
  Q->front = (Node*)malloc(sizeof(Node));
  if(Q->front == NULL)
    my_err("Node malloc", __LINE__);
  Q->rear = Q->front;
  Q->front->next = NULL;
  return Q;
}

/*判断是否是目录*/
int IsDir(char pathName[256]){
  struct stat buf;
  if(lstat(pathName, &buf) < 0)
    my_err("lstat", __LINE__);
  if(S_ISDIR(buf.st_mode)){
    return 1;
  }
  else
    return 0;
}

/*无参数 -l 时,以简单格式对齐输出传入的名称 (每次输出一个文件名或目录名) */
void param_NO_L_single_print(char fileName[STANDARD_LEN]){
  int lenGap;                                      //普通目录名与最长目录名之间的长度差,即文件名左对齐后,右补的空格数
  int i;
  
  if((maxLen+2) > lenLeft){                        //如果将要输出的文件名加上空格数的长度大于行剩余显示长度,则换行,并初始化lenLeft
    printf("\n");
    lenLeft = LINE_MAX_LEN;
  }
  printf("%-s",fileName);                          //左对齐输出
  lenGap = maxLen - strlen(fileName);
  for(i = 0; i < lenGap; i++)                      //右补空格
    printf(" ");
  printf("  ");                                    //每行的文件名之间空两格
  lenLeft = lenLeft - (maxLen + 2);                //更新行剩余显示长度
}

/*有参数 -l 时,以长格式输出 (每次输出一个文件名或目录名) (该输出方式需要传入属性) */
void param_L_single_print(char fileName[256], struct stat buf){
  char buf_time[64];                               //储存最后一次修改的时间
  struct passwd *pwd;                              //从该结构体中获取文件使用者的用户名
  struct group *grp;                               //从该结构体中获取文件使用者的所属组的组名
  /*打印文件类型*/
  if(S_ISLNK(buf.st_mode))
    printf("l");
  else if(S_ISREG(buf.st_mode))
    printf("-");
  else if(S_ISDIR(buf.st_mode))
    printf("d");
  else if(S_ISCHR(buf.st_mode))
    printf("c");
  else if(S_ISBLK(buf.st_mode))
    printf("b");
  else if(S_ISFIFO(buf.st_mode))
    printf("f");
  else if(S_ISSOCK(buf.st_mode))
    printf("s");
  
  /*打印文件所有者对文件的操作权限*/
  if(buf.st_mode & S_IRUSR)
    printf("r");
  else
    printf("-");
  if(buf.st_mode & S_IWUSR)
    printf("w");
  else
    printf("-");
  if(buf.st_mode & S_IXUSR)
    printf("x");
  else
    printf("-");
  
  /*打印与文件所有者同组的用户对文件的操作权限*/
  if(buf.st_mode & S_IRGRP)
    printf("r");
  else
    printf("-");
  if(buf.st_mode & S_IWGRP)
    printf("w");
  else
    printf("-");
  if(buf.st_mode & S_IXGRP)
    printf("x");
  else
    printf("-");
  
  /*打印其他用户对文件的操作权限*/
  if(buf.st_mode & S_IROTH)
    printf("r");
  else
    printf("-");
  if(buf.st_mode & S_IWOTH)
    printf("w");
  else
    printf("-");
  if(buf.st_mode & S_IXOTH)
    printf("x");
  else
    printf("-");

  printf(" ");                               //打印完权限后空一格

  /***********/
  printf("%-4d ", buf.st_nlink);             //打印文件链接数
  pwd = getpwuid(buf.st_uid);                
  grp = getgrgid(buf.st_gid);
  printf("%-8s ", pwd->pw_name);             //打印用户名
  printf("%-8s ", grp->gr_name);             //打印用户组名
  printf("%-8d ", buf.st_size);              //打印文件大小
  /*打印最后一次修改文件的时间*/
  strncpy(buf_time, ctime(&buf.st_mtime), strlen(ctime(&buf.st_mtime))-1);        //去掉换行符
  printf("%-25s  ",buf_time);
  printf("%-s\n", fileName);                                                      // 输出文件或目录名
}

/*根据指定参数, 调用函数输出 (每次输出一个文件名) ,该函数会从传入的路径名中获取文件属性和文件名,并匹配相应的输出方式 */
void param_single_print(int param, char pathName[256]){
  //注意：传入的文件或目录的路径名, 不以'/'结尾
  char fileName[256];                       //储存文件名或目录名
  int i, j = 0;
  struct stat buf;                          //储存获取的文件属性
  /*根据传入的文件路径获取文件属性*/
  if(lstat(pathName, &buf) < 0){
    my_err("lstat", __LINE__);
  }
  /*从路径中获取文件名*/
  for(i = 0; i < strlen(pathName); i++){
    if(pathName[i] == '/'){
      j = 0;
      continue;
    }
    fileName[j++] = pathName[i];
  }
  fileName[j] = '\0';
  /*匹配参数,决定输出文件名的方式*/
  switch (param) {             
  case PARAM_NONE:                           //无参
    if(fileName[0] != '.')
      param_NO_L_single_print(fileName);
    break;

  case PARAM_R:
    if(fileName[0] != '.')
      param_NO_L_single_print(fileName);
    break;
    
  case PARAM_A:                             //输出所有文件,包括隐藏文件
    param_NO_L_single_print(fileName);
    break;

  case (PARAM_A+PARAM_R):                   //输出所有文件,包括隐藏文件
    param_NO_L_single_print(fileName);
    break;

  case PARAM_L:                             //以长格式输出文件,不包含隐藏文件
    if(fileName[0] != '.')
      param_L_single_print(fileName, buf);
    break;

  case (PARAM_L+PARAM_R):                   //以长格式输出文件,不包含隐藏文件
    if(fileName[0] != '.')
      param_L_single_print(fileName, buf);
    break;
    
  case (PARAM_A+PARAM_L):
    param_L_single_print(fileName, buf);
    break;

  case (PARAM_A+PARAM_L+PARAM_R):
    param_L_single_print(fileName, buf);
    break;

  default:
    break;
  } 
}

/*根据指定格式,输出指定目录下的文件或目录 (一个或多个) */
void param_print_dir(int param, char pathName[256]){
  
  //注意：这里的pathName已经是'/'结尾了
  
  DIR *dir;
  struct dirent *ptr;
  char pathNames[5000][STANDARD_LEN];         //用于储存指定目录下文件或目录的路径
  char temp[256];
  int count = 0, i, j;
  maxLen = 0;                                         //获取目录下最长文件名前,先初始化
  if((dir = opendir(pathName)) == NULL)
    my_err("opendir", __LINE__);
  while((ptr = readdir(dir)) != NULL){
    strcpy(pathNames[count], pathName);
    strcat(pathNames[count], ptr->d_name);            //获取该目录下的文件和目录的路径,不以'/'结尾 (即在文件名或目录名前添加之前的路径)
    if(strlen(ptr->d_name) > maxLen)
      maxLen = strlen(ptr->d_name);                   //获取该目录下,最长文件名长度
    if((strcmp(ptr->d_name, "..") != 0) && (strcmp(ptr->d_name, ".") !=0)){
      if( (param & PARAM_R) && IsDir(pathNames[count]) ){
	strcpy(temp, pathNames[count]);
	strcat(temp, "/");
	InQueue(Q, temp);
      }
    }
    count++;
  }
  /*选择法对文件名排序*/
  for(i = 0; i < count; i++){
    for(j = i+1; j < count; j++){
      if(strcmp(pathNames[i], pathNames[j]) > 0){
	strcpy(temp, pathNames[i]);
	strcpy(pathNames[i], pathNames[j]);
	strcpy(pathNames[j], temp);
      }
    }
  }
  lenLeft = LINE_MAX_LEN;                            //输出之前对lenLeft初始化
  for(i = 0; i < count; i++)
    param_single_print(param, pathNames[i]);         //依次传路径
  if(!(param & PARAM_L))                             //用于换行
    printf("\n");
}

void main(int argc, char **argv){

  int param = PARAM_NONE;                            //设定参数种类
  char pathName[256];                                //路径名
  char buf_param[32];                                //保存从命令行读取的参数
  int count = 0;                                     //记录'-'的个数
  struct stat buf;                                   //存放从命令行获取的文件或目录的属性
  int i, j, k;
  for(i = 1; i < argc; i++){
    if(argv[i][0] == '-' ){
      for(j = 1, k = 0; j < strlen(argv[i]); j++, k++)
	buf_param[k] = argv[i][j];
      count++;
    }
  }
  /*根据读取到的参数设定参数param的值*/
  for(i = 0; i < k; i++){
    if(buf_param[i] == 'a')
      param |= PARAM_A;
    else if(buf_param[i] == 'l')
      param |= PARAM_L;
    else if(buf_param[i] == 'R')
      param |= PARAM_R;
    else
      printf("Ivalid Param!\n");
  }
  
  /*若没有目标文件或目录就显示当前目录*/
  if(count == argc-1){
    strcpy(pathName, "./");
    if(param & PARAM_R){
      Q = EstQueue(Q);                                        //建队
      InQueue(Q, pathName);
      while(!IsEmpty(Q)){
	OutQueue(Q, buf_string);
	printf("%s:\n", buf_string);
	param_print_dir(param, buf_string);
	printf("\n");
	if(strcmp(buf_string, pathName) == 0){
	  for(i = 0; i < 150; i++)
	    printf("-");
	  printf("\n\n");
	}
      }
      return;
    }
    param_print_dir(param, pathName);
  }
  else{
    for(i = 1; i < argc; i++){
      if(argv[i][0] != '-'){
	strcpy(pathName, argv[i]);                                   //获取目标文件前或目录的路径
	if(stat(pathName, &buf) < 0)                                 //由路径获取属性
	  my_err("stat", __LINE__);
	if(S_ISDIR(buf.st_mode)){                                    //通过属性判断是文件还是目录
	  if(pathName[strlen(pathName)-1] != '/')                
	    strcat(pathName, "/");                                   //如果是目录的路径,则确保目录的路径是'/'结尾;
	  if(param & PARAM_R){
	     Q = EstQueue(Q);                                        //建队
	     InQueue(Q, pathName);
	     while(!IsEmpty(Q)){
	       OutQueue(Q, buf_string);
	       printf("%s:\n", buf_string);
	       param_print_dir(param, buf_string);
	       printf("\n");
	       if(strcmp(buf_string, pathName) == 0){
		 for(i = 0; i < 150; i++)
		   printf("-");
		 printf("\n\n");
	       }
	     }
	     return;
	   }
	   param_print_dir(param, pathName);
	}
	else{
	  param_single_print(param, pathName);
	  printf("\n");
	}
      }
    }
  }
}
