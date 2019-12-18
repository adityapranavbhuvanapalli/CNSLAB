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

typeL gcd(typeL m, typeL n)
{
    return (n==0) ? m : gcd(n, m%n);
}

typeL decrypt(typeL C, typeL PR[2])
{
    typeL M = 1;
    for(int i=1; i<=PR[0]; i++)
        M = (M*C) % PR[1];
    return M;
}

int main()
{
    	int port;
    	char addr[100]={'\0'};
    	cout<<"Address  : "; scanf("%s",addr);
    	cout<<"Port     : "; cin>>port;
    
	srand(time(NULL));
	typeL p,q,n,phi,e,d;
	cout<<"p = "; cin>>p;
	cout<<"q = "; cin>>q;
	n=p*q;
	phi=(p-1)*(q-1);
	do e = rand()%(phi-3)+2; while(gcd(e,phi) != 1);
	do d = rand()%(phi-3)+2; while((e*d)%phi != 1);
	typeL PR[2]={d,n},PU[2]={e,n};
	
	// ****Connection
	struct sockaddr_in server={AF_INET, htons(port), inet_addr(addr)};
    	int sockfd = socket(AF_INET, SOCK_STREAM,0);
    	connect(sockfd, (SA*)&server, sizeof(server));	
    	// ****Connection Established

	cout<< "PR = {" << d << " , "<< n << "}" <<endl;
	cout<< "PU = {" << e << " , "<< n << "}" <<endl;
	send(sockfd, &PU, sizeof(PU), 0);

	typeL cipher[100];
	string text="";
	recv(sockfd, &cipher, sizeof(cipher), 0);
	cout<<"Received cipher : ";
	for(int i=1;i<=cipher[0];i++)
	{
		cipher[i]= decrypt(cipher[i],PR);
		printf("%02d",cipher[i]);
	}
	cout<<endl;
	for(int i=1;i<=cipher[0];i++)
	{
		if(cipher[i]<26)
			text+=(cipher[i]+'a');
		else
			text+=(cipher[i]+'A'-26);
	}
	cout<<"Decrypted text : "<<text<<endl;	
    	return 0;
}

