#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

void  shellprint();
char* readline();


int main(int argc, char** argv){
  
  while(1){
    shellprint();
    char* command = readline();
    printf("%s\n",command);
  }
}

void shellprint(){
  struct passwd* pw = getpwuid(geteuid());
  char* wd = getcwd(NULL,0);
  char host[255];
  gethostname(host,255);
  
  if(!strncmp(wd,pw->pw_dir,strlen(pw->pw_dir))){
    wd += strlen(pw->pw_dir)-1;
    *wd = '~';
  }
  printf("%s:%s:%s$ ",host,pw->pw_name,wd);
}

char* readline(){
  size_t length = 80;
  char* line = malloc(length);
  char c;
  int len = 0; 
  if(!line){
    printf("malloc fail");
    exit(1);
  }
 
  while(1){
    c = getchar();
    if(c=='\n'||c==EOF){
      line[len] = '\0';
      return line;
    }
    line[len] = c;
    ++len;
    if(len%length==0){
      line = realloc(line,len+length);
      if(line==NULL){
	printf("realloc fail");
	exit(1);
      }
    }
  }
}
