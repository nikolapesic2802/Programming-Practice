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

const int N=1e4+5,L=15;
vector<int> par(N);
int find(int tr)
{
    if(tr==par[tr])
        return tr;
    return par[tr]=find(par[tr]);
}
void merge(int a,int b)
{
    a=find(a);
    b=find(b);
    par[a]=b;
}
vector<vector<pair<int,int> > > graf(N);
vector<int> depth(N),level(N);
int up[N][L];
void dfs(int tr)
{
    for(auto p:graf[tr])
        if(!depth[p.f])
            depth[p.f]=depth[tr]+p.s,up[p.f][0]=tr,level[p.f]=level[tr]+1,dfs(p.f);
}
int lca(int a,int b)
{
    if(level[a]<level[b])
        swap(a,b);
    for(int j=L-1;j>=0;j--)
        if(level[a]-level[b]>=(1<<j))
            a=up[a][j];
    if(a==b)
        return a;
    for(int j=L-1;j>=0;j--)
        if(up[a][j]!=up[b][j])
            a=up[a][j],b=up[b][j];
    return up[a][0];
}
int main()
{
    for(int i=0;i<N;i++)
        par[i]=i;
    int n,m;
    scanf("%i %i",&n,&m);
    vector<pair<int,pair<int,int> > > edges,unused;
	for(int i=0;i<m;i++)
    {
        int a,b,l;
        scanf("%i %i %i",&a,&b,&l);
        a--;b--;
        edges.pb({l,{a,b}});
    }
    sort(all(edges));
    for(auto p:edges)
        if(find(p.s.f)!=find(p.s.s))
            merge(p.s.f,p.s.s),graf[p.s.f].pb({p.s.s,p.f}),graf[p.s.s].pb({p.s.f,p.f});
        else
            unused.pb(p);
    depth[0]=level[0]=1;
    up[0][0]=0;
    dfs(0);
    for(int j=1;j<L;j++)
        for(int i=0;i<n;i++)
            up[i][j]=up[up[i][j-1]][j-1];
    int sol=INT_MAX;
    for(auto p:unused)
        sol=min(sol,depth[p.s.f]+depth[p.s.s]-2*depth[lca(p.s.f,p.s.s)]+p.f);
    if(sol==INT_MAX)
        assert(0);
    printf("%i\n",sol);
    return 0;
}
