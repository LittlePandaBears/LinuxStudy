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

#define PARAM_NONE       0                          
#define PARAM_A          1                          
#define PARAM_L          2                          
#define PARAM_R          4                          
#define LINE_MAX_LEN     150                        
#define STANDARD_LEN     256                        

typedef struct QueueNode{
  char string[256];
  struct QueueNode *next;
}Node;

typedef struct LinkQueue{
  Node *front;
  Node *rear;
}Link;

int maxLen;                                         
int lenLeft;                                       
Link *Q;                                            
char buf_string[256];                               

void my_err(char *err_string, int line){
  printf("line %d:\n", line);
  perror(err_string);
  exit(1);
}


void InQueue(Link *Q, char inString[256]){
  Node *s = (Node*)malloc(sizeof(Node));
  if(s == NULL)
    my_err("Node malloc", __LINE__);
  strcpy(s->string, inString);
  Q->rear->next = s;
  Q->rear = s;
  s->next = NULL;
}

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

int IsEmpty(Link *Q){
  if(Q->front == Q->rear)
    return 1;
  else
    return 0;
}
 
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

void param_NO_L_single_print(char fileName[STANDARD_LEN]){
  int lenGap;                                     
  int i;
  if((maxLen+2) > lenLeft){                        
    printf("\n");
    lenLeft = LINE_MAX_LEN;
  }
  printf("%-s",fileName);                       
  lenGap = maxLen - strlen(fileName);
  for(i = 0; i < lenGap; i++)                    
    printf(" ");
  printf("  ");                                   
  lenLeft = lenLeft - (maxLen + 2);               
}

void param_L_single_print(char fileName[256], struct stat buf){
  char buf_time[64];                             
  struct passwd *pwd;                            
  struct group *grp;                           
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

  printf(" ");                            
  printf("%-4d ", buf.st_nlink);            
  pwd = getpwuid(buf.st_uid);                
  grp = getgrgid(buf.st_gid);
  printf("%-8s ", pwd->pw_name);        
  printf("%-8s ", grp->gr_name);           
  printf("%-8d ", buf.st_size);            
  strncpy(buf_time, ctime(&buf.st_mtime), strlen(ctime(&buf.st_mtime))-1);        
  printf("%-25s  ",buf_time);
  printf("%-s\n", fileName);                                                    
}

void param_single_print(int param, char pathName[256]){
  char fileName[256];                     
  int i, j = 0;
  struct stat buf;                        
  if(lstat(pathName, &buf) < 0){
    my_err("lstat", __LINE__);
  }
  for(i = 0; i < strlen(pathName); i++){
    if(pathName[i] == '/'){
      j = 0;
      continue;
    }
    fileName[j++] = pathName[i];
  }
  fileName[j] = '\0';
  switch (param) {             
  case PARAM_NONE:                      
    if(fileName[0] != '.')
      param_NO_L_single_print(fileName);
    break;

  case PARAM_R:
    if(fileName[0] != '.')
      param_NO_L_single_print(fileName);
    break;
    
  case PARAM_A:                           
    param_NO_L_single_print(fileName);
    break;

  case (PARAM_A+PARAM_R):                   
    param_NO_L_single_print(fileName);
    break;

  case PARAM_L:                            
    if(fileName[0] != '.')
      param_L_single_print(fileName, buf);
    break;

  case (PARAM_L+PARAM_R):                 
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

void param_print_dir(int param, char pathName[256]){
  DIR *dir;
  struct dirent *ptr;
  char pathNames[5000][STANDARD_LEN];       
  char temp[256];
  int count = 0, i, j;
  maxLen = 0;                                       
  if((dir = opendir(pathName)) == NULL)
    my_err("opendir", __LINE__);
  while((ptr = readdir(dir)) != NULL){
    strcpy(pathNames[count], pathName);
    strcat(pathNames[count], ptr->d_name);          
    if(strlen(ptr->d_name) > maxLen)
      maxLen = strlen(ptr->d_name);                 
    if((strcmp(ptr->d_name, "..") != 0) && (strcmp(ptr->d_name, ".") !=0)){
      if( (param & PARAM_R) && IsDir(pathNames[count]) ){
	strcpy(temp, pathNames[count]);
	strcat(temp, "/");
	InQueue(Q, temp);
      }
    }
    count++;
  }
  for(i = 0; i < count; i++){
    for(j = i+1; j < count; j++){
      if(strcmp(pathNames[i], pathNames[j]) > 0){
	strcpy(temp, pathNames[i]);
	strcpy(pathNames[i], pathNames[j]);
	strcpy(pathNames[j], temp);
      }
    }
  }
  lenLeft = LINE_MAX_LEN;                          
  for(i = 0; i < count; i++)
    param_single_print(param, pathNames[i]);        
  if(!(param & PARAM_L))                             
    printf("\n");
}

void main(int argc, char **argv){
  int param = PARAM_NONE;                           
  char pathName[256];                             
  char buf_param[32];                               
  int count = 0;                                  
  struct stat buf;                                 
  int i, j, k;
  for(i = 1; i < argc; i++){
    if(argv[i][0] == '-' ){
      for(j = 1, k = 0; j < strlen(argv[i]); j++, k++)
	buf_param[k] = argv[i][j];
      count++;
    }
  }
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
  if(count == argc-1){
    strcpy(pathName, "./");
    if(param & PARAM_R){
      Q = EstQueue(Q);                            
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
	strcpy(pathName, argv[i]);                                
	if(stat(pathName, &buf) < 0)                           
	  my_err("stat", __LINE__);
	if(S_ISDIR(buf.st_mode)){                                
	  if(pathName[strlen(pathName)-1] != '/')                
	    strcat(pathName, "/");                                  
	  if(param & PARAM_R){
	     Q = EstQueue(Q);                            
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
