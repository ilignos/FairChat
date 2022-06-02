#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> //gia to exit()

int main(){
  int welcomeSocket, newSocket[10];
  char buffer[1024];
  char newbuffer[1024];
  char password[32];
  
  int pid;
  int client_num;

  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;


  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;  
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    perror("Listen:\n");

  addr_size = sizeof serverStorage;

  int i;
  int k;

  printf("Give the number of clients you want to FAIR CHAT:");
  scanf("%d",&client_num);
  
  char name[client_num][1024]; //AFOU KSEROUME TON ARITHMO TWN CLIENTS FTIAXNOUME ENAN PINAKA string pou tha mas dinei to onoma tou kathenos

  sprintf(buffer, "%d", client_num); //int to string gia na to steiloume mesw send 

  printf("Create a password (=sunthhma in greek):");
  scanf("%s",password);


  while (1){
	 for(i=0;i<client_num;i++){

		//printf("Waiting for the #%d client to login\n",i+1);
		printf("Waiting...\n");
	 	newSocket[i] = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
		
		if (newSocket[i] < 0) { 
			perror("Socket"); 
			continue;}

		send(newSocket[i],buffer,sizeof(buffer),0); //stelnoume to client_num stous clients
		send(newSocket[i],password,sizeof(password),0); //stelnoume to password stous clients
	}
	
	//STELNOUN OLOI TO USERNAME TOUS STON SERVER
	for(i=0;i<client_num;i++){
		recv(newSocket[i],newbuffer,sizeof(newbuffer),0);
		strcpy(name[i],newbuffer);
	}
	//AFOU VRHKAN TO PASSWORD STELNOUN STON SERVER
	for(i=0;i<client_num;i++){
		recv(newSocket[i],newbuffer,sizeof(newbuffer),0);
	}
	//OTAN TON VROUN OLOI O SERVER STELNEI PISW
	for(i=0;i<client_num;i++){
		send(newSocket[i],buffer,sizeof(buffer),0);
	}
	
	/*//O SERVER STELNEI OLA TA USERNAME PISW SE AYTOUS
	for(i=0;i<client_num;i++){
		for(k=0;k<client_num;k++){
			send(newSocket[i],name[k],sizeof(name),0);
		}
	}*/

	printf("Now the all the clients are ready for a FAIR CHAT\n");

        pid = fork();
	//printf("PID = %d\n",pid);
	  if (pid < 0)
		{
			perror("Could not fork");
			exit(1);
		}
          if (pid == 0) // This is the child process
		{
			close(welcomeSocket);
			while(1){
				//i=0;
				for(i=0;i<client_num;i++){
					recv(newSocket[i],buffer,sizeof(buffer),0);
					for(k=0;k<client_num;k++){
						if (i==k)
							continue;
						else
							send(newSocket[k],buffer,sizeof(buffer),0);
					}
				}
					//AYTO EINAI ENA PARADEIGMA GIA TO PWS LEITOURGEI TO PANW FOR GIA 3 CLIENTS
					/*recv(newSocket[i],buffer,sizeof(buffer),0);   //i=0

					send(newSocket[i+1],buffer,sizeof(buffer),0);	//i=1
				
					send(newSocket[i+2],buffer,sizeof(buffer),0);	//i=2

					recv(newSocket[i+1],buffer,sizeof(buffer),0);

					send(newSocket[i],buffer,sizeof(buffer),0);

					send(newSocket[i+2],buffer,sizeof(buffer),0);

					recv(newSocket[i+2],buffer,sizeof(buffer),0);

					send(newSocket[i],buffer,sizeof(buffer),0);

					send(newSocket[i+1],buffer,sizeof(buffer),0);
				//}*/
				
			}
			for(i=0;i<client_num;i++)
				close(newSocket[i]);
			exit(0);
		}
	else
		{
		 	// This is the parent
			for(i=0;i<client_num;i++)
		 		close(newSocket[i]);
		}
  }

  close(welcomeSocket);

  return 0;
}
