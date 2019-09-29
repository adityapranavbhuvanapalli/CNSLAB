#include <iostream>
using namespace std;

int key[3][3], C[1000][3]={0};

int fnDet(int a[3][3], int n)
{
    if(n==2)
        return a[0][0]*a[1][1] - a[0][1]*a[1][0];
	else if (n==3)
		return a[0][0]*(a[1][1]*a[2][2]-a[1][2]*a[2][1]) - a[0][1]*(a[1][0]*a[2][2]-a[2][0]*a[1][2]) + a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);
	else return 0;
}

int mod26(int r){ return r>=0?(r%26):mod26(r+26); }

int fnDetInv(int r , int d = 26)
{
    int i=0, p[100], q[100], t;
    if(d%r==0) return 1;
    do
    {
        t=d;
        q[i]=d/r;
        d=r , r=t%r;
        if(i==0 || i==1) p[i]=i;
        else
            p[i]=mod26(p[i-2]-p[i-1]*q[i-2]);
        i++;
    } while(r!=0);
    return mod26(p[i-2]-p[i-1]*q[i-2]);
}

void matrixMultiply(int a[1000][3], int m1, int n1, int b[1000][3], int m2, int n2, int res[1000][3])
{
	for(int i=0 ;i<m1 ;i++)
	{
		for(int j=0 ;j<n2 ;j++)
		{
			for(int k = 0 ; k<n1 ;k++)
				res[i][j]+=(a[i][k]*b[k][j]);
			res[i][j] = mod26(res[i][j]);
		}
	}
}

void matrixInverse(int a[3][3], int n, int invDet, int inv[3][3] )
{
	if(n==2)
        inv[0][0]=a[1][1] , inv[1][1]=a[0][0] , inv[0][1]=-a[0][1] , inv[1][0]=-a[1][0];
	else
	{
	    //Note: MEFM is the matrix from eliminating 1st row and col from 5x5 matrix
	    //MEFM :1201 --F-First(0), M-Middle(1), E-End(2) -- 0,1,2 are indices.
	    int mefm[4][4],t[4]={1,2,0,1};
	    for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                mefm[i][j]=a[t[i]][t[j]];

        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                inv[j][i]=mod26(mefm[i][j]*mefm[i+1][j+1]-mefm[i+1][j]*mefm[i][j+1]);
	}
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
            inv[i][j] = mod26(inv[i][j]*invDet);
}

string encrypt(string text, int n)
{
    //C=PK
    int P[1000][3]={0}, k=0;
    if(text.length()%n!=0)
        text.append(n-text.length()%n,'x'); //Appending 'x' to text n-m%n times (m - text length)
    for(int i=0; i<text.length()/n; i++)
        for(int j=0; j<n; j++)
            P[i][j]=text[k++]-'a';
    matrixMultiply(P, text.length()/n, n, key, n, n, C);

    string cipher="";
    for(int i=0; i<text.length()/n; i++)
        for(int j=0; j<n; j++)
            cipher+= (C[i][j]+'a');
    return cipher;
}

string decrypt(string cipher, int n)
{
    //P=C*inv(K)
    int P[1000][3]={0};
    int invK[3][3];
    matrixInverse(key, n, fnDet(key,n), invK);
    matrixMultiply(C, cipher.length()/n, n, invK, n, n, P);
    string text="";
    for(int i=0; i<cipher.length()/n; i++)
        for(int j=0; j<n; j++)
            text+=(P[i][j]+'a');
    return text;
}

int main()
{
    int n;
    string text;
    cout<<"Enter plain text         : "; cin>>text;
    cout<<"Enter order of keymatrix : "; cin>>n;
    cout<<"Enter key matrix : " <<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>key[i][j] ;
    string cipher=encrypt(text,n);
    cout<<"Plain text       : "<<text<<endl;
    cout<<"Cipher text      : "<<cipher<<endl;
    cout<<"Decrypted text   : "<<decrypt(cipher,n)<<endl;
    return 0;
}
