#include <iostream>

using namespace std;

int main()
{
    int i,j,a[2][2];
    cout<<"Enter 2x2 matrix A[2,2] : "<<endl;
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            cin>>a[i][j];
    cout<<"Det(A) = "<<a[0][0]*a[1][1]-a[0][1]*a[1][0]<<endl;
    return 0;
}
