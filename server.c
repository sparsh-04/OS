#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#define ARRAY_SIZE 5
#define PERMS 0644

struct my_msgbuf
{
  long mtype;
  char mtext[200];
};
int
main ()
{
  struct my_msgbuf buf;
  int msqid, len;
  key_t key;
// key_t = ();
// pid_t pid = fork();

  if ((key = ftok ("server.c", 'B')) == -1)
    {
      perror ("ftok");
      exit (1);
    }
  if ((msqid = msgget (key, PERMS | IPC_CREAT)) == -1)
    {
      perror ("msgget");
      exit (1);
    }
  int pipe_fd[2];

// pid_t child_pid = fork();
  pid_t child_pid;
  if (pipe (pipe_fd) == -1)
    {
      perror ("pipe");
      return 1;
    }
  while (1)
    {
      if (msgrcv (msqid, &buf, sizeof (buf.mtext), 0, 0) == -1)
	{
	  perror ("msgrcv");
	  exit (1);
	}
      child_pid = fork ();
      // printf("Reader: \"%s\"\n",buf.mtext);

      if (child_pid == -1)
	{
	  perror ("child fork failed");
	  return 1;
	}
      else if (child_pid != 0)
	{
	  close (pipe_fd[0]);
	  if((buf.mtext[0]='h' )&& (buf.mtext[1]='i')){

	  int child_a[ARRAY_SIZE] = { 1, 2};
	  write (pipe_fd[1], child_a, sizeof (child_a));
	  }
	  close (pipe_fd[1]);
	}
      else
	{
	  close (pipe_fd[1]);
	  int parent_a[5];
	  read (pipe_fd[0], parent_a, 20);
	  if((parent_a[0]=1 )&& (parent_a[1]=2)){
		int len=sprintf(buf.mtext,"hello");
    printf("anefnewf");
		if(msgsnd(msqid,&buf,len+1,0)==-1){
				perror("msgsnd");
				exit(0);
	  }

//   for(int i=0;i<5;i++)
//   printf("%d ",parent_a[i]);
	  close (pipe_fd[0]);


	}
    }
// 
// 
// 
// 



}
  return 0;
}
