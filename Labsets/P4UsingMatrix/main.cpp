#include <iostream>
using namespace std;
int main()
{
	string key,key2;
	string msg;
	string cipher="";
	string decipher="";
	cout<<"Enter the message    : "; cin>>msg;
	cout<<"Enter the key        : "; cin>>key;
	int n=msg.length();
	int m=key.length();
	if(n%m!=0) msg.append(m-n%m,'x');
	n=msg.length();
	int z=n/m;
	char matrix[z][m];
	int k=0;

	//Encryption
	for(int i=0;i<z;i++)
		for(int j=0;j<m;j++)
			matrix[i][j]=msg[k++];

	for(int i=1;i<=m;i++)
		for(int j=0;j<z;j++)
			cipher.append(1,matrix[j][key.find(i+48)]);
    cout<<endl;
	cout<<"Cipher text is       : "<<cipher<<endl;

	//Decryption
	k=0;
	for(int i=1;i<=m;i++)
		for(int j=0;j<z;j++)
			matrix[j][key.find(i+48)]=cipher[k++];

	for(int i=0;i<z;i++)
		for(int j=0;j<m;j++)
			decipher.append(1,matrix[i][j]);

	cout<<"Decipher text is     : "<<decipher<<endl;
	return 0;
}
