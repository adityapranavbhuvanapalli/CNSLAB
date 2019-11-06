#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SA struct sockaddr
#define typeL unsigned long
using namespace std;

typeL encrypt(typeL M, typeL PU[2])
{
    typeL C=1;
    for(int i=1; i<=PU[0]; i++)
        C = (C*M)%PU[1];
    return C;
}

int main()
{	
    	int port;
    	char addr[100]={'\0'};
    	cout<<"Address  : "; scanf("%s",addr);
    	cout<<"Port     : "; cin>>port;

	// ****Connection
	struct sockaddr_in server={AF_INET, htons(port), inet_addr(addr)}, client;
    	int sockfd = socket(AF_INET, SOCK_STREAM,0);
    	bind(sockfd, (SA*)&server, sizeof(server));
    	listen(sockfd,1);
    	socklen_t len=sizeof(client);
    	int connfd = accept(sockfd,(SA*)&client,&len);
    	// ****Connection Established
	
	srand(time(NULL));
	typeL PU[2];
	recv(connfd, &PU, sizeof(PU), 0); 
    	cout << "PU = {" << PU[0] << ", " << PU[1] << "}" << endl;

    	typeL M; 
    	cout<<"M = "; cin>>M;

    	typeL C = encrypt(M, PU);
    	cout<<"C : "<<C<<endl;
    	send(connfd, &C, sizeof(C), 0); 
    	cout<<"Sent encrypted message to client"<<endl;
    	return 0;
}



/***************************
Output:
Address  : 127.0.0.1 
Port     : 3400
PU = {3887, 4331}
M = 45
C : 3587
Sent encrypted message to client

****************************/
