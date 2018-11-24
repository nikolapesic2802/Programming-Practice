#include <bits/stdc++.h>

#define ll long long
#define mp make_pair

using namespace std;
const ll inf=LLONG_MAX/2;
const int N=1e5+5;
ll cost[N],dp[12][N];
int w[N],sum[N];
ll get(int l,int r)
{
    r++;
    ll tr=cost[l];
    tr-=cost[r];
    tr-=(ll)(r-l)*sum[r];
    return tr;
}
void calc(int d,int l,int r,int L,int R)
{
    if(l>r)
        return;
    int mid=(l+r)>>1;
    pair<ll,int> sol=mp(inf,0);
    for(int i=L;i<=min(mid-1,R);i++)
    {
        sol=min(sol,mp(dp[d-1][i]+get(i+1,mid),i));
    }
    dp[d][mid]=sol.first;
    calc(d,l,mid-1,L,sol.second);
    calc(d,mid+1,r,sol.second,R);
}
int main()
{
    int n,k;
    scanf("%i %i",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%i",&w[i]);
    sum[n]=w[n];
    for(int i=n-1;i>=1;i--)
    {
        cost[i]=(ll)cost[i+1]+sum[i+1];
        sum[i]=sum[i+1]+w[i];
    }
    for(int i=1;i<=n;i++)
        dp[0][i]=inf;
    for(int i=1;i<=k;i++)
        calc(i,1,n,0,n);
    printf("%lld\n",dp[k][n]);
    return 0;
}
