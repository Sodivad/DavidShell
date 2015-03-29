#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
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
  else{
    setenv("PWD",getcwd(NULL,0),1);
  }
  return 0;
}

int  builtin_exit(char** arg){
  return 1;
}


void runprogramm(char** args){
  pid_t pid = fork();
  if(pid==-1){
    printf("Creating a new process failed %s",args[0]);
  }
  else if(pid==0){
    if(execvp(args[0],args)==-1){
      perror("That shouldn't happen");
    }
  }
  else{
    int status;
    do{
      waitpid(pid, &status, WUNTRACED);
    }
    while(!WIFEXITED(status)||WIFSIGNALED(status));
  }
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
  runprogramm(command);
  return 0;
}

