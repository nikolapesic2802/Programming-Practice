/*
    -Calculate the distance between every pair of points {1,2,3,...,k+1,n} by running dijkstra k+2 times.
    -Then do bitmask dp to find the shortest path.
    -It requires a memory optimization to use less than O(k*2^k) memory.
    -This can be done by noticing that the last visited will always be a 1 in the bitmask and not memorise it in the state and therefore use O(k*2^(k-1)) memory which is enough.
*/
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
const int N=2e4+5,oo=INT_MAX/2;
vector<vector<pair<int,int> > > graf(N);
vector<int> dist(N),distEnd(N);
int u[20][20];
vector<int> no(21);
int n,m,k;
void calcDist(int tr)
{
    fill(all(dist),INT_MAX);
    dist[tr]=0;
    set<pair<int,int> > s;
    s.insert({0,tr});
    int cnt=0;
    while(s.size())
    {
        pair<int,int> t=*s.begin();
        s.erase(s.begin());
        if(t.f>dist[t.s])
            continue;
        cnt++;
        for(auto p:graf[t.s])
            if(dist[p.f]>t.f+p.s)
                dist[p.f]=t.f+p.s,s.insert({dist[p.f],p.f});
    }
}
int shrink(int mask,int last)
{
    int i=(1<<last)-1;
    int t=mask&i;
    mask>>=last+1;
    mask<<=last;
    mask+=t;
    return mask;
}
int calc(int last,int mask)
{
    int msk=shrink(mask,last);
    if(mask==(1<<k)-1)
        return distEnd[last+1];
    if(dp[last][msk]!=-1)
        return dp[last][msk];
    dp[last][msk]=oo;
    for(int i=0;i<k;i++)
    {
        if(i==last)
            continue;
        if(mask&(1<<i))
            continue;
        if((mask&no[i])!=no[i])
            continue;
        int sol=calc(i,mask|(1<<i));
        if((ll)sol+u[last][i]<oo)
            dp[last][msk]=min(dp[last][msk],u[last][i]+sol);
    }
    return dp[last][msk];
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
        no[s]|=1<<r;
    }
    int sol=INT_MAX;
    if(k==0)
        sol=dist[n-1];
    for(int i=0;i<k;i++)
        if(no[i]==0){
            int tr=calc(i,1<<i);
            if((ll)tr+dist[i+1]<oo)
                sol=min(sol,dist[i+1]+tr);
        }
    printf("%i\n",sol);
    return 0;
}
