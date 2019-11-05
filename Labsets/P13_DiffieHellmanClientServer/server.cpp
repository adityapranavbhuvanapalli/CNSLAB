#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SA struct sockaddr
#define typeL unsigned long
using namespace std;

typeL powermod(typeL a, typeL b, typeL  q)
{
	typeL res=1;
	for(typeL i=0;i<b;i++)
		res=(res*a)%q;
	return res;
}

int main()
{	
    	int port;
    	char addr[100]={'\0'};
    	cout<<"Address  : "; scanf("%s",addr);
    	cout<<"Port     : "; cin>>port;
    
	srand(time(NULL));
	typeL q, alpha, Xb, Yb, Ya, k;
	cout<<"q     = "; cin>>q;
	cout<<"alpha = "; cin>>alpha;
	
	Xb = rand() % (q-1) + 1;
	Yb = powermod(alpha, Xb, q);

	// ****Connection
	struct sockaddr_in server={AF_INET, htons(port), inet_addr(addr)}, client;
    	int sockfd = socket(AF_INET, SOCK_STREAM,0);
    	bind(sockfd, (SA*)&server, sizeof(server));
    	listen(sockfd,1);
    	socklen_t len=sizeof(client);
    	int connfd = accept(sockfd,(SA*)&client,&len);
    	// ****Connection Established
	
	recv(connfd, &Ya, sizeof(Ya), 0);
	send(connfd, &Yb, sizeof(Yb), 0);

	cout<< "Xb = " << Xb <<endl;
	cout<< "Yb = " << Yb <<endl;
	cout<< "Ya = " << Ya <<endl;
	k = powermod(Ya,Xb,q);	
	cout<<"Key k = "<<k<<endl;

	typeL msg;
	cout<<"Enter the msg to send : "; cin>>msg;
	typeL cipher=msg^k;
	send(connfd, &cipher, sizeof(cipher), 0);
    	return 0;
}



/***************************
Output:
Address  : 127.0.0.1
Port     : 5000
q     = 71 
alpha = 7
Xb = 35
Yb = 70
Ya = 19
Key k = 1
Enter the msg to send : 35
****************************/
