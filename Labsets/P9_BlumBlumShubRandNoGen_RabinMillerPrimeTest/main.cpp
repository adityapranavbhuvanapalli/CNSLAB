//Author : Aditya Pranav Bhuvanapalli
//Note : RabinMiller will be updated shortly
#include <bits/stdc++.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

bool prime(int x)
{
    if(x==0 || x==1) return false;
    for(int i=2;i<=sqrt(x);i++)
        if(x%i==0)
            return false;
    return true;
}

int randNofn()
{
    int x;
    do{ x=rand()%10000;} while(x%4!=3 || !prime(x));
    return x;
}

int fnBBS(int p, int q)
{
    int n,s,x,num;
    int b=0;
    n=p*q;

    do s=rand(); while(s<=1 || s%p==0 || s%q==0);

    cout<<"Number of bits : "; cin>>num;

    x=(s*s)%n;
    while(num--)
    {
        x=(x*x)%n;
		b=(b<<1) | (x&1);   // Appending last bit of x to b
    }
    return b;
}



int main()
{
    int p,q;
    srand(time(NULL));
    p=randNofn();
    q=randNofn();
    cout<<"P="<<p<<" "<<"Q="<<q<<endl;
    int b=fnBBS(p,q);
    cout<<"B="<<b<<endl;
    //fnRabinMiller(b);
    return 0;
}
