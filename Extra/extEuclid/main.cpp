#include <iostream>

using namespace std;

int main()
{
    int i, n=26, num,p[100],q[100],r,d,t;
    cin>>num;
    d=n;
    r=num;
    i=0;
    do
    {
        t=d;
        q[i]=d/r;
        d=r;
        r=t%r;
        if(i==0 || i==1) p[i]=i;
        else
        {
            p[i]=(p[i-2]-p[i-1]*q[i-2])%26;
            p[i]=(p[i]>=0?p[i]:26+p[i]);
        }
        i++;
    }
    while(r!=0);
    p[i]=(p[i-2]-p[i-1]*q[i-2])%26;
    p[i]=(p[i]>=0?p[i]:26+p[i]);
    cout<<p[i]<<endl;
    return 0;
}
