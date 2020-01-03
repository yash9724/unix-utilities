#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <termios.h>
#include <unistd.h>



#define LINELEN 512
#define PAGELEN 20                               // currently assuming page length in terminal is fixed

int getch(FILE*);
void display(FILE*); 
int get_input(FILE*);

int main(int argc, char* argv[]){
    if(argc == 1){
        display(stdin);
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
    FILE* fp_tty = fopen("/dev/tty","r");
    while(fgets(buf, LINELEN, fp)){
        fputs(buf, stdout);
        no_of_lines_displayed++;
        if(no_of_lines_displayed == PAGELEN){
            int i = get_input(fp_tty);
            if(i == 0){
                printf("\033[1A \033[2K \033[1G");
                exit(0);
            }
            else if(i == 1){
                printf("\033[1A \033[2K \033[1G");
                no_of_lines_displayed -= PAGELEN;
            }
            else if(i == 2){
                printf("\033[1A \033[2K \033[1G");
                no_of_lines_displayed--;
            }
            else{
                printf("\033[1A \033[2K \033[1G");
                break;
            }
        }
    }
}

int get_input(FILE* terminalStream){
    char c;
    printf("\033[7m--more--(%%)\033[m");
    c = getch(terminalStream);
    if(c == 'q')
        return 0;
    else if(c ==  ' ')
        return 1;
    else if(c == '\n')
        return 2;
    return 3;
}

/* reads from keypress, doesn't echo */
int getch(FILE* i)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getc(i);
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
