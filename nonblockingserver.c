#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> //gia to exit()
#include <fcntl.h>

int main(){
  int welcomeSocket,welcomeSocket2, newSocket;
  char buffer[1024];

  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;


  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  welcomeSocket2 = welcomeSocket;

  if (welcomeSocket < 0) { perror("Socke1t"); } 
  
  serverAddr.sin_family = AF_INET;  
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  addr_size = sizeof serverStorage;

  //while (1){

	  newSocket= accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

	  fcntl(welcomeSocket2, F_SETFL, O_NONBLOCK);
	  fcntl(newSocket, F_SETFL, O_NONBLOCK);

	  if (newSocket < 0) { perror("Socket"); } 
	  while(1){
	 	 recv(newSocket,buffer,sizeof(buffer),0);
	  	 printf("%s",buffer);

	 	 fgets(buffer,sizeof(buffer),stdin);
		 fcntl(0, F_SETFL, O_NONBLOCK);
	  	 send(newSocket,buffer,sizeof(buffer),0);}

	  /*pid = fork();
	  if (pid < 0)
		{
			perror("Could not fork");
			exit(1);
		}
          if (pid == 0)
		{
			// This is the child process
			close(welcomeSocket);
			
			recv(newSocket,name,sizeof(name),0);
	  		int i=0;

			while(1){

				recv(newSocket,buffer,sizeof(buffer),0);
				printf("%s:%s",name,buffer);
				
				for(k=number;k<0;k--){
					
					send(newSocket[k],name,sizeof(buffer),0);
					send(newSocket[k],buffer,sizeof(buffer),0);
					}


			close(newSocket);
			exit(0);
		}
	else
		{
		 	// This is the parent
		 	close(newSocket);
		}*/

  //}

  close(welcomeSocket);

  return 0;
}
