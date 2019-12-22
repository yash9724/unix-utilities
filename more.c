#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINELEN 512
#define PAGELEN 21                // currently assuming page length in terminal is fixed

void display(FILE*); 
int get_input();

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
        printf("%s\n", argv[i]);
        for(int j = 0 ; j <= strlen(argv[i]); j++)
            printf("-");
        printf("\n\n");
        display(fp);
        fclose(fp);
        i++;

        printf("\n\n");
    }
    return 0;
}

void display(FILE* fp){
    char buf[LINELEN];
    int no_of_lines_displayed = 0;
    while(no_of_lines_displayed < PAGELEN){
        if(fgets(buf, LINELEN, fp)){
            fputs(buf, stdout);
            no_of_lines_displayed++;
        }
        else
            break;
        if(no_of_lines_displayed == PAGELEN-1){
            int i = get_input();
            if(i == 0)
                break;
            else if(i == 1)
                no_of_lines_displayed -= PAGELEN;
            else if(i == 2)
                no_of_lines_displayed--;
            else
                break;
        }
    }
}

int get_input(){
    char c;
    c = getchar();
    if(c == 'q')
        return 0;
    else if(c ==  ' ')
        return 1;
    else if(c == '\n')
        return 2;
    return 3;
}

