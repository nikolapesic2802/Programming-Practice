/*
    -When k*(k+1)>=n, the answer is always "DA". So, we need to calculate the answer only when k<20. This allows for an exponential algorithm to pass in time.
    -Notice that its always optimal to block 1 node for every depth from [1,k](on the first move a node on depth 1, on the second a node on depth 2 and so on)
    -For every node calculate which interval of nodes of depth k it will cover(relabel the nodes at depth k according to their position in the euler tour) and at which depth the node is.
    -We need to check if its possible to select k of these intervals(one at each depth) such that they cover all the nodes at depth k.
    -This can be done with dp in O(2^k*n)
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;

int n,k;
vector<vector<int> > dp,graf;
vector<vector<pair<int,int> > > nxt;
vector<int> in;
int t=0;
void init(int tr,int par,int d)
{
    in[tr]=t;
    if(d==k)
        t++;
    if(d!=k)
        for(auto p:graf[tr])
        {
            if(p==par)
                continue;
            init(p,tr,d+1);
        }
    if(t>in[tr]&&d!=0)
        nxt[in[tr]].pb({t,d-1});
}
bool calc(int mask,int tr)
{
    if(tr==t)
        return true;
    if(dp[mask][tr]!=-1)
        return dp[mask][tr];
    for(auto p:nxt[tr])
        if((mask&(1<<p.s))==0)
            if(calc(mask|(1<<p.s),p.f))
                return dp[mask][tr]=1;
    return dp[mask][tr]=0;
}
int main()
{
	scanf("%i %i",&n,&k);
	graf.resize(n);in.resize(n);nxt.resize(n);
	for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;b--;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    if(k*(k+1)>=n)
    {
        printf("DA\n");
        return 0;
    }
    init(0,-1,0);
    dp.resize(1<<k,vector<int>(t,-1));
    if(calc(0,0))
        printf("DA\n");
    else
        printf("NE\n");
    return 0;
}
