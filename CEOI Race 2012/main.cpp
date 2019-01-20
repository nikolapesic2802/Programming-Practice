/*
    -We need 3 dp tables to figure out the answer:
    -dp1[l][r][a] - Max length of a path starting at l and ending at r, going in direction a.
    -dp2[l][r][a] - Max length of a path starting at l, visiting r and then continuing from r in the opposite direction(still in interval [l,r] and it can swap the direction multiple times)
    -dp3[l][r][a] - Max of dp2[l][l...r][a] : We need this to calculate the case where we have an intersection in O(n^3) and not O(n^4)
    -The case where there is no crossing can be solved using only the first 2 dps, the second case requires us to go though all the states of dp1, and for every one of them(if there is a path from l to r)
    we need to try to elongate it such that we only cross once at the starting segment.
*/
#include <bits/stdc++.h>

using namespace std;

const int N=501;
bool adj[N][N];
int dp1[N][N][2],dp2[N][N][2],dp3[N][N][2],b[N][2];
pair<int,int> ans;
void calc(int l,int r,int a)
{
    if(adj[l][r])
    {
        dp1[l][r][a]=1;
        dp2[l][r][a]=1+dp3[r][b[l][a]][a^1];
    }
    else
    {
        dp1[l][r][a]=dp2[l][r][a]=INT_MIN/2;
    }
    for(int k=b[l][a];k!=r;k=b[k][a])
    {
        dp1[l][r][a]=max(dp1[l][r][a],dp1[l][k][a]+dp1[k][r][a]);
        dp2[l][r][a]=max(dp2[l][r][a],dp1[l][k][a]+dp2[k][r][a]);
    }
    dp3[l][r][a]=max(dp3[l][b[r][a^1]][a],dp2[l][r][a]);
}
int main()
{
	int n,k;
	scanf("%i %i",&n,&k);
	for(int i=0;i<n;i++)
    {
        int t;
        scanf("%i",&t);
        while(t!=0)
        {
            adj[i][t-1]=true;
            scanf("%i",&t);
        }
        b[i][0]=(i+1)%n;
        b[i][1]=(i-1+n)%n;
    }
    for(int l=1;l<n;l++)
        for(int i=0;i<n;i++)
            calc(i,(i+l)%n,0),calc((i+l)%n,i,1);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int a=0;a<2;a++)
                ans=max(ans,make_pair(dp2[i][j][a],i));
    if(k)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int a=0;a<2;a++)
                    if(dp1[i][j][a]>0)
                    {
                        int k=b[j][a];
                        for(;k!=i;k=b[k][a])
                            if(adj[k][i])
                                break;
                        if(k!=i)
                            for(int l=b[k][a];l!=i;l=b[l][a])
                                if(adj[j][l])
                                    ans=max(ans,make_pair(max(dp3[l][b[i][a^1]][a],dp3[l][b[k][a]][a^1])+dp1[i][j][a]+2,k));
                    }
    }
    printf("%i\n%i\n",ans.first,ans.second+1);
    return 0;
}
