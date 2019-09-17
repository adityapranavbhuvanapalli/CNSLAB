#include <iostream>

using namespace std;

int main()
{
    int i,j,k,l,a[3][3],sign=1,res=0,pos,neg,temp[4]={1,-1,-1,1};
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            cin>>a[i][j];
    for(k=0;k<3;k++)
    {
        l=0;
        pos=neg=1;
        for(i=1;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(j!=k)
                {
                    if(temp[l]>0)
                        pos*=a[i][j];
                    else
                        neg*=a[i][j];
                    l++;
                }
            }
        }
        res+=(sign*a[0][k]*(pos-neg));
        sign=-sign;
    }
    cout<<res<<endl;
    return 0;
}
