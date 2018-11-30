#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair

const int N = 200031;
int Him(int n,string st)
{
    int ar[N]={};
    int cnt=0;
    int ans=0;
    int L[N]={},R[N]={};
	for (int i=1;i<=n;i++){
		ar[i]=(st[i]=='G');
		cnt+=ar[i];
	}

	for (int i=1;i<=n;i++){
		L[i]=L[i-1]+1;
		if (ar[i]==0)
			L[i]=0;
	}

	for (int i=n;i>=1;--i){
		R[i]=R[i+1]+1;
		if (ar[i]==0)
			R[i]=0;
	}

	for (int i=1;i<=n;i++){
		ans=max(ans,L[i]);
		ans=max(ans,L[i-1]+R[i+1]+1);
	}
	ans=min(ans,cnt);
	return ans;
}
int Tadija(int n,string s)
{
    int l[N]={},r[N]={};
	int i;
	for(i=1;i<=n;i++)
	{
		if(s[i]=='G') l[i]=l[i-1]+1;
		else l[i]=0;
	}
	int cnt=0;
	for(i=n;i>=1;i--)
	{
		if(s[i]=='G') r[i]=r[i+1]+1,cnt++;
		else r[i]=0;
	}
	int ans=0;
    for(i=1;i<=n;i++)
	{
		ans=max(ans,l[i]+1);
		if(l[i]==0) ans=max(ans,l[i-1]+r[i+1]+1);
	}
	ans=min(ans,cnt);
	return ans;
}
int main()
{
    while(true)
    {
        int n=rand()%10000;
        string s=" ";
        for(int i=0;i<n;i++)
        {
            int a=rand()%2;
            if(a)
                s+="G";
            else
                s+="S";
        }
        if(Tadija(n,s)!=Him(n,s))
        {
            //printf("%i %i\n",Tadija(n,s),Him(n,s));
            printf("%i\n",n);
            cout << s;
            exit(0);
        }
    }
}
