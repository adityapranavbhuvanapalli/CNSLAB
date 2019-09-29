#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
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
    vector<string> keySpace;
    string text;
    string uniq="";
    string key;
    string cipher="";

    //i.    Take input from file
    ifstream fin( "plaintext.txt" );
    fin>>text;                               //Taking input from file
    cout<<"Plain text : "<<text<<endl;
    fin.close();

    //ii.   Compute Key Space
    n=text.length();
    for(i=0;i<n;i++)
        if(uniq.find(text[i])==-1)
            uniq+=text[i];
    cout<<"Unique Set : {"<<uniq<<"}"<<endl;
    cout<<"KEY SPACE : "<<endl;
    computeKeySpace(uniq,0,uniq.length()-1,keySpace);

    //iii.  Encryption
    srand(time(NULL));
    key=keySpace[rand()%keySpace.size()];   //Randomly select key from key space
    cout<<"Chosen Key : "<<key<<endl;
    for(i=0;i<n;i++)
    {
        cipher+=key[uniq.find(text[i])];
    }
    cout<<"Cipher Text : "<<cipher<<endl;
    ofstream fout("cipher.txt");
    fout<<cipher;
    fout.close();
    //iv.   Calculate Frequency of Occurences of each alphabet
    int freq[uniq.length()];
    for(i=0;i<uniq.length();i++)
        freq[i]=0;                          //Initialise frequency to zero
    for(i=0;i<n;i++)
        freq[uniq.find(text[i])]++;
                                            //Display Frequency
    cout<<"FREQ\tPLAIN\tCIPHER"<<endl;
    for(i=0;i<uniq.length();i++)
        cout<<freq[i]*1.0/text.length()<<"\t"<<uniq[i]<<"\t"<<key[i]<<endl;

    // Extra :   Brute Force Attack (not needed for lab test)
    string decipher;
    int j;
    for(i=0;i<keySpace.size();i++)
    {
        decipher="";
        for(j=0;j<cipher.length();j++)
            decipher+=keySpace[i][uniq.find(cipher[j])];
        if(decipher==text)
        {
            cout<<"Brute Force Hits : "<<i+1<<endl;
            break;
        }
    }
    // End of Brute Force Attack
    return 0;
}
