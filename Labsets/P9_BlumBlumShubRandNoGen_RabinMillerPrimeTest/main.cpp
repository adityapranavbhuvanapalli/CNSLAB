//Author : Aditya Pranav Bhuvanapalli
#include <bits/stdc++.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define typeL unsigned int
using namespace std;

bool prime(typeL  x)
{
    if(x==0 || x==1) return false;
    for(typeL  i=2;i<=sqrt(x);i++)
        if(x%i==0)
            return false;
    return true;
}

typeL  randNofn()
{
    typeL  x;
    do x=rand()%10000; while(x%4!=3 || !prime(x));
    return x;
}

typeL  fnBBS(typeL  p, typeL  q)
{
    typeL  n,s,x,num;
    typeL  i=0,b=0;
    n=p*q;

    do s=rand(); while(s<=1 || s%p==0 || s%q==0);

    cout<<"Number of bits : "; cin>>num;

    x=(s*s)%n;
    while(i<=num)
    {
        x=(x*x)%n;
		b=(b<<1) | (x&1);   // Appending last bit of x to b
		cout<<"X"<<i<<" = "<< x<<endl;
		i++;
    }
    return b;
}

//(a^n)%q
typeL powermod(typeL  a, typeL  n, typeL  q)
{
	typeL res=1;
	for(int i=0; i<n; i++)
		res=(res*a)%q;
	return res;
	
}

string fnRabinMiller(typeL n)
{
	typeL k=0,q,temp=n-1;
	while(temp%2==0)
	{
		temp=temp>>1;
		k++;
	}
	q=temp;
	typeL a=rand()%(n-2)+1;	// 1 < a < n-1
	if(powermod(a,q,n)==1)	return "Inconclusive";
	for(int j=0; j<k; j++)
		if(powermod(a,pow(2,j)*q,n)==n-1)	
			return "Inconclusive";
	return "Composite";
	
}

int main()
{
    typeL  p,q;
    srand(time(NULL));
    p=randNofn();
    q=randNofn();
    cout<<"P="<<p<<" "<<"Q="<<q<<endl;
    typeL  b=fnBBS(p,q);
    cout<<"B="<<b<<endl;
    cout<<fnRabinMiller(b)<<endl;
    return 0;
}


/******************
Output:
P=179 Q=2267
Number of bits : 16
X0 = 229559
X1 = 243915
X2 = 403909
X3 = 303112
X4 = 74035
X5 = 135174
X6 = 368865
X7 = 212704
X8 = 318460
X9 = 173454
X10 = 391303
X11 = 165119
X12 = 269870
X13 = 118225
X14 = 16533
X15 = 241400
X16 = 56235
B=119917
Composite
********************/
