/*
    -Sort the trapezoids according to the upper interval.
    -Sweep through the trapezoids and for each one we will have a suffix of trapezoids for which the upper interval doesn't intersect.
    -To deal with the bottom interval we will use a segment tree.
    -We can get an answer by querying on all the trapezoids that dont intersect on the upper interval and have the left value of the bottom interval larger than the right border of the current interval.
    -If we sort the trapezoids by the left border of the upper interval (like i did), we will need a persistent segment tree to get the answers but if we sort the by the right border we can do it with a regular segment tree.
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

const int N=1e5+5,mod=30013;
int n;
vector<pair<pair<int,int>,pair<int,int> > > t;
unsigned short add(unsigned short a,unsigned short b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
pair<int,unsigned short> merge(pair<int,unsigned short> a,pair<int,unsigned short> b)
{
    pair<int,unsigned short> sol={max(a.f,b.f),0};
    if(a.f==sol.f)
        sol.s=add(sol.s,a.s);
    if(b.f==sol.f)
        sol.s=add(sol.s,b.s);
    return sol;
}
struct node{
    pair<int,unsigned short> maxx;
    int l,r;
};
vector<node> drvo;
int newNode()
{
    node a;
    a.l=a.r=-1;
    drvo.pb(a);
    return drvo.size()-1;
}
int copyNode(int i)
{
    drvo.pb(drvo[i]);
    return drvo.size()-1;
}
vector<int> roots(N);
void build(int l=0,int r=N-1,int i=0)
{
    if(l==r)
    {
        if(l==N-1)
            drvo[i].maxx={0,1};
        return;
    }
    int a=newNode(),m=(l+r)>>1;
    drvo[i].l=a;
    build(l,m,a);
    a=newNode();
    drvo[i].r=a;
    build(m+1,r,a);
    drvo[i].maxx=merge(drvo[drvo[i].l].maxx,drvo[drvo[i].r].maxx);
}
int sett(int pos,pair<int,int> a,int i,int l=0,int r=N-1)
{
    if(l>pos||r<pos)
        return i;
    int tr=copyNode(i);
    if(l==r)
    {
        drvo[tr].maxx=merge(drvo[tr].maxx,a);
        return tr;
    }
    int m=(l+r)>>1;
    int aa=sett(pos,a,drvo[tr].l,l,m);
    drvo[tr].l=aa;
    aa=sett(pos,a,drvo[tr].r,m+1,r);
    drvo[tr].r=aa;
    drvo[tr].maxx=merge(drvo[drvo[tr].l].maxx,drvo[drvo[tr].r].maxx);
    return tr;
}
pair<int,int> get(int qs,int i,int qe=N-1,int l=0,int r=N-1)
{
    if(qs>r||qe<l)
        return {0,0};
    if(qs<=l&&qe>=r)
        return drvo[i].maxx;
    int m=(l+r)>>1;
    return merge(get(qs,drvo[i].l,qe,l,m),get(qs,drvo[i].r,qe,m+1,r));
}
int getRoot(int i)
{
    int l=i+1,r=n-1;
    while(l<r)
    {
        int m=(l+r)>>1;
        if(t[m].f.f>t[i].f.s)
            r=m;
        else
            l=m+1;
    }
    if(t[r].f.f<=t[i].f.s)
        return 0;
    return roots[r];
}
vector<int> y;
int find(int pos)
{
    int l=0,r=y.size()-1;
    while(l<r)
    {
        int m=(l+r)>>1;
        if(y[m]>pos)
            r=m;
        else
            l=m+1;
    }
    if(y[l]<=pos)
        return N-1;
    return l;
}
int main()
{
	scanf("%i",&n);
	t.resize(n);
	newNode();
	build();
	for(int i=0;i<n;i++)
        scanf("%i %i %i %i",&t[i].f.f,&t[i].f.s,&t[i].s.f,&t[i].s.s),y.pb(t[i].s.f);
    sort(all(y));
    y.erase(unique(all(y)),y.end());
    map<int,int> mapa;
    for(int i=0;i<(int)y.size();i++)
        mapa[y[i]]=i;
    for(auto &p:t)
        p.s.f=mapa[p.s.f];
    mapa.clear();
    sort(all(t));
    pair<int,int> sol={0,0};
    for(int ind=n-1;ind>=0;ind--)
    {
        int root=getRoot(ind);
        auto val=get(find(t[ind].s.s),root);
        val.f++;
        roots[ind]=sett(t[ind].s.f,val,roots[ind+1]);
        sol=merge(sol,val);
    }
    printf("%i %i\n",sol.f,sol.s);
    return 0;
}
