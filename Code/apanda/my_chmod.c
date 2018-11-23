#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
  int mode;
  int mode_u;		//所属者权限
  int mode_g;		//同组用户权限
  int mode_o;		//其他用户权限
  char *path;		//文件路径
/*检测参数个数否合法(参数个数反映输入格式是否正确),若不合法则输出正确的输入格式*/
  if(argc < 3){
    printf("%s <mode num> <target file>\n",argv[0]);
    exit(0);
  }
  mode = atoi(argv[1]);		//获取命令行参数
  if(mode > 777 || mode < 0){
    printf("mode num error!\n");
    exit(0);
  }
  mode_u = mode / 100;
  mode_g = (mode - mode_u*100) / 10;
  mode_o = mode - mode_u*100 - mode_g*10;
  path = argv[2]; 		//从命令行获取文件路径
  mode = mode_u*8*8 + mode_g*8 + mode_o;		//转换成八进制
  if(chmod(path, mode) == -1){
    perror("chmod error!");
    exit(1);
  }
  return 0;
}
