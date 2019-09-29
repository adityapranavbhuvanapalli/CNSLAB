#include <iostream>
using namespace std;
int main()
{
    int i,j,k=0,m,n,x;
    string text,key,cipher="",decipher="";
    cout<<"Plain Text    : ";cin>>text;
    cout<<"Key           : ";cin>>key;
    m=key.length(),n=text.length();
    // Augmented text
    if(n%m!=0)
        text.append(m-n%m,'x');     //Appending 'x' to text (m-n%m) times
    n=text.length();                //By appending 'x', length of text will change.

    for(i=0;i<m;i++)
    {
        for(j=0;j<n/m;j++)
            cout<<text[k++]<<"\t";
        cout<<endl;
    }
    // Encryption
    for(i=1;i<=m;i++)
        for(j=0;j<n;j++)
            if(key[j%m]-48==i)      //48 is ASCII value of '0'.
                cipher+=text[j];
    cout<<"Cipher Text   : "<<cipher<<endl;
    //Decryption
    x=n/m;
    for(i=0;i<x;i++)
        for(j=0;j<m;j++)
            decipher+=(cipher[(key[j]-48-1)*x+i]);
    cout<<"Decipher Text : "<<decipher<<endl;
    return 0;
}
