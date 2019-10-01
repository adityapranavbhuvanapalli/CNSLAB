#include <iostream>

using namespace std;
int gcd(int m,int n)
{
    if(n>0)
        return gcd(n,m%n);
    return m;
}
int main()
{
    int m,n;
    cout<<"M = ";cin>>m;
    cout<<"N = ";cin>>n;
    cout<<"GCD(M,N) = "<<gcd(m,n)<<endl;
    return 0;
}
