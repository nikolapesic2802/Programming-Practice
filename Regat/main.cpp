/*
    -Sort the nodes by the euler path values.
    -In a segment tree keep the distances to all nodes.
    -Answer queries by querying maximum multiple times.
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

const int N=1e5+1;
vector<vector<pair<int,int> > > graf(N);
vector<vector<int> > q(N);
vector<int> ans(N),in(N),out(N),par(N),maxx(4*N),lazy(4*N);
int t,offset;
vector<pair<int,int> > undo;
void prop(int i)
{
    maxx[2*i]+=lazy[i];
    maxx[2*i+1]+=lazy[i];
    lazy[2*i]+=lazy[i];
    lazy[2*i+1]+=lazy[i];
    lazy[i]=0;
}
void add(int qs,int qe,int x,int l=0,int r=N-1,int i=1)
{
    if(qs>r||qe<l||qs>qe)
        return;
    if(qs<=l&&qe>=r)
    {
        maxx[i]+=x;
        lazy[i]+=x;
        return;
    }
    if(lazy[i])
        prop(i);
    int m=(l+r)>>1;
    add(qs,qe,x,l,m,2*i);
    add(qs,qe,x,m+1,r,2*i+1);
    maxx[i]=max(maxx[2*i],maxx[2*i+1]);
}
int get(int l=0,int r=N-1,int i=1)
{
    if(l==r)
    {
        int sol=maxx[i];
        undo.pb({l,maxx[i]});
        add(l,l,-maxx[i]);
        return sol;
    }
    if(lazy[i])
        prop(i);
    int m=(l+r)>>1;
    if(maxx[2*i]>=maxx[2*i+1])
        return get(l,m,2*i);
    return get(m+1,r,2*i+1);
}
void dfs(int tr,int pa,int dist)
{
    in[tr]=t;
    add(t,t,dist);
    t++;
    for(auto p:graf[tr])
        if(p.f!=pa)
            dfs(p.f,tr,dist+p.s),par[p.f]=p.s;
    out[tr]=t-1;
}
void solve(int tr,int pa)
{
    for(auto p:q[tr])
        ans[p]=get()+offset;
    for(auto p:undo)
        add(p.f,p.f,p.s);
    undo.clear();
    for(auto p:graf[tr])
    {
        if(p.f==pa)
            continue;
        offset+=p.s;
        add(in[p.f],out[p.f],-2*p.s);
        solve(p.f,tr);
        offset-=p.s;
        add(in[p.f],out[p.f],2*p.s);
    }
}
int main()
{
    freopen("regat.in","r",stdin);
    freopen("regat.out","w",stdout);
	int n,m,a,b,c;
	scanf("%i %i",&n,&m);
	for(int i=1;i<n;i++)
        scanf("%i %i %i",&a,&b,&c),a--,b--,graf[a].pb({b,c}),graf[b].pb({a,c});
    for(int i=0;i<m;i++)
        scanf("%i",&a),a--,q[a].pb(i);
    dfs(0,-1,0);
    undo.clear();
    solve(0,-1);
    for(int i=0;i<m;i++)
        printf("%i\n",ans[i]);
    return 0;
}
