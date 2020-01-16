#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>

void do_ls(char*);

extern int errno;
int main(int argc, char **argv){
   if(argc == 1)
        do_ls("./");
    else{
        for(int i = 1 ; i < argc; i++){
            printf("%s:\n\n", argv[i]);
            do_ls(argv[i]);
        }
    }
    return 0;
}

void do_ls(char *dirpath){
    DIR *dirp = opendir(dirpath);
    if(dirp == NULL){
        fprintf(stderr,"Cannot read directory : %s\n",dirpath);
        return;
    } 
    errno = 0;
    struct dirent *entry;
    while((entry = readdir(dirp)) != NULL){
        if(entry == NULL && errno != 0){
            perror("readdir failed");
            exit(errno);
        }else
            printf("%s\n",entry->d_name);
    }

    closedir(dirp);
}

