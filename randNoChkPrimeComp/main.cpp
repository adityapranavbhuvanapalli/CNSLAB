#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    srand(time(NULL));
    int i,j,a=rand();
    cout<<a<<endl;
    for(i=a/2;i>1;i--)
    {
        if(a%i==0)
        {
            cout<<"Composite"<<endl;
            return 0;
        }
    }
    cout<<"Prime"<<endl;
    return 0;
}
