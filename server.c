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
int get_number(char * a){
  int i=0,num=0;
  while(a[i]!=';'){
    num=num*10;
    num+=a[i]-'0';
    i++;
  }
  return num;
}
int get_taski(char * a){
  int i=0;

  while(a[i++]!=';'){
  }
  return i;
}
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
      if (msgrcv (msqid, &buf, sizeof (buf.mtext), 1000, 0) == -1)
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
        //parent process

	  close (pipe_fd[0]);

    write (pipe_fd[1], buf.mtext,1 + strlen(buf.mtext));
	  close (pipe_fd[1]);
	}
      else
	{

    //child process
    int len;
	  close (pipe_fd[1]);
	  char *parent_a;
	  read (pipe_fd[0], parent_a, 200);
    int client_id=get_number(parent_a+1);
    int start = get_taski(parent_a);
    char * file_name;
    buf.mtype = client_id;
    switch (parent_a[0])
    {
    case '1':
      len=sprintf(buf.mtext,"hello");
        printf(" q %s",buf.mtext);
		if(msgsnd(msqid,&buf,len+1,0)==-1){
				perror("msgsnd");
				exit(0);
      break;

    case '2':
    file_name=buf.mtext;
    int child_pipe_fd[2];
    if (pipe (child_pipe_fd) == -1)
    {
      perror ("pipe");
      return 1;
    }
    dup2(child_pipe_fd[1], 1);
        if (execlp("find",".","-name",buf.mtext+start, NULL) == -1){
         perror("execlp");
       }
        close(child_pipe_fd[1]);
	      read (child_pipe_fd[0], buf.mtext, 200);
        close(child_pipe_fd[0]);

      // len=sprintf(buf.mtext, )

	  }
	  close (pipe_fd[0]);
      break;
    
    default:
      break;
    }
    }
// 
// 
// 
// 



}
  return 0;
}
