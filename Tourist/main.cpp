#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int dp[20][1<<19];
const int N=2e4+5,L=(1<<19)-1;
vector<vector<pair<int,int> > > graf(N);
vector<int> dist(N),distEnd(N);
int u[20][20];
vector<vector<int> > no(N);
void calcDist(int tr)
{
    fill(all(dist),INT_MAX);
    dist[tr]=0;
    set<pair<int,int> > s;
    s.insert({tr,0});
    while(s.size())
    {
        pair<int,int> t=*s.begin();
        s.erase(s.begin());
        if(t.s>dist[t.f])
            continue;
        for(auto p:graf[t.f])
            if(dist[p.f]>t.s+p.s)
                dist[p.f]=t.s+p.s,s.insert({p.f,dist[p.f]});
    }
}
int n,m,k;
int calc(int last,int mask)
{
    if(mask==(1<<k)-1)
        return distEnd[last+1];
    if(dp[last][mask]!=-1)
        return dp[last][mask];
    dp[last][mask]=INT_MAX/2;
    for(int i=0;i<k;i++)
    {
        if(mask&(1<<i))
            continue;
        bool moze=false;
        for(auto p:no[i])
            if((mask&(1<<p))==0)
            {
                moze=true;
                break;
            }
        if(moze)
            continue;
        dp[last][mask]=min(dp[last][mask],u[last][i]+calc(i,mask|(1<<i)));
    }
    return dp[last][mask];
}
int main()
{
    memset(dp,-1,sizeof(dp));
    scanf("%i %i %i",&n,&m,&k);
    for(int i=0;i<m;i++)
    {
        int a,b,g;
        scanf("%i %i %i",&a,&b,&g);
        a--;b--;
        graf[a].pb({b,g});
        graf[b].pb({a,g});
    }
    for(int i=1;i<=k;i++){
        calcDist(i);
        for(int j=1;j<=k;j++)
            u[i-1][j-1]=dist[j];
    }
    calcDist(n-1);
    distEnd=dist;
    calcDist(0);
    int g;
    scanf("%i",&g);
    for(int i=0;i<g;i++)
    {
        int r,s;
        scanf("%i %i",&r,&s);
        r-=2;
        s-=2;
        no[s].pb(r);
    }
    int sol=INT_MAX;
    for(int i=0;i<k;i++)
        if(no[i].size()==0)
            sol=min(sol,dist[i+1]+calc(i,1<<i));
    printf("%i\n",sol);
    return 0;
}
