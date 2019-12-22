#include<stdio.h>
#include<stdlib.h>

#define LINELEN 512

void display(FILE*);

int main(int argc, char* argv[]){
    if(argc == 1){
        printf("This is the help page.\n");
        exit(0);
    }
    FILE* fp;
    int i = 1;
    while(i < argc){
        fp = fopen(argv[i],"r");
        if(fp == NULL){
            perror("Error in opening file.\n");
            exit(1);
        }
        display(fp);
        fclose(fp);
        i++;
    }
    return 0;
}

void display(FILE* fp){
    char buf[LINELEN];
    while(fgets(buf, LINELEN, fp))
        fputs(buf, stdout);
}


