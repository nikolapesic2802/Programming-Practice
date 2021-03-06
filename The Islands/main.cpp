/*
    -Maintain a segment tree with each field storing how many polygons(coastlines) cover it.
    -The answer will be the maximum number of polygons open on a field.
    -Sweep along the y axis (or x).
    -We only need to look at segments of the polygon parallel to the x axis.
    -For each one determine if it opens or closes a polygon (can be done by sweeping through those segments and maintaining a segment tree of which fields are covered)
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

const int N=2e5+5;
vector<int> maxx(4*N),lazy(4*N);
void add(int qs,int qe,int x,int l=0,int r=N-1,int i=1)
{
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        maxx[i]+=x;
        lazy[i]+=x;
        return;
    }
    maxx[2*i]+=lazy[i];
    maxx[2*i+1]+=lazy[i];
    lazy[2*i]+=lazy[i];
    lazy[2*i+1]+=lazy[i];
    lazy[i]=0;
    int m=(l+r)>>1;
    add(qs,qe,x,l,m,2*i);
    add(qs,qe,x,m+1,r,2*i+1);
    maxx[i]=max(maxx[2*i],maxx[2*i+1]);
}
void add2(int qs,int qe,int x,int l=0,int r=N-1,int i=1)
{
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        lazy[i]+=x;
        return;
    }
    lazy[2*i]+=lazy[i];
    lazy[2*i+1]+=lazy[i];
    lazy[i]=0;
    int m=(l+r)>>1;
    add2(qs,qe,x,l,m,2*i);
    add2(qs,qe,x,m+1,r,2*i+1);
}
int get(int pos,int l=0,int r=N-1,int i=1)
{
    if(r<pos||l>pos)
        return 0;
    if(l==pos&&l==r)
        return lazy[i];
    lazy[2*i]+=lazy[i];
    lazy[2*i+1]+=lazy[i];
    lazy[i]=0;
    int m=(l+r)>>1;
    return get(pos,l,m,2*i)+get(pos,m+1,r,2*i+1);
}
int main()
{
    int n;
    scanf("%i",&n);
    vector<pair<pair<int,int>,pair<int,int> > > q;
    for(int i=0;i<n;i++)
    {
        int k;
        scanf("%i",&k);
        vector<int> x(k);
        for(int j=0;j<k;j++)
            scanf("%i",&x[j]);
        vector<pair<int,int> > p;
        for(int j=0;j<k;j++)
            if(j%2)
                p.pb({x[(j+1)%k],x[j]});
            else
                p.pb({x[j],x[j+1]});
        vector<pair<int,pair<int,int> > > e;
        for(int j=0;j<k;j++)
            if(p[j].s==p[(j+1)%k].s)
                e.pb({p[j].s,{min(p[j].f,p[(j+1)%k].f),max(p[j].f,p[(j+1)%k].f)-1}});
        sort(all(e));
        vector<int> v;
        for(auto p:e)
            v.pb(p.s.f),v.pb(p.s.s);
        sort(all(v));
        v.erase(unique(all(v)),v.end());
        map<int,int> mapa;
        for(int i=0;i<(int)v.size();i++)
            mapa[v[i]]=i;
        for(auto p:e)
        {
            if(get(mapa[p.s.f]))
                add2(mapa[p.s.f],mapa[p.s.s],-1),q.pb({{p.f,-1},p.s});
            else
                add2(mapa[p.s.f],mapa[p.s.s],1),q.pb({{p.f,1},p.s});
        }
    }
    sort(all(q));
    vector<int> v;
    for(auto p:q)
        v.pb(p.s.f),v.pb(p.s.s);
    sort(all(v));
    v.erase(unique(all(v)),v.end());
    map<int,int> mapa;
    for(int i=0;i<(int)v.size();i++)
        mapa[v[i]]=i;
    for(auto &p:q)
        p.s.f=mapa[p.s.f],p.s.s=mapa[p.s.s];
    int sol=0;
    for(auto p:q)
        add(p.s.f,p.s.s,p.f.s),sol=max(sol,maxx[1]);
    printf("%i\n",sol);
    return 0;
}
