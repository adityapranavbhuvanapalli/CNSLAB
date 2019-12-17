#include<arpa/inet.h>
#include<sys/socket.h>
#include<iostream>
using namespace std;
#define SA struct sockaddr
#define typeL unsigned long

typeL gcd(typeL m, typeL n)
{
    return (n==0) ? m : gcd(n, m%n);
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
	struct sockaddr_in server={AF_INET,htons(port),inet_addr("127.0.0.1")};
	
	connect(sockfd,(SA*)&server,sizeof(server));
	//End of connection
	
	typeL p,q,e,d;
	cout<<"P=";cin>>p;
	cout<<"Q=";cin>>q;
	
	typeL n=p*q;
	typeL phi=(p-1)*(q-1);
	
	do e = rand()%(phi-3)+2; while(gcd(e,phi)!=1);
	do d = rand()%(phi-3)+2; while((e*d)%phi!= 1);
			
	typeL PUb[2]={e,n} , PRb[2]={d,n};
	typeL PUa[2];
	//RSA algo done
	
	recv(sockfd,&PUa,sizeof(PUa),0);	
	send(sockfd,&PUb,sizeof(PUb),0);
	cout<<"PUa = "<<PUa[0]<<" "<<PUa[1]<<endl;
	//cout<<"PRb = "<<PRb[0]<<" "<<PRb[1]<<endl;
	cout<<"PUb = "<<PUb[0]<<" "<<PUb[1]<<endl;
	//Exchange public keys done
	
	typeL N1,N2,msg,cip;
	//1
	recv(sockfd,&cip,sizeof(cip),0);
	msg=powermod(cip,PRb[0],PRb[1]);
	cout<<"Received Encrypt N1+IDa = "<<cip<<endl;
	cout<<"Decrypted N1+IDa = "<<msg<<endl;
	N1=msg/100;
	//2
	N2=rand()%100;
	msg=N1*100+N2;
	cip=powermod(msg,PUa[0],PUa[1]);
	cout<<"N1+N2 = "<<msg<<endl;
	cout<<"Encrypt N1+N2 = "<<cip<<endl;
	send(sockfd,&cip,sizeof(cip),0);
	//3
	recv(sockfd,&cip,sizeof(cip),0);
	msg=powermod(cip,PRb[0],PRb[1]);
	cout<<"Received Encrypt N2 = "<<cip<<endl;
	cout<<"Decrypted N2 = "<<msg<<endl;
	if(N2==msg)
		cout<<"N2 is valid"<<endl;
	//4
	recv(sockfd,&cip,sizeof(cip),0);
	cip=powermod(cip,PUa[0],PUa[1]);
	typeL Ks=powermod(cip,PRb[0],PRb[1]);
	cout<<"Secret Key received = "<<Ks<<endl;
	
	return 0;
}
