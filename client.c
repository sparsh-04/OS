#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>

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
  int msgqid, len;
  key_t key;
  int client_id;
  printf ("Enter Client-ID: ");
  scanf ("%d", &client_id);

  printf ("Enter 1 to contact the Ping Server\n");
  printf ("Enter 2 to contact the File Search Server\n");
  printf ("Enter 3 to contact the File Word Count Server\n");
  printf ("Enter 4 if this Client wishes to exit\n");
  char a[1000];
// memset
// for(int i=0;i<100;i++)
// a[i]='\0';


  int which_task_to_do;
  scanf ("%d", &which_task_to_do);
  int leni=0;
    if ((key = ftok("server.c",'B')) == -1){
    perror("ftok");
    exit(1);
  }
    if ((msgqid = msgget(key, PERMS )) == -1){
    perror("msgget");
    exit(1);
  }
      /* code */
      buf.mtype=1000;
  switch (which_task_to_do)
    {
    case 1:
    buf.mtext[0]='1';
      leni=1;
      leni+= sprintf (buf.mtext+1, "%d",client_id);
      leni+= sprintf (buf.mtext+leni, "%c",';');
      leni += sprintf (buf.mtext+leni, "hi");
      printf("\t%s",buf.mtext);
      if (msgsnd (msgqid, &buf, leni + 1, 0) == -1)
	{
	  perror ("msgsnd");
	  exit (0);
	}

printf("Reader: ready to recieve message.\n");
//printf("Enter: lines of text message.\n");
// buf.mtype=1;
     while (1){
             if(msgrcv(msgqid,&buf,sizeof(buf.mtext)+1,client_id,0)==-1){

             perror("msgrcv");
             exit(1);
             }

     printf("Reader: \"%s\"\n",buf.mtext);

     }
  //    if (msgctl(msgqid, IPC_RMID, NULL) == -1){
  //   perror("msgctl");
  //   exit(1);
  // }

      break;





    case 2:
       
      printf ("Enter the file name\n");
      scanf ("%s", a);
       leni = sprintf (buf.mtext, "%s",a);
      if (msgsnd (msgqid, &buf, leni + 1, 0) == -1)
	{
	  perror ("msgsnd");
	  exit (0);
	}

if((msgqid=msgget(key, PERMS | IPC_CREAT))==-1){
     perror("MSGGET");
     exit(1);
}
        while (1){
             if(msgrcv(msgqid,&buf,sizeof(buf.mtext),client_id,0)==-1){

             perror("msgrcv");
             exit(1);
             }

     printf("Reader: \"%s\"\n",buf.mtext);

     }

      break;
      // printf("%s",a);

      break;


      /* code */
    case 3:
      /* code */
      break;
    case 4:
      /* code */
      break;
    default:
      break;
    }

// if((key=ftok("Writer.c",'B'))==-1){
//      perror("ftok");
//      exit(1);
// }
// if((msqid=msgget(key, PERMS | IPC_CREAT))==-1){
//      perror("MSGGET");
//      exit(1);
// }
// printf("Reader: ready to recieve message.\n");
// //printf("Enter: lines of text message.\n");
// //buf.mtype=1;
//      while (1){
//              if(msgrcv(msqid,&buf,sizeof(buf.mtext),0,0)==-1){

//              perror("msgrcv");
//              exit(1);
//              }

//      printf("Reader: \"%s\"\n",buf.mtext);

//      }




  return 0;
}
