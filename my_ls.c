#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include "errno.h"

#define PATH_NUM 256
#define DIR_NUM 1000
#define PARAMETER_NUM 32

#define FALSE 0
#define TRUE !FALSE

typedef struct QNode{
    char path[PATH_NUM];
    struct QNode *next;
}QNode;

typedef struct{
    QNode* head;
    QNode* rear;
}Queue;


int haveI = FALSE, haveA = FALSE, haveR = FALSE; //参数i,a,R是否存在
char path1[DIR_NUM][PATH_NUM] = {'\0'};
char path2[DIR_NUM][PATH_NUM] = {'\0'};

void show(char pathname[PATH_NUM]);
void readFileList(char pathname[PATH_NUM], Queue* Q);
void printl(char pathname[PATH_NUM]);

void initQueue(Queue* Q);
int enterQueue(Queue* Q, char *p);
int deleteQueue(Queue* Q, char *p);


int main(int argc, char *argv[]){
    int i; 
    char path[PATH_NUM + 1] = {'\0'}; //ls的路径
    char parameter[PARAMETER_NUM]; //参数的数组
    struct stat buf;
    Queue Q;
    char tempPath[PATH_MAX];

    //初始化队列
    initQueue(&Q);

    //初始化数组
    memset(path, '\0', sizeof(char) * PATH_NUM);
    memset(parameter, '\0', sizeof(char) * PARAMETER_NUM);

    //获取参数l,a,R;
    for(i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            strcat(parameter, &argv[i][1]);
        }
    }


    //获取ls命令工作路径
    if(argc > 1 && argv[argc - 1][0] != '-'){
        strcpy(path, argv[argc - 1]);
    }else{
        strcpy(path, "./");
        path[2] = '\0';
    }

    //判断参数的合法性
    for(i = 0; parameter[i] != '\0'; i++){
        switch(parameter[i]){
            case 'a' : haveA = TRUE; break;
            case 'l' : haveI = TRUE; break;
            case 'R' : haveR = TRUE; break;
            default : printf("ls : invalid option.\n"); exit(1);
        }
    }

    //判断路径的合法性
    if(stat(path, &buf) == -1){
        perror("stat :");
        exit(1);
    }

    //读取子文件夹
    if(!haveR){
        show(path);

    }
    else{        //用队列实现
        enterQueue(&Q, path);

        while(Q.head != Q.rear){
            deleteQueue(&Q, tempPath);
            show(tempPath);
            readFileList(tempPath, &Q);
        }
        
    }
    return 0;
}


void show(char pathname[PATH_NUM]){    
    DIR *dir;
    struct dirent *ptr;
    int count = 0;
    char tempPath[PATH_MAX] = {'\0'};
    if ((dir = opendir(pathname)) == NULL)
    {
        perror("Open dir error.\n");
        exit(1);
    }
    printf("\n\n%s\n", pathname);  //输出当前目录

    //读取当前目录下的文件
    while ((ptr = readdir(dir)) != NULL){
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){
            if(!haveA){
                continue;
            }
        }

        if(!haveI){
            printf("%-15s  ",ptr->d_name);
            count++;
            if(count % 4 == 0){
            printf("\n");
            }
        }else{
            //子文件的路径
            memset(tempPath, '\0', sizeof(char) * PATH_MAX);
            strcpy(tempPath, pathname);
            strcat(tempPath, "/");
            strcat(tempPath, ptr->d_name);
            //长文档打印
            printl(tempPath);
            count++;
        }
        
    }

        closedir(dir);
        return;
    
}    


//读取文件夹 ls-R
void readFileList(char pathname[PATH_NUM], Queue* Q){
    DIR *dir;
    struct dirent *ptr;
    char tempPath[PATH_MAX];

    if ((dir=opendir(pathname)) == NULL)
    {
        perror("Open dir error.\n");
        exit(1);
    }
    //读取是目录的文件
    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){
            if(!haveA){
                continue;
            }   
        }
        if(ptr->d_type == 4){       //dir
            memset(tempPath, '\0', sizeof(char) * PATH_MAX);
            //子目录地址
            strcpy(tempPath, pathname);
            strcat(tempPath, "/");
            strcat(tempPath, ptr->d_name);
            enterQueue(Q, tempPath);
        }
    }
    
    closedir(dir);
    return;
}


//长文档输出一个文件
void printl(char pathname[PATH_NUM]){
    struct stat buf;
    struct passwd *getpsd;
    struct group *getgrp;

    if(stat(pathname, &buf) == -1){
        perror("stat :");
        exit(1);
    }

    //打印文件类型
    if(S_ISLNK(buf.st_mode)){
        printf("l");
    }else if(S_ISREG(buf.st_mode)){
        printf("-");
    }else if(S_ISDIR(buf.st_mode)){
        printf("d");
    }else if(S_ISCHR(buf.st_mode)){
        printf("c");
    }else if(S_ISBLK(buf.st_mode)){
        printf("b");
    }else if(S_ISSOCK(buf.st_mode)){
        printf("s");
    }else{
        printf(" ");
    }
    
    //打印文件所有者的权限
    if((unsigned long) buf.st_mode & S_IRUSR){
        printf("r");
    }else{
        printf("-");
    }
    if((unsigned long) buf.st_mode & S_IWUSR){
        printf("w");
    }else{
        printf("-");
    }
    if((unsigned long) buf.st_mode & S_IXUSR){
        printf("x");
    }else{
        printf("-");
    }
    
    //打印文件所在组的权限
    if((unsigned long) buf.st_mode & S_IRGRP){
        printf("r");
    }else{
        printf("-");
    }
    if((unsigned long) buf.st_mode & S_IWGRP){
        printf("w");
    }else{
        printf("-");
    }
    if((unsigned long) buf.st_mode & S_IXGRP){
        printf("x");
    }else{
        printf("-");
    }

    //打印文件其他用户的权限
    if((unsigned long) buf.st_mode & S_IROTH){
        printf("r");
    }else{
        printf("-");
    }
    if((unsigned long) buf.st_mode & S_IWOTH){
        printf("w");
    }else{
        printf("-");
    }
    if((unsigned long) buf.st_mode & S_IXOTH){
        printf("x");
    }else{
        printf("-");
    }
    printf(" ");

    //获取用户名组名
    getpsd = getpwuid(buf.st_uid);
    getgrp = getgrgid(buf.st_gid);
    printf("%3d", buf.st_nlink);
    printf("%-5s", getpsd->pw_name);
    printf("%-5s", getgrp->gr_name);

    //获取文件名
    int flag;
    for(int i = 0; pathname[i] != '\0'; i++){
        if(pathname[i] == '/'){
            flag = i;
        }
    }

    //打印用户名组名以及文件名
    printf(" %d  %s %s\n", buf.st_blksize, ctime(&(buf.st_atime)), &pathname[flag+1]);
    
    return;
}

void initQueue(Queue* Q){
    QNode *p = (QNode *)malloc(sizeof(QNode));

	p->next = NULL;
	Q->head = Q->rear = p;
}

int enterQueue(Queue* Q, char *p){
    QNode* q = (QNode*)malloc(sizeof(QNode));
    if(q == NULL)  return 0;

    strcpy(q->path, p);
    q->next = NULL;
    Q->rear->next = q;
    Q->rear = q;
    
    return 1;
}


int deleteQueue(Queue* Q, char *p){
    QNode *q;
	if(Q->head == Q->rear)  return 0;

	q = Q->head->next;
	strcpy(p, q->path);
	Q->head->next = q->next;
	
	if(Q->rear == q){
		Q->rear = Q->head;
	}
	
	free(q);
	return 1;
}