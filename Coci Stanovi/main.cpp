/*
    -We first need to notice that its optimal to make either a horizontal or a vertical cut when dividing the rectangle so this gives us an easy n^3 dp solution.
    -But there is this requirement that all the smaller rectangles share an edge with the starting rectangle.
    -The easiest way to keep track of this is to make 4 more dimensions of size 2 to keep track if that side of the current rectangle is shared with the starting one.
    -This approach gets TLE and we need to optimize it. We can do this by noticing that if we look at the left and right edge(or top and bottom) and only one of them shares a side with the starting rectangle,
    it doesn't matter which one, This allows us to use only 2 extra dimensions of size 3 instead of 4 dimensions of size 2. This nearly doubles the speed and allows the program to pass.
    -We can also only look at states where n<m to further cut the speed of the program.
*/
#include <bits/stdc++.h>

#define ll long long

using namespace std;

int k;
ll dp[301][301][3][3];
ll calc(int n,int m,int a1,int a2)
{
	if(dp[n][m][a1][a2]!=-1)
        return dp[n][m][a1][a2];
    if(n>m)
        return dp[n][m][a1][a2]=calc(m,n,a2,a1);
    dp[n][m][a1][a2]=(ll)(k-n*m)*(k-n*m);
    if(n*m<=k)
		return dp[n][m][a1][a2];
	if(a1||(a2==2))
	{
		for(int i=1;i<n;i++)
		{
			ll a;
			if(a2==0)
                a=calc(i,m,a1,0)+calc(n-i,m,a1,0);
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
			ll a;
			if(a1==0)
                a=calc(n,i,0,a2)+calc(n,m-i,0,a2);
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
	memset(dp,-1,sizeof(dp));
	int n,m;
	scanf("%i %i %i",&n,&m,&k);
	printf("%lld",calc(n,m,2,2));
}
