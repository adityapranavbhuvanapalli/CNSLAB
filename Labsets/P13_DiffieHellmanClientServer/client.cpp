#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SA struct sockaddr
using namespace std;

unsigned long powermod(unsigned long a, unsigned long b, unsigned long  q)
{
	unsigned long res=1;
	for(unsigned long i=0;i<b;i++)
		res=(res*a)%q;
	return res;
}

int main()
{
	
    
    int port;
    char addr[100]={'\0'};
    cout<<"Address  : "; gets(addr);
    cout<<"Port     : "; cin>>port;
    
	srand(time(NULL));
	unsigned long q, alpha, Xa, Ya, Yb, k;
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

	unsigned long cipher;	
	recv(sockfd, &cipher, sizeof(cipher), 0);
	unsigned long decipher=cipher^k;	
	cout<<"Received message  : "<<cipher<<endl;
	cout<<"Decrpyted message : "<<decipher<<endl;

    close(sockfd);
    return 0;
}
