#include <iostream>

using namespace std;

int main()
{
    int k;
    string str;
    cout<<"Enter K      : ";cin>>k;
    cout<<"Enter string : "<<endl;
    cin>>str;
    for(int i=0;i<str.length();i++)
    {
        if(isupper(str[i]))
            str[i]=(str[i]-65+k)%26+65;
        else
            str[i]=(str[i]-97+k)%26+97;
    }
    cout<<"Encrypted String :"<<endl;
    cout<<str<<endl;
    return 0;
}
