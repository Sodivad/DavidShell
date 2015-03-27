#include <pwd.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#include "commands.h"

int builtin_cd(char** args){
  if(args[1]==NULL){
    struct passwd* pw = getpwuid(geteuid());
    args[1] = pw->pw_dir;
  }
  if(chdir(args[1]) == -1){
    perror("cd");
  }
  return 0;
}

int  builtin_exit(char** arg){
  return 1;
}


int execute(char** command){
  char* builtins[] = {"cd","exit"}; 
  int builtincnt = sizeof(builtins)/sizeof(char*);
  int (*builtinfunc[])(char**) = {&builtin_cd, &builtin_exit};
  int i;
  for(i=0;i<builtincnt;++i){
    if(!strcmp(command[0],builtins[i])){
      return  (*builtinfunc[i])(command);
    }
  }
  return 0;
}

