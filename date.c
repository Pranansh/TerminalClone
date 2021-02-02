#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<unistd.h>

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

	time_t t1;

	time(&t1);

	if (argv[1][0]=='-'){

		char ch5=argv[1][1];

		if (ch5=='u'){

			printf("%s\n", asctime(gmtime(&t1)));
		}
		else{
			printf("command not found\n");
		}
		return 0;
	}

	printf("%s\n", ctime(&t1));

	return 0;
}