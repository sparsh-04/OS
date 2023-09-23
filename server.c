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
int
get_number (char a[])
{
  int i = 1, num = 0;
  while (a[i] != ';')
    {
      num = num * 10;
      num += a[i] - '0';
      i++;
    }
  return num;
}

int
get_taski (char *a)
{
  int i = 0;

  while (a[i++] != ';')
    {
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
	  write (pipe_fd[1], buf.mtext, sizeof (buf.mtext));

	  // close (pipe_fd[1]);
	}
      else
	{


	  //child process
	  int len;
	  close (pipe_fd[1]);
	  char parent_a[1000];
	  memset (parent_a, '\0', sizeof (parent_a));
	  read (pipe_fd[0], parent_a, 100);
	  close (pipe_fd[0]);

	  int client_id = get_number (parent_a);
	  int start = get_taski (parent_a);
	  buf.mtype = client_id;
	  char *file_name;
	  // strncpy(file_name,parent_a+(start),sizeof(buf.mtext));
	  // printf("abc %s",parent_a);
	  switch (parent_a[0])
	    {
	    case '1':
	      len = sprintf (buf.mtext, "hello");
	      // break;
	      // case '2':

	      // len=sprintf(buf.mtext, )

	      if (msgsnd (msqid, &buf, len + 1, 0) == -1)
		{
		  perror ("msgsnd");
		  exit (0);
		}
	      // close (pipe_fd[0]);
	      break;
	    case '2':

	      file_name = buf.mtext+start;
    int child_pipe_fd[2];
        char find_output[1000]; // Buffer to store the output from find
    if (pipe(child_pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t new_child_pid;

    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (new_child_pid == 0) {
        // Child process
        char file_name_reveive[1000];
        memset(file_name_reveive, '\0', sizeof(file_name_reveive));

        read(child_pipe_fd[0], file_name_reveive, 1000);
        printf("Reader: %s\n",file_name_reveive);
        close(child_pipe_fd[0]); // Close the read end of the pipe
        dup2(child_pipe_fd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(child_pipe_fd[1]); // Close the write end (not needed after redirection)
        // printf(" aab %s",file_name);
        // Execute the find command in the child process
        execlp("find", "find", ".", "-name", file_name_reveive, NULL);

        // If execlp fails, print an error message
        perror("execlp");
        exit(1);
    } else {        
      	  
        write (child_pipe_fd[1], file_name, sizeof (file_name));



        // Parent process
        close(child_pipe_fd[1]);
        wait(NULL); // Close the write end of the pipe

        ssize_t bytes_read = read(child_pipe_fd[0], find_output, sizeof(find_output));

        if (bytes_read == -1) {
            perror("read");
            return 1;
        }

        // Null-terminate the string
        find_output[bytes_read/2] = '\0';

        // printf("find_output: %s", find_output);

        close(child_pipe_fd[0]); // Close the read end of the pipe

    }
          printf("find_output: %s", find_output);

    	      len = sprintf (buf.mtext, "%s",find_output);
 if (msgsnd (msqid, &buf, len + 1, 0) == -1)
		{
		  perror ("msgsnd");
		  exit (0);
		}

	      break;

	    default:
	      break;
	    }
	  return 0;
	}



    }
  return 0;
}
