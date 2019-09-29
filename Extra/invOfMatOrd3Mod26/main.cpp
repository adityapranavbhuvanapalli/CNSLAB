#include <iostream>
using namespace std;
int findDet(int a[3][3])
{
    int i,j,k,l,sign=1,res=0,pos,neg,temp[4]={1,-1,-1,1};
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
    cout<<"Det:"<<res<<endl;
    return res;
}
int extEuclid(int num)
{
    int i,n=26,p[100],q[100],r,d,t;
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
    cout<<"InvDet="<<p[i]<<endl;
    return p[i];
}
int main()
{
    int i,j,k,l,a[3][3],mefm[4][4],arr[4]={1,2,0,1},inv[3][3],det,invDet;

    /* Input Matrix */
    cout<<"Enter the matrix:\n";
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            cin>>a[i][j];

    /* Find Determinant */
    det=findDet(a);

    /* Find Multiplicative Inverse of Determinant */
    invDet=extEuclid(det);

    /* Temporary Matrix (MEFM) */
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            mefm[i][j]=a[arr[i]][arr[j]];

    /* Find Inverse Matrix */
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            inv[j][i]=(invDet*(mefm[i][j]*mefm[i+1][j+1]-mefm[i+1][j]*mefm[i][j+1]))%26;
            if(inv[j][i]<0)
                inv[j][i]+=26;
        }

    /* Display Inverse Mod 26 of Matrix */
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
            cout<<inv[i][j]<<"\t";
        cout<<endl;
    }
    return 0;
}
