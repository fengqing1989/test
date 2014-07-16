#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include <errno.h>

void findfile(char* path,char targetfile[512]){
	struct stat info;
	DIR *pDir;
	struct dirent* ent;
	char childpath[512];
	if (!(pDir=opendir(path))){
		fprintf(stderr, "%s is not exist: %s\n", path, strerror(errno));
		return ;
	}
	memset(childpath,0,sizeof(childpath));
	//定义一个所要查找的目标文件
	while((ent=readdir(pDir))){//目录不为空
		if(ent->d_type&DT_DIR){//是目录不是文件
			if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0){
				continue;
			}
	//在递归过程中判断所要找的文件，边循环、边匹配。如果匹配则跳出循环并输出路径
			sprintf(childpath,"%s/%s",path,ent->d_name);
		//	printf("path:%s\n",childpath);
			if(strcmp(ent->d_name,targetfile)==0){
				printf("path:%s\n",path);
				printf("the targetfile is:%s\n",targetfile);
			}
			findfile(childpath,targetfile);
		}
		else{
			if(strcmp(ent->d_name,targetfile)==0){//如果目标是文件不是目录也打印输出
				printf("path:%s\n",path);
				printf("the targetfile is:%s\n",targetfile);
			}
		}
	}
}

int main(int argc,char* argv[]){
	if(argc < 2){
		printf("please use:%s <PATH>\n",argv[0]);
		exit(-1);
	}
//	DIR *pDir;
	char targetfile[512];
	printf("please input the file name what you want to find:\n");
	scanf("%s",targetfile);
	findfile(argv[1],targetfile);
//	closedir(pDir);
	return 0;
}
