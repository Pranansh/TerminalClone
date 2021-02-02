#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
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
	char *name;

	if (argv[1][0]=='-'){

		char ch5=argv[1][1];

		if (ch5=='v'){  //explain what is being done

			name=argv[2];
			ret=remove(name);

			if (ret==0){
				printf("Removing %s\n",name);
			}
			else{
				printf("File Not found\n");
			}
		}
		else if (ch5=='f'){  //ignore non existing files

			name=argv[2];
			ret=remove(name);

		}
		else{

			printf("Command not found\n");
		}

		return 0;
	}

	//ret=rmdir(name);
	name=argv[1];
	ret=remove(name);

	if (ret!=0){
		printf("File not found\n");
	}

	/*
	if (ret==0){
		printf("Deleted successfully\n");
	}
	else{
		printf("Not deleted\n");
	}
	*/

	//printf("%d\n", ret);

	//system("dir");

	return 0;

}

