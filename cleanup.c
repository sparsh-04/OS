#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define PERMS 0644

// Define a message structure for communication
struct my_msgbuf
{
  long mtype;
  char mtext[200];
};

int main() {
    // Create a message queue
  struct my_msgbuf buf;
  int msgqid, len;
  key_t key;
  int client_id;
 if ((key = ftok("server.c",'B')) == -1){
    perror("ftok");
    exit(1);
  }
    if ((msgqid = msgget(key, PERMS )) == -1){
    perror("msgget");
    exit(1);
  }

    pid_t child_pid; // Keep track of child processes

    // Start the cleanup process
    if ((child_pid = fork()) == 0) {
  struct my_msgbuf buf;
        printf("Do you want the server to terminate? Press Y for Yes and N for No: ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            // Send a termination message to the main server
            buf.mtype = 1; // Use a unique message type for termination
            strcpy(buf.mtext, "terminate");
            msgsnd(msgqid, &buf, sizeof(buf.mtext), 0);
        }
        exit(EXIT_SUCCESS);
    } else if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Main server logic
    while (1) {
    struct my_msgbuf buf;
        msgrcv(msgqid, &buf, sizeof(buf.mtext), 1, 0); // Receive messages with type 1

        if (strcmp(buf.mtext, "terminate") == 0) {
            // Termination sequence: Terminate child servers, cleanup, and exit
            printf("Termination message received. Initiating server shutdown.\n");
            // Add logic here to terminate child server processes.
            // Perform other cleanup tasks as needed.
            // Finally, exit the server.
            exit(EXIT_SUCCESS);
        }
        // Process other messages or handle client requests here.
    }

    return 0;
}
