/*Gia na treksei swsta to programma oi clients prepei na sundeodai  me th seira me ton prwton na einai o 0*/
/*px gia 3 clients ./client 0 ./client 1 ./client 2*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h> //gia to exit()

int main(int argc, char **argv){
  if (argc != 2)
  {
	printf("usage: %s number of client\n", argv[0]);
	return -1;
  }
  int clientSocket;
  char buffer[1024];
  char password[32];
  char password2[32];
  char name[1024]; 
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  int client_num;
  int i,k;
  int argv_int;
  int table;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  /*GETS THE TOTAL NUMBER OF CLIENTS FROM THE SERVER*/
  recv(clientSocket,buffer,sizeof(buffer),0);
  client_num = atoi(buffer); //number of clients

  /*USERNAME*/
  printf("Give a username!:");
  scanf("%s",name);

  /*PASSWORD*/
  recv(clientSocket,password,sizeof(password),0);
  printf("Who is the password?:");
  scanf("%s",password2);
  while(strcmp(password2,password)){
	printf("Wrong! Try again:");
  	scanf("%s",password2);
	}

  send(clientSocket,name,sizeof(name),0);

  printf("Correct %s!The fair chat is about to begin!\n",name);
  printf("***********FAIR CHAT INFO ***********\n"
	 "Fair chat is a unique chat program written in c with unique features.\n"
         "The rules are simple! Be patient and wait for your turn to talk.If you\n"
         "want to exit just type exit but this is gonna exit all the users.\n"
         "so be careful!\n"
	 "*************************************\n");
  
  /*OPOIOS CLIENT VRHKE TO PASSWORD STELNEI ENA SEND STON SERVER*/
  send(clientSocket,buffer,sizeof(buffer),0);

  /*AN OLOI OI CLIENTS TON VRHKAN 0 SERVER STELNEI ENA RECV PISW*/
  recv(clientSocket,buffer,sizeof(buffer),0);//diavazoume ksana apton server to client_num gia na mhn paei apeutheias sto while(1), na uparxei anamonh mexri na sundethoun oloi.

  /*//OLA TA USERNAME STON CLIENT
  for(k=0;k<client_num;k++){
	recv(clientSocket,name2[k],sizeof(name2),0);
  }*/

  argv_int = atoi(argv[1]); //kanoume int to argv gia na mas voithisei sto deutero while()

  while(1){
	for(i=0;i<client_num;i++){
		if (i==argv_int){
			fgets(buffer,sizeof(buffer),stdin);	
			send(clientSocket,buffer,sizeof(buffer),0);
			if (strcmp(buffer,"exit\n")==0)
				exit(1);
			else if (strcmp(buffer,"info\n")==0)
				  printf("***********FAIR CHAT INFO ***********\n"
	 				 "Fair chat is a unique chat program written in c with unique features.\n"
        				 "The rules are simple! Be patient and wait for your turn to talk.If you\n"
         				 "want to exit just type exit but this is gonna exit all the users.\n"
         				 "so be careful!\n");
			else if (strcmp(buffer,"private\n")==0)
				  printf("Coming soon.......\n");
			

		}
		else{
			recv(clientSocket,buffer,sizeof(buffer),0);
			printf("%s",buffer);
			if (strcmp(buffer,"exit\n")==0)
				exit(1);
		}
	}

	//AYTO EINAI ENA PARADEIGMA GIA TO PWS LEITOURGEI TO PANW FOR GIA 3 CLIENTS
	/*if (strcmp(argv[1],"1")==0){
		printf("write something:");
		fgets(buffer,sizeof(buffer),stdin);	
		send(clientSocket,buffer,sizeof(buffer),0);

		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("%s",buffer);
		
		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("%s",buffer);}
	else if (strcmp(argv[1],"2")==0){
		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("%s",buffer);

		printf("write something:");
		fgets(buffer,sizeof(buffer),stdin);	
		send(clientSocket,buffer,sizeof(buffer),0);
		
		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("%s",buffer);}

	else if (strcmp(argv[1],"3")==0){
	
		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("%s",buffer);
	
		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("%s",buffer);

		printf("write something:");
		fgets(buffer,sizeof(buffer),stdin);	
		send(clientSocket,buffer,sizeof(buffer),0);}*/
	
  }

}
   
