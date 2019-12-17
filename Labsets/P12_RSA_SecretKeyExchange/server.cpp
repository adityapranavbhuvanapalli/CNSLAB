#include<arpa/inet.h>
#include<sys/socket.h>
#include<iostream>
using namespace std;
#define SA struct sockaddr
#define typeL unsigned long

typeL gcd(typeL a, typeL b)
{
	return (b==0)?a:gcd(b,a%b);
}

typeL powermod(typeL a, typeL x, typeL n)
{
	typeL res=1;
	for(typeL i=0;i<x;i++)
		res=res*a%n;
	return res;
	
}

int main()
{
	srand(time(NULL));
	
	typeL sockfd=socket(AF_INET,SOCK_STREAM,0);
	typeL port;
	cout<<"Port : ";cin>>port;
	struct sockaddr_in server={AF_INET,htons(port),inet_addr("127.0.0.1")},client;
	bind(sockfd,(SA*)&server,sizeof(server));
	
	listen(sockfd,5);
	socklen_t len=sizeof(client);
	typeL connfd=accept(sockfd,(SA*)&client,&len);
	//End of Connection
	
	typeL p,q,e,d;
	cout<<"P=";cin>>p;
	cout<<"Q=";cin>>q;
	
	typeL n=p*q;
	typeL phi=(p-1)*(q-1);
	
	do e = rand()%(phi-3)+2; while(gcd(e,phi)!=1);
	do d = rand()%(phi-3)+2; while((e*d)%phi!= 1);
			
	typeL PUa[2]={e,n} , PRa[2]={d,n};
	typeL PUb[2];
	//RSA algo done
	
	send(connfd,&PUa,sizeof(PUa),0);
	recv(connfd,&PUb,sizeof(PUb),0);
	//cout<<"PRa = "<<PRa[0]<<" "<<PRa[1]<<endl;
	cout<<"PUa = "<<PUa[0]<<" "<<PUa[1]<<endl;
	cout<<"PUb = "<<PUb[0]<<" "<<PUb[1]<<endl;
	//Exchange public keys done
	
	typeL N1,N2,IDa,msg,cip;
	//1
	N1=rand()%100; 
	IDa=rand()%100;
	msg=N1*100+IDa;
	cip=powermod(msg,PUb[0],PUb[1]);
	cout<<"N1+IDa = "<<msg<<endl;
	cout<<"Encrypt N1+IDa = "<<cip<<endl;
	send(connfd,&cip,sizeof(cip),0);
	//2
	recv(connfd,&cip,sizeof(cip),0);
	msg=powermod(cip,PRa[0],PRa[1]);
	cout<<"Received Encrypt N1+N2 = "<<cip<<endl;
	cout<<"Decrypted N1+N2 = "<<msg<<endl;
	if(N1==msg/100)
		cout<<"N1 is valid"<<endl;
	//3	
	N2=msg%100;
	cip=powermod(N2,PUb[0],PUb[1]);
	cout<<"N2 = "<<N2<<endl;
	cout<<"Encrypt N2 = "<<cip<<endl;
	send(connfd,&cip,sizeof(cip),0);
	//4
	typeL Ks=rand()%1000;
	cip=powermod(Ks,PRa[0],PRa[1]);
	cip=powermod(cip,PUb[0],PUb[1]);
	send(connfd,&cip,sizeof(cip),0);
	cout<<"Secret Key sent = "<<Ks<<endl;
	
	return 0;
}
