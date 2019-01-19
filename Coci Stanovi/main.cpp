#include <bits/stdc++.h>

#define ll long long

using namespace std;

int k;
ll dp[301][301][3][3];
ll calc(int n,int m,int a1,int a2)
{
	if(n*m<=k)
		return (ll)(k-n*m)*(k-n*m);
	if(dp[n][m][a1][a2]!=-1)
        return dp[n][m][a1][a2];
    dp[n][m][a1][a2]=(ll)(k-n*m)*(k-n*m);
	if(a1||(a2==2))
	{
		for(int i=1;i<n;i++)
		{
			int a;
			if(a2==0)
                a=calc(i,m,a1,a2)+calc(n-i,m,a1,a2);
            if(a2==1)
                a=calc(i,m,a1,1)+calc(n-i,m,a1,0);
            if(a2==2)
                a=calc(i,m,a1,1)+calc(n-i,m,a1,1);
			if(a<dp[n][m][a1][a2])
			dp[n][m][a1][a2]=a;
		}
	}
	if(a2||(a1==2))
	{
		for(int i=1;i<m;i++)
		{
			int a;
			if(a1==0)
                a=calc(n,i,a1,a2)+calc(n,m-i,a1,a2);
            if(a1==1)
                a=calc(n,i,0,a2)+calc(n,m-i,1,a2);
            if(a1==2)
                a=calc(n,i,1,a2)+calc(n,m-i,1,a2);
			if(a<dp[n][m][a1][a2])
                dp[n][m][a1][a2]=a;
		}
	}
	return dp[n][m][a1][a2];
}
int main()
{
    int o=0;
    for(int i=1;i<301;i++)
        for(int j=1;j<301;j++)
            o+=(i+j)*9;
    cout << o;
	memset(dp,-1,sizeof(dp));
	int n,m;
	scanf("%i %i %i",&n,&m,&k);
	printf("%lld",calc(n,m,2,2));
}
