#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
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
	typeL q, alpha, Xa, Ya, Yb, k;
	cout<<"q     = "; cin>>q;
	cout<<"alpha = "; cin>>alpha;
	
	Xa = rand() % (q-1) +1;
	Ya = powermod(alpha, Xa, q);
	
	// ****Connection
	struct sockaddr_in server={AF_INET, htons(port), inet_addr(addr)};
    	int sockfd = socket(AF_INET, SOCK_STREAM,0);
    	connect(sockfd, (SA*)&server, sizeof(server));	
    	// ****Connection Established

	
	send(sockfd, &Ya, sizeof(Ya), 0);	
	recv(sockfd, &Yb, sizeof(Yb), 0);	

	cout<< "Xa = " << Xa <<endl;
	cout<< "Ya = " << Ya <<endl;
	cout<< "Yb = " << Yb <<endl;
	k = powermod(Yb,Xa,q);	
	cout<<"Key k = "<<k<<endl;

	typeL cipher;	
	recv(sockfd, &cipher, sizeof(cipher), 0);
	typeL decipher=cipher^k;	
	cout<<"Received message  : "<<cipher<<endl;
	cout<<"Decrpyted message : "<<decipher<<endl;
    	return 0;
}

/************************
Output:
Address  : 127.0.0.1
Port     : 5000
q     = 71
alpha = 7
Xa = 16
Ya = 19
Yb = 70
Key k = 1
Received message  : 34
Decrpyted message : 35
************************/
