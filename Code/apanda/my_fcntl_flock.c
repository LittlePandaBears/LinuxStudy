#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

/*1.自定义错误处理函数*/
void my_error(char *error_string, int line){
  fprintf(stderr,"line:%d",__LINE__);
  perror(error_string);
  exit(1);
}

/*2.测试是否可以设置锁*/
int lock_test(int fd, struct flock *lock){
  if(fcntl(fd, F_GETLK, lock) == 0){  //执行成功
    if(lock->l_type == F_UNLCK){
      printf("lock can be set\n");
      return 0;
    }
    else {
      if(lock->l_type == F_RDLCK){
	printf("lock can't be set, read lock has been set by %d\n",lock->l_pid);
      }
      else if(lock->l_type == F_WRLCK){
	printf("lock can't be set, write lock has been set by %d\n",lock->l_pid);
      }
      return -2;
    }
  }
  else {
    my_error("get incompatible lock fail",__LINE__);
    return -1;
  }
}

/*3.设置锁*/
int lock_set(int fd, struct flock *lock){
  if(fcntl(fd, F_SETLK, lock) == 0){  //执行成功
    if(lock->l_type == F_RDLCK){
      printf("set read lock, pid:%d\n",getpid());
    }
    else if(lock->l_type == F_WRLCK){
      printf("set write lock, pid:%d\n",getpid());
    }
    else if(lock->l_type == F_UNLCK){
      printf("release lock, pid:%d\n",getpid());
    }
    return 0;
  }
  else {
    my_error("set lock fail",__LINE__);
    return -1;
  }
}

/*主函数*/
int main(int argc, char *argv[]){
  int fd;
  struct flock lock;
  char read_buf[30];
  char *path;
  if(argc < 2){
    printf("%s <pathname>\n",argv[0]);
    exit(0);
  }
  path = argv[1];
  /*打开或创建文件*/
  if((fd = open(path, O_CREAT|O_TRUNC|O_RDWR, S_IRWXU)) < 0){
    my_error("open", __LINE__);
    exit(1);
  }
  /*写入文件*/
  if(write(fd, "I am apanda-xu", 14) != 14){
    my_error("write", __LINE__);
    exit(1);
  }
  /*初始化lock结构*/
  memset(&lock, 0, sizeof(struct flock));
  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_whence = SEEK_SET;
  /*设置读锁*/
  if(lock_test(fd, &lock) == 0){  //说明可以设置锁
     lock.l_type = F_RDLCK;
     lock_set(fd, &lock);
  }
  /*读文件*/
  lseek(fd, 0, SEEK_SET);
  if(read(fd, read_buf, 14) != 14){
    my_error("read", __LINE__);
    exit(1);
  }
  printf("read_buf = %s", read_buf);
  /*等待任意按键*/
  getchar();
  /*设置写锁*/
  if(lock_test(fd, &lock) == 0){
    lock.l_type = F_WRLCK;
    lock_set(fd, &lock);
  }
  /*释放锁*/
  lock.l_type = F_UNLCK;
  lock_set(fd, &lock);
  
  close(fd);
  return 0;
}
