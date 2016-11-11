/* Author: Omar Mohammed Mousa
   Student ID #: 006181240
  Title: Parent Child communication (Homework #2)
  Description:
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
  pid_t pid;
  int mypipefd[2];
  char buf[20] = "Daddy my name is ";
  char buf2[60] = "I am your Daddy! and My name is ";


  pipe(mypipefd); /* creating a pipe */

  if(pid == -1)
  {
    perror("pipe");
    exit(1);
  }
  int pid2 = getpid();
  pid = fork(); /* creating a child process */
  if(pid == 0)
  {
    /* Child Process */
    close(mypipefd[0]); //blocking the receiving end for the Parent Process
    write(mypipefd[1], buf,18); // writing from the child end to communicate with parent
    read(mypipefd[0],buf2,65);
    printf("%s %d\n", buf2,pid2);

  }
  else
  {
     /* Parent Process */
    //printf("I am your Daddy! and my Name is %d\n", getpid());
  //  write(mypipefd[0], "I am your Daddy! and my Name is ", 18);
    close(mypipefd[1]);// blocking the receiving end of the child process
    write(mypipefd[0],buf2,65);
    read(mypipefd[1],buf,18); // reading through the Parent process end of the pipe
    printf("%s %d\n", buf,pid); // printing out what was written
  }


}

