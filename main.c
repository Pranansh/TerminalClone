#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<readline/history.h> 

#define clear() printf("\033[H\033[J") 

int hcnt=0;
char history[51][10000];


int inputfromTerminal(char* str) 
{ 
    char* buf; 
  
    buf = readline(">>> "); 

    if (strlen(buf) != 0) { 
         
        strcpy(str, buf); 
        strcpy(history[hcnt],str);
        hcnt++;
        return 0;

    } 

    else {

        return 1; 
    
    } 
} 

void forking(char** parsed2,char* finalpath2){

    //strcpy(parsed2[3],NULL);
    parsed2[3]=NULL;

    pid_t pt=fork();

    if (pt==-1){

        fprintf(stderr, "Forking failed\n");
    }
    else if (pt==0){

        if (execvp(finalpath2,parsed2)<0){

            printf("Cannot Execute\n");
        }

        exit(0);
    }
    else{

        wait(NULL);
        return ;
    }
}

void external(char** parsed, char* path){

    char finalpath[10000];

    strcpy(finalpath,path);

    int ch3=-1;

    if (strcmp(parsed[0],"ls")==0){
        ch3=0;
        strcat(finalpath,"/ls");
    }
    else if (strcmp(parsed[0],"cat")==0){
        ch3=1;
        strcat(finalpath,"/cat");
    }
    else if (strcmp(parsed[0],"date")==0){
        ch3=2;
        strcat(finalpath,"/date");
    }
    else if (strcmp(parsed[0],"mkdir")==0){
        ch3=3;
        strcat(finalpath,"/mkdir");
    }
    else if (strcmp(parsed[0],"rm")==0){
        ch3=4;
        strcat(finalpath,"/rm");
    }

    // if (ch3==0 || ch3==1 || ch3==2 || ch3==3 || ch3==4){
    //     forking(parsed,finalpath);
    // }
    // else{
    //     printf("Command not found\n");
    // }

    if (ch3==-1){
        printf("Command not found\n");
    }
    else{
        forking(parsed,finalpath);
    }


}

int myCMD(char** parsed) 
{ 
    int i, choice = -1; 
    char* internal[6];
    char* external1[5]; 

    internal[0]="cd"; 
    internal[1]="echo"; 
    internal[2]="history"; 
    internal[3]="pwd";
    internal[4]="exit";
    internal[5] = "help";
  
    external1[0] = "";
    external1[0] = "";
    external1[0] = "";
    external1[0] = "";
    external1[0] = "";

    for (i=0; i<6 ; i++) { 

        if (strcmp(parsed[0], internal[i]) == 0) { 
            choice = i; 
            break; 
        }

    } 

    int ch=choice;

    if (ch==-1){

        //printf("Command not found\n");
            //exit(0);
        return 0;

    }
    else if (ch==0){

        //printf("0\n");

        char cwd2[1024]; 
        getcwd(cwd2, sizeof(cwd2));

        if (cwd2==NULL){
            perror("getcwd() error");
            return 0;
        } 

        if (parsed[1][0]=='-'){

            char ch2=parsed[1][1];
            if (ch2=='L'){

                chdir(parsed[2]); 
                char cwd[1024]; 
                getcwd(cwd, sizeof(cwd)); 
                printf("\nDir: %s\n", cwd);
            }
            else if (ch2=='p'){

                chdir(parsed[2]); 
                char cwd[1024]; 
                getcwd(cwd, sizeof(cwd)); 
                printf("\nDir: %s\n", cwd);

            }
            else{

                printf("Command not found\n");
                return 0;
            }


        }
        else{

            chdir(parsed[1]); 
            char cwd[1024]; 
            getcwd(cwd, sizeof(cwd)); 
            printf("\nDir: %s\n", cwd);

        }
        /*
        chdir(parsed[1]); 
        char cwd[1024]; 
        getcwd(cwd, sizeof(cwd)); 
        printf("\nDir: %s\n", cwd);
        */
        return 1;

    }
    else if (ch==1){

        //printf("1\n");

        char cwd2[1024]; 
        getcwd(cwd2, sizeof(cwd2));

        if (cwd2==NULL){
            perror("getcwd() error");
            return 0;
        } 

        //if (strcmp(parsed[2][0],"-")==0){
        if (parsed[1][0]=='-'){ 

            char ch2=parsed[1][1];
            if (ch2=='n'){
                for (int i=0;i<strlen(parsed[2]);i++){

                    printf("%c", parsed[2][i]);
                
                }

            }
            else if (ch2=='E'){
                printf("%s\n", parsed[2]);
            }
            else{
                printf("Command not found\n");
                return 0;
            }
            //printf("%c\n", parsed[2][1]);
            //printf("YESS\n");
        }
        else{
            printf("%s\n", parsed[1]);
        }

        // printf("%s\n", parsed[1]);
        //printf("\n");
        return 1;

    }
    else if (ch==2){

        //printf("2\n");

        char cwd2[1024]; 
        getcwd(cwd2, sizeof(cwd2));

        if (cwd2==NULL){
            perror("getcwd() error");
            return 0;
        } 

        if (parsed[1][0]=='-'){

            char ch2=parsed[1][1];

            if (ch2=='c'){

                for (int i=0;i<hcnt;i++){
                    strcpy(history[i],"");
                }
                hcnt=0;

            }
            else if (ch2=='d'){

                int todelete=atoi(parsed[2]);
                //todelete--;

                //int i=0;

                /*
                for (;i<todelete;i++){
                    printf("%d  %s\n", i+1, history[i]);
                }
                */

                int i=todelete-1;
                //printf("Deleted history is: %d  %s\n", i+1, history[i]);

                i=todelete;

                for (;i<hcnt;i++){
                    strcpy(history[i-1],history[i]);
                    //history[i-1]=history[i];
                }

                hcnt--;

            }
            else{
                printf("Command not found\n");
                return 0;
            }
        }
        else{
            
            for (int i=0;i<hcnt;i++){
               //puts(history[i]);
                printf("%d  %s\n", i+1, history[i]);
            }
        }

        /*
        for (int i=0;i<hcnt;i++){
            puts(history[i]);
        }
        */
        //printf("\n");
        return 1;

    }
    else if (ch==3){

        //printf("3\n");

        char cwd2[1024]; 
        getcwd(cwd2, sizeof(cwd2));

        if (cwd2==NULL){
            perror("getcwd() error");
            return 0;
        } 


        if (parsed[1][0]=='-'){

            char ch2=parsed[1][1];
            if (ch2=='L'){

                char cwd1[1024]; 
                getcwd(cwd1, sizeof(cwd1)); 
                printf("Directory: %s\n", cwd1);
            }
            else if (ch2=='p'){

                char cwd1[1024]; 
                getcwd(cwd1, sizeof(cwd1)); 
                printf("Directory: %s\n", cwd1);

            }
            else{

                printf("Command not found\n");
                return 0;
            }


        }
        else{

            char cwd1[1024]; 
        getcwd(cwd1, sizeof(cwd1)); 
        printf("Directory: %s\n", cwd1);

        }
        /*
        char cwd1[1024]; 
        getcwd(cwd1, sizeof(cwd1)); 
        printf("\nDirectory: %s", cwd1);
        */
        //printf("\n");
        return 1;

    }
    else if (ch==4){

        //printf("4\n");
        exit(0);

    }
    else if (ch==5){

        printf("5\n"); 
        printf("List Of supported commands :\n");
        printf("cd\n");
        printf("echo\n");
        printf("history\n");
        printf("pwd\n");
        printf("exit\n"); 
        //printf("\n");
        return 1;

    }
    else {

        //break;

    }
  
    return 0; 

} 

int myTokenizer(char* str, char** parsed) 
{  
    
    for (int i=0;i<5;i++){

        *(parsed+i) = (char*) malloc(100 * sizeof(char));

    }
    
    int cnt=0;
    char s[100]="";

    for (int i=0; i < strlen(str) ; i++){

        if (str[i]==' '){

            strcpy(*(parsed+cnt),s);
            cnt++;
            strcpy(s,"");
            //printf("HELLO %s\n", *(parsed+cnt-1));
        }
        else{

            //printf("HEY\n");
            int l=strlen(s);
            s[l]=str[i];
            s[l+1]='\0';
        }

        //printf("%s\n", s);

    }

    strcpy(*(parsed+cnt),s);

    /*
    for (int i=0;i<cnt+1;i++){
        printf("%s\n", *(parsed+i));
    }
    */
    
  
    if (myCMD(parsed)) 
        return 0; 
    else
        return 1; 
} 

int main() 
{ 
    char temp='y';
    char inp[1000];  

    int eflag = 0; 
  
    char *parsed1[100];

    char path[10000];

    getcwd(path,sizeof(path));


    while (temp=='y') { 

        int flag1=inputfromTerminal(inp);

        if (flag1){

            continue; 

        }

        eflag = myTokenizer(inp, parsed1); 
  		
  		if (eflag==0){

  			continue;	
        
        }
        else{

            external(parsed1, path);
        }

    } 
    return 0; 
}