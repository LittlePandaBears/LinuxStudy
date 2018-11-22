#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<linux/sched.h>

void my_err(const char *err_string, int line){
	fprintf(stderr,"line:%d ", line);
	perror(err_string);
	exit(1);
}

int main(){
        int fd;
	int access_mode;
	int ret;
	if((fd = open("blank1.txt", O_CREAT|O_TRUNC|O_RDWR, S_IRWXU)) == -1){
		my_err("open", __LINE__);
	}
	if((ret = fcntl(fd, F_SETFL, O_APPEND)) < 0){
		my_err("fcntl", __LINE__);
	}
	if((ret = fcntl(fd, F_GETFL, __LINE__))  < 0){
		my_err("fcntl", __LINE__);
	}
	access_mode = ret & O_ACCMODE;
	if(access_mode == O_RDONLY){
		printf("READ ONLY\n");
	}
	else if(access_mode == O_WRONLY){
		printf("WRITE ONLY\n");
	}
	else if(access_mode == O_RDWR){
		printf("READ and WRITE");
	}
	printf("\n");
	close(fd);
	return 0;
}



	
