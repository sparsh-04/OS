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
int get_number(char  a[]){
  int i=1,num=0;
  while(a[i]!=';'){
    num=num*10;
    num+=a[i]-'0';
    i++;
  }
    printf("%d\n",num);
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

// pid_t child_pid = fork();
  pid_t child_pid;
  while (1)
    {
  int pipe_fd[2];
  if (pipe (pipe_fd) == -1)
    {
      perror ("pipe");
      return 1;
    }
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
    // char parent[100];
    write (pipe_fd[1], buf.mtext, sizeof(buf.mtext));
    // read (pipe_fd[0], parent, 100);
    // write (pipe_fd[1], buf.mtext, sizeof(buf.mtext));

    // printf("%s\t gfg \n",parent);

	  // close (pipe_fd[1]);
	}
      else
	{


    //child process
    int len;
	  close (pipe_fd[1]);
	  char parent_a[1000];
    memset(parent_a,'\0',sizeof(parent_a));
	  read (pipe_fd[0], parent_a, 100);
    close (pipe_fd[0]);
        printf("%s a\n",parent_a);

    int client_id=get_number(parent_a);
    int start = get_taski(parent_a);
    buf.mtype = client_id;
    switch (parent_a[0])
    {
    case '1':
      len=sprintf(buf.mtext,"hello");
      // break;
    // case '2':

      // len=sprintf(buf.mtext, )

		if(msgsnd(msqid,&buf,len+1,0)==-1){
				perror("msgsnd");
				exit(0);
	  }
	  // close (pipe_fd[0]);
      break;
    
    default:
      break;
    }
    return 0;
    }
// 
// 
// 
// 



}
  return 0;
}
