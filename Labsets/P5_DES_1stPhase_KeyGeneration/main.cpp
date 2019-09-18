#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int PC1[] = {
   57, 49, 41, 33, 25, 17, 9,
   1, 58, 50, 42, 34, 26, 18,
   10, 2, 59, 51, 43, 35, 27,
   19, 11, 3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
   14, 6, 61, 53, 45, 37, 29,
   21, 13, 5, 28, 20, 12, 4};

int PC2[] = {
   14, 17, 11, 24, 1, 5, 3, 28,
   15, 6, 21, 10, 23, 19, 12, 4,
   26, 8, 16, 7, 27, 20, 13, 2,
   41, 52, 31, 37, 47, 55, 30, 40,
   51, 45, 33, 48, 44, 49, 39, 56,
   34, 53, 46, 42, 50, 36, 29, 32};

int shiftTable[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

string compPC1(string key)
{
    string res="";
    for(int i=0;i<56;i++)
        res+=key[PC1[i]-1];
    return res;
}

string compPC2(string key)
{
    string res="";
    for(int i=0;i<48;i++)
        res+=key[PC2[i]-1];
    return res;
}

int main()
{
    ofstream fout("keys.txt");
    unsigned long long hexkey=0x133457799bbcdff1;
    string C,D;
    cout<<"Enter 64 bit key (in hex) : " ;cin>>hex>>hexkey;
    // Convert hex to bin
    string key=bitset<64>(hexkey).to_string() ;
    // Compute PC1
    key=compPC1(key);
    C=key.substr(0,28) , D=key.substr(28,28);
    for(int i=0;i<16;i++)
    {
        //Left Shift
        C=C.substr(shiftTable[i],28-shiftTable[i]) + C.substr(0,shiftTable[i]);
        D=D.substr(shiftTable[i],28-shiftTable[i]) + D.substr(0,shiftTable[i]);
        // Compute PC2
        key=compPC2(C+D);
        cout<<"Key "<<i+1<<" : "<<key<<endl;
        fout<<key<<endl;
    }
    fout.close();
    return 0;
}
