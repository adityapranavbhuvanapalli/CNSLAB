#include <iostream>

using namespace std;

int main()
{
    int i,j,a[2][2],det;
    float inva[2][2];
    cout<<"Enter 2x2 matrix A[2,2] : "<<endl;
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            cin>>a[i][j];
    det=a[0][0]*a[1][1]-a[0][1]*a[1][0];
    inva[0][0]=a[1][1]*1.0/det;
    inva[0][1]=-a[0][1]*1.0/det;
    inva[1][0]=-a[1][0]*1.0/det;
    inva[1][1]=a[0][0]*1.0/det;
    cout<<"Inverse of A[2,2] : "<<endl;
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
            cout<<inva[i][j]<<"\t";
        cout<<endl;
    }
    return 0;
}
