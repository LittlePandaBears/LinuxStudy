#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[]){
  int fd;
  int mode;
  int mode_u;
  int mode_g;
  int mode_o;
  char *path;
  if(argc < 3){
    printf("%s <mode num> <pathname>\n",argv[0]);
    exit(0);
  }
  mode = atoi(argv[1]);
  if(mode >777 || mode < 0){
    printf("mode num error\n");
    exit(0);
  }
  path = argv[2];
  if(fd = open(path, O_CREAT|O_EXCL) == -1){
    perror("open");
    exit(1);
  }
  else {
    printf("create file success\n");
 }
  mode_u = mode / 100;
  mode_g = (mode - mode_u*100) / 10;
  mode_o = (mode -mode_u*100 - mode_g*10);
  mode = mode_u*8*8 + mode_g*8 + mode_o;
  if(chmod(path, mode) == -1){
    perror("chmod error");
    exit(1);
  }
  else {
    printf("change file right success\n");
  }
  close(fd);
  return 0;
}
