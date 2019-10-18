#include <iostream>

using namespace std;

void swap (short *a,short *b)
{
    int x=*a;
    *a=*b;
    *b=x;
}

int main()
{
    short S[256],T[256],K[256],C[256],D[256];
    string msg;
    string keyInStr;
    cout<<"Enter message : ";cin>>msg;
    cout<<"Enter key : ";cin>>keyInStr;
    cout<<endl;

    int keylen=keyInStr.length();
    int i,j,t;
    for(i=0;i<keylen;i++)
        K[i]=keyInStr[i];

    // Initialisation
    for(i=0;i<256;i++)
        S[i]=i , T[i]=K[i%keylen];

    // Initial Permutation of S
    for(i=0;i<256;i++)
    {
        j=(j+S[i]+T[i])%256;
        swap(&S[i],&S[j]);
    }

    // Stream Generation
    i=j=0;
    while(i<msg.length())
    {
        i=(i+1)%256;
        j=(j+S[i])%256;
        swap(S[i],S[j]);
        t=(S[i]+S[j])%256;
        K[i]=S[t];
    }

    cout<<"Plain text : ";
    for(i=0;i<msg.length();i++)
        cout<<(int)msg[i]<<" ";
    cout<<endl;

    // Encryption
    cout<<"Encrypted message : ";
    for(i=0;i< msg.length();i++)
    {
        C[i]=msg[i]^K[i];
        cout<<C[i]<<" ";
    }
    cout<<endl;

    // Decryption
    cout<<"Decrypted message : ";
    for(i=0;i< msg.length();i++)
    {
        D[i]=C[i]^K[i];
        cout<<D[i]<<" ";
    }
    cout<<endl;
    cout<<"Decrypted text : ";
    for(i=0;i< msg.length();i++)
        cout<<(char)D[i];
    cout<<endl;
    return 0;
}
