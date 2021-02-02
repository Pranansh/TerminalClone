#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
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

	int fd;
	char buf[100001];
	char *name;

	if (argv[1][0]=='-'){

		char ch5=argv[1][1];

		if (ch5=='u'){  //igmored

			name=argv[2];

			fd=open(name,O_RDONLY);

			if (fd==-1){
				printf("Failed to open\n");
				exit(1);
			}

			read(fd,buf,10000);

			close(fd);

			puts(buf);
		}
		else if (ch5=='E'){  //display $ at end of each line

			name=argv[2];
			fd=open(name,O_RDONLY);

			if (fd==-1){
				printf("Failed to open\n");
				exit(1);
			}

			read(fd,buf,10000);

			close(fd);

			for (int i=0;i<strlen(buf);i++){
				if (buf[i]=='\n')
					printf("$\n");
				else
					printf("%c", buf[i]);
			}
			printf("$\n");

		}
		else{

			printf("Command not found\n");
		}

		return 0;
	}

	name=argv[1];

	fd=open(name,O_RDONLY);

	if (fd==-1){
		printf("Failed to open\n");
		exit(1);
	}

	read(fd,buf,10000);

	close(fd);

	puts(buf);

	//system("dir");

	return 0;
}