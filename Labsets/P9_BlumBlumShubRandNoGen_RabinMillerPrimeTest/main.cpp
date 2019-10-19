//Author : Aditya Pranav Bhuvanapalli
//Note : RabinMiller will be updated shortly
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

int prime(int x)
{
    for(int i=x/2;i>1;i++)
        if(x%i==0)
            return 0;
    return 1;
}

int randNofn()
{
    int x;
    do{
        x=rand()%(1000-100)+100;
    }while(x%4!=3 && !prime(x));
    return x;
}

int gcd(int m, int n)
{
    if(n>0)
        return gcd(n,m%n);
    return m;
}

int fnBBS(int p, int q)
{
    int n,s,x,num;
    int b=0;
    n=p*q;
    do{
        s=rand()%n;
    }while(s==1 && s%p!=1 && s%q!=1);
    x=(s*s)%n;
    cout<<"Number of bits : "; cin>>num;
    while(num--)
    {
        x=(x*x)%n;
		b=(b<<1) | (x&1);   // Appending first bit of x to b
    }
    return b;
}

int main()
{
    srand(time(NULL));
    int p=randNofn(),q=randNofn();
    cout<<"P="<<p<<" "<<"Q="<<q<<endl;
    int b=fnBBS(p,q);
    cout<<"B="<<b<<endl;
    fnRabinMiller(b);
    return 0;
}
