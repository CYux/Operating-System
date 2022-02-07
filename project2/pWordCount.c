/*
 * COMP 7500: Projcet 2 
 * Title: A pipe-based word count program
 * 
 * Description:
 * (1) read a file contain a list of words
 * (2) count the total number of words in the file
 * (3) print the number of words in the file
 *
 * * * * * * * * * * * * * 
 * Author: Yuxiang Chen  *
 * Date: Feb/05/2022     *
 * * * * * * * * * * * * *
 *
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PROGRAM_NAME "pWordCount"
#define BUFFER_SIZE  1000
#define READ_END     0
#define WRITE_END    1

void
usage(int status){
  if (status != EXIT_SUCCESS)
    fprintf(stderr,
	    "Please enter a file name.\nUsage: ./%s <file_name>\n"
	    ,PROGRAM_NAME);
}

bool
isChar(char ch){
  if(isspace(ch) || ch == '\t' 
    || ch == '\v'|| ch =='\n')
    return false;
  else
    return true;
}

int main(int argc, char* argv[]){

  FILE* fp;
  //Error handle: User input invalid
  if(argc != 2)
  {
    usage(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
  else{  
    //Open file
    fp = fopen(argv[1], "r");
    //Error handle: File cannot be opened

    if(fp == NULL)
    {
      fprintf(stderr, "Error: File %s cannot be opened\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  char write_msg[BUFFER_SIZE];
  char read_msg[BUFFER_SIZE];
  char line[BUFFER_SIZE];

  pid_t pid;
  int fd[2][2];
  int i;
  int total_words = 0;


  printf("Beginning of pipe....\n");
  
  // Create the pipe
  for(i = 0; i < 2; i++){
    if(pipe(fd[i]) == -1) 
    {
      fprintf(stderr, "Error: Pipe failed");
      return EXIT_FAILURE;
    }
  }

  // Fork a child process
  pid = fork();
  if (pid < 0) 
  {
    fprintf(stderr, "Error: Fork failed");
    return EXIT_FAILURE;
  }

  /*Parent process*/
  else if (pid > 0)
  {
    //close the unused end of the pipe
    close(fd[0][READ_END]);
    close(fd[1][WRITE_END]);

    //Reading file
    printf("Process 1 is reading file \"%s\" now ...\n",argv[1]);
     
    while(fgets(line, BUFFER_SIZE, fp) != NULL){
      strcat(write_msg, line);
    }
     
    printf("Process 1 starts sending data to Process 2 ...\n",argv[1]);

    //Write to the pipe
    write(fd[0][WRITE_END], write_msg, strlen(write_msg)+1);

    //Close the write end of the pipe
    close(fd[0][WRITE_END]);
   
    read(fd[1][READ_END], read_msg, BUFFER_SIZE);
    printf("Process 1 Total words: %s.\n", read_msg);
    
    close(fd[1][READ_END]);
  }

  else
  /*Child process*/ 
  {
    //Close the unused end of the pipe
    close(fd[0][WRITE_END]);
    close(fd[1][READ_END]);

    //Read from the pipe
    read(fd[0][READ_END], read_msg, BUFFER_SIZE);
    //Close the read end of the pipe
    close(fd[0][READ_END]);
    printf("Process 2 finishes receiveing data from Process 1 ...\n");

    printf("Process 2 is counting words now ...\n");    
   
    bool inword = false;
    for(i = 0; i < strlen(read_msg); i++)
    {
      if(isChar(read_msg[i])){
       	inword = true;
      }else if(inword){
	inword = false;
	total_words++;
      }
    }
    sprintf(write_msg, "%d", total_words);

    printf("Process 2 is sending the result back to Process 1 ...\n");

    write(fd[1][WRITE_END], write_msg, strlen(write_msg));
    close(fd[1][WRITE_END]);
 
   }     
    return EXIT_SUCCESS;
}
