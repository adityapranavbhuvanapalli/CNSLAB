#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

		string text;
    	cout<<"Text : "; cin>>text;
		typeL cipher[text.length()+1];
		cipher[0]=text.length();
		cout<<"Text(INT) : ";
		for(int i=1;i<=text.length();i++)
		{
			if(islower(text[i-1]))
				cipher[i]=text[i-1]-'a';
			else
				cipher[i]=text[i-1]-'A'+26;
			printf("%02d",cipher[i]);
		}
		cout<<endl<<"Cipher(INT) : ";
		for(int i=1;i<=text.length();i++)
		{	
			cipher[i]= encrypt(cipher[i],PU);
			printf("%02d",cipher[i]);
		}
		send(connfd,&cipher,sizeof(cipher),0);
    	cout<<endl<<"Sent encrypted message to client"<<endl;
		
    	return 0;
}

