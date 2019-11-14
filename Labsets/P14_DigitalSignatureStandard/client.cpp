#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#define SA struct sockaddr
#define typeL long
using namespace std;

typeL powermod(typeL a, typeL b, typeL  q)
{
	typeL res=1;
	for(typeL i=0;i<b;i++)
		res=(res*a)%q;
	return res;
}

typeL inverse(typeL a,typeL m)
{
	typeL x=1,y=0;
	typeL m0=m;
	if(m==1)
		return 0;
	while(a>1)
	{
		typeL r = a%m;
		typeL tempy=y;
		y=x-(a/m)*y;
		x=tempy;
		a=m;
		m=r;
	}
	if(x<0)
		x+=m0;
	return x;
}

typeL H(typeL M)
{
	return (M^1234); //hash key=1234
}

typeL f4(typeL y,typeL p,typeL q,typeL g,typeL hashval, typeL w,typeL r)
{
	typeL u1,u2;
	u1=(hashval*w)%q;
	u2=(r*w)%q;
	return (( powermod(g,u1,p) * powermod(y,u2,p) )%p)%q;
} 

int main()
{
    	int port;
    	char addr[100]={'\0'};
    	cout<<"Address  : "; scanf("%s",addr);
    	cout<<"Port     : "; cin>>port;

	// ****Connection
	struct sockaddr_in server={AF_INET, htons(port), inet_addr(addr)};
    	int sockfd = socket(AF_INET, SOCK_STREAM,0);
    	connect(sockfd, (SA*)&server, sizeof(server));	
    	// ****Connection Established
    
	srand(time(NULL));
	typeL p,q,r,s,w,v,g,hashval,y;
	cout<<"p = "; cin>>p;
	cout<<"q = "; cin>>q;
		
	recv(sockfd, &hashval, sizeof(hashval), 0);	
	recv(sockfd, &r, sizeof(r), 0);
	recv(sockfd, &s, sizeof(s), 0);	
	recv(sockfd, &g, sizeof(g), 0);		
	recv(sockfd, &y, sizeof(y), 0);

	cout<<"Packet received with values"<<endl;
	cout<<"Hash : "<<hashval<<endl;
	cout<<"R    : "<<r<<endl;
	cout<<"S    : "<<s<<endl;
	cout<<"Y    : "<<y<<endl;
	cout<<"G    : "<<g<<endl;
	
	//Verifying
	w=inverse(s,q)%q;	// f3() = (invS) mod q
	typeL u1= (hashval*w)%q;
	typeL u2= (r*w)%q;
	v = ((powermod(g,u1,p)*powermod(y,u2,p))%p)%q;
	cout<<endl<<"V    : "<<v<<endl;

	if(v==r) cout<<"Digital Signature Verified. (V=R)"<<endl;
	else cout<<"Digital Signature is invalid (V!=R)"<<endl;

    	return 0;
}

/************************************
Output:
Address  : 127.0.0.1
Port     : 8000
p = 67
q = 11
Packet received with values
Hash : 1258
R    : 4
S    : 5
Y    : 40
G    : 22
V    : 4
Digital Signature Verified. (V=R)
************************************/
