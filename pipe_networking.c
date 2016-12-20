
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "pipe_networking.h"

int server_handshake(int * from_client) {
  mkfifo("pipe",0644);
  *from_client = open("pipe",O_RDONLY);
  char message[MESSAGE_BUFFER_SIZE];
  read(*from_client, message, MESSAGE_BUFFER_SIZE);
  printf("Received message: %s\n", message);
  int rm = remove("pipe");
  int clientSend = open(message, O_WRONLY);
	printf("Found private pipe: %s\n", message);
	char *confMessage = "pipe";
	printf("Confirmation message...\n");
	write(clientSend, confMessage, MESSAGE_BUFFER_SIZE);
	return clientSend;
}

int client_handshake(int *to_server){
  char message[MESSAGE_BUFFER_SIZE];
  int pid = getpid();
  sprintf(message, "%d", pid);
  mkfifo(message, 0644);
  *to_server = open("fifo", O_WRONLY);
  write(*to_server, message, sizeof(message));
  int serverMessage = open(message, O_RDONLY);
  char *buffer;
  read(serverMessage, buffer, MESSAGE_BUFFER_SIZE);
  printf("received: %s\n", buffer);


 return *to_server;
}
