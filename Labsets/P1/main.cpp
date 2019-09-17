#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void computeKeySpace(string str, int l, int r,vector<string>& keySpace)
{
    int i;
    if(l==r)
    {
        cout<<str<<endl;
        keySpace.push_back(str);
    }
    else
    {
        for(i=l;i<=r;i++)
        {
            swap(str[l], str[i]);
            computeKeySpace(str,l+1,r,keySpace);
            swap(str[l], str[i]);
        }
    }
}

int main()
{
    int i,n;
    fstream fs;
    vector<string> keySpace;
    string text;
    string uniq="";
    string key;
    string cipher="";

    //i.    Take input from file
    ifstream in( "plaintext.txt" );
    in>>text;                               //Taking input from file
    cout<<"Plain text : "<<text<<endl;

    //ii.   Compute Key Space
    n=text.length();
    for(i=0;i<n;i++)
        if(uniq.find(text[i])==-1)
            uniq.append(1,text[i]);
    cout<<"Unique Set : {"<<uniq<<"}"<<endl;
    cout<<"KEY SPACE : "<<endl;
    computeKeySpace(uniq,0,uniq.length()-1,keySpace);

    //iii.  Encryption
    srand(time(NULL));
    key=keySpace[rand()%keySpace.size()];   //Randomly select key from key space
    cout<<"Chosen Key : "<<key<<endl;
    for(i=0;i<n;i++)
    {
        cipher.append(1,key[uniq.find(text[i])]);
    }
    cout<<"Cipher Text : "<<cipher<<endl;
    ofstream out("cipher.txt");
    out<<cipher;

    //iv.   Calculate Frequency of Occurences of each alphabet
    int freq[uniq.length()];
    for(i=0;i<uniq.length();i++)
        freq[i]=0;                          //Initialise frequency to zero
    for(i=0;i<n;i++)
        freq[uniq.find(text[i])]++;
                                            //Display Frequency
    cout<<"FREQ\tPLAIN\tCIPHER"<<endl;
    for(i=0;i<uniq.length();i++)
        cout<<freq[i]<<"\t"<<uniq[i]<<"\t"<<key[i]<<endl;

    //Ext   Brute Force Attack
    string decipher;
    int j;
    for(i=0;i<keySpace.size();i++)
    {
        decipher="";
        for(j=0;j<cipher.length();j++)
            decipher.append(1,keySpace[i][uniq.find(cipher[j])]);
        if(decipher==text)
        {
            cout<<"Brute Force Hits : "<<i+1<<endl;
            break;
        }
    }

    return 0;
}
