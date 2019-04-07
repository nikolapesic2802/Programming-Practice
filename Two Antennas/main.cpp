/*
    -https://codeforces.com/blog/entry/66022?#comment-500622
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

const int N=2e5+5,oo=INT_MAX;
vector<pair<int,pair<int,int> > > antene(N);
vector<ll> solq(N,-1);
struct segTree{
    vector<ll> c,d,lazy;
    void init()
    {
        c.clear();
        d.clear();
        lazy.clear();
        c.resize(4*N,-oo);
        d.resize(4*N,-1);
        lazy.resize(4*N,oo);
    }
    void prop(int i)
    {
        if(lazy[i]==oo)
            return;
        d[2*i]=max(d[2*i],c[2*i]-lazy[i]);
        d[2*i+1]=max(d[2*i+1],c[2*i+1]-lazy[i]);
        lazy[2*i]=min(lazy[2*i],lazy[i]);
        lazy[2*i+1]=min(lazy[2*i+1],lazy[i]);
        lazy[i]=oo;
    }
    void upd(int i)
    {
        d[i]=max(d[2*i],d[2*i+1]);
        c[i]=max(c[2*i],c[2*i+1]);
    }
    void update(int qs,int qe,ll h,int l=0,int r=N-1,int i=1)
    {
        if(qs>qe)
            return;
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            d[i]=max(d[i],c[i]-h);
            lazy[i]=min(h,lazy[i]);
            return;
        }
        prop(i);
        int m=(l+r)>>1;
        update(qs,qe,h,l,m,2*i);
        update(qs,qe,h,m+1,r,2*i+1);
        upd(i);
    }
    ll get(int qs,int qe,int l=0,int r=N-1,int i=1)
    {
        if(qs>r||qe<l)
            return -1;
        if(qs<=l&&qe>=r)
            return d[i];
        prop(i);
        int m=(l+r)>>1;
        return max(get(qs,qe,l,m,2*i),get(qs,qe,m+1,r,2*i+1));
    }
    void set(int pos,ll val,int l=0,int r=N-1,int i=1)
    {
        if(l>pos||r<pos)
            return;
        if(l==pos&&r==pos)
        {
            c[i]=val;
            return;
        }
        prop(i);
        int m=(l+r)>>1;
        set(pos,val,l,m,2*i);
        set(pos,val,m+1,r,2*i+1);
        upd(i);
    }
}st;
int main()
{
	int n;
	scanf("%i",&n);
	vector<pair<int,pair<int,int> > > events1,events2;
	for(int i=0;i<n;i++)
    {
        int h,a,b;
        scanf("%i %i %i",&h,&a,&b);
        antene[i].f=h;
        antene[i].s.f=a;
        antene[i].s.s=b;
        events1.pb({i+a,{-2,i}});
        events1.pb({i,{-1,i}});
        events1.pb({i+b,{N,i}});

        events2.pb({i,{N,i}});
        events2.pb({i-a,{N+1,i}});
        events2.pb({i-b,{-1,i}});
    }
    int q;
    scanf("%i",&q);
    for(int i=0;i<q;i++)
    {
        int l,r;
        scanf("%i %i",&l,&r);
        l--;r--;
        events1.pb({r,{l,i}});
        events2.pb({l,{r,i}});
    }
    sort(all(events1));
    sort(all(events2));
    reverse(all(events2));
    st.init();
    for(auto p:events1)
    {
        if(p.s.f==-2)
        {
            st.set(p.s.s,antene[p.s.s].f);
            continue;
        }
        if(p.s.f==-1)
        {
            st.update(max(p.s.s-antene[p.s.s].s.s,0),p.s.s-antene[p.s.s].s.f,antene[p.s.s].f);
            continue;
        }
        if(p.s.f==N)
        {
            st.set(p.s.s,-oo);
            continue;
        }
        int i=p.s.s;
        solq[i]=max(solq[i],st.get(p.s.f,p.f));
    }
    st.init();
    for(auto p:events2)
    {
        if(p.s.f==N+1)
        {
            st.set(p.s.s,antene[p.s.s].f);
            continue;
        }
        if(p.s.f==N)
        {
            st.update(p.s.s+antene[p.s.s].s.f,min(p.s.s+antene[p.s.s].s.s,n-1),antene[p.s.s].f);
            continue;
        }
        if(p.s.f==-1)
        {
            st.set(p.s.s,-oo);
            continue;
        }
        int i=p.s.s;
        solq[i]=max(solq[i],st.get(p.f,p.s.f));
    }
    for(int i=0;i<q;i++)
        printf("%i\n",solq[i]);
    return 0;
}
