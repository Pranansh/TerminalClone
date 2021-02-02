#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include<unistd.h>
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

	struct dirent *d;
	DIR *dir=opendir(".");

	if (!dir){

		perror ("Unable to read directory");
		exit(EXIT_FAILURE);
	}

	
	
	if (strcmp(argv[1],"")==0){

		while ((d=readdir(dir))!=NULL){

			if (d->d_name[0] == '.'){
				continue;
			}

		printf("%s  ", d->d_name);
		}

		printf("\n");

		return 0;

	}
	

	if (argv[1][0]=='-'){

		char ch5=argv[1][1];

		if (ch5=='a'){  //displays files starting with '.'

			if (!dir){

				perror ("Unable to read directory");
				exit(EXIT_FAILURE);
			}

			while ((d=readdir(dir))!=NULL){

				printf("%s  ", d->d_name);
			}

			printf("\n");
			
		}
		else if (ch5=='1'){  //1 entry per line

			if (!dir){

				perror ("Unable to read directory");
				exit(EXIT_FAILURE);
			}

			while ((d=readdir(dir))!=NULL){

				printf("%s  \n", d->d_name);
			}

			printf("\n");

		}
		else{

			printf("Command not found\n");
		}

		return 0;
	}


	// if (!dir){

	// 	perror ("Unable to read directory");
	// 	exit(EXIT_FAILURE);
	// }

	while ((d=readdir(dir))!=NULL){

		if (d->d_name[0] == '.'){
			continue;
		}

		printf("%s  ", d->d_name);
	}

	printf("\n");

	return 0;	
}
