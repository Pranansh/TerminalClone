#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<error.h>

int main(int argc, char *argv[]){

	if (argc<1){
		exit(EXIT_FAILURE);
		return 0;
	}

	char current[10000];

	getcwd(current,sizeof(current));

	if (current==NULL){
		perror("Directory error");
		return 0;
	}

	int ret;
	char* name;

	//printf("%c\n", argv[1][0]);

	if (argv[1][0]=='-'){

		char ch5=argv[1][1];

		if (ch5=='p'){

			name=argv[2];
			ret=mkdir(name,0777);
			/*
			if (ret){
				printf("No such file or directory exist\n");
			}
			*/
		}
		else if (ch5=='v'){

			name=argv[2];
			ret=mkdir(name,0777);

			if (!ret){
				printf("Created Directory %s\n",name);
			}

		}
		else{

			printf("Command not found\n");
		}

		return 0;
	}

	//if (strcmp(argv[2],""))

	
	name=argv[1];

	//ret=mkdir("NewDirectory", S_IRUSR | S_IRGRP | S_IROTH);
	ret=mkdir(name,0777);


	return 0;
}