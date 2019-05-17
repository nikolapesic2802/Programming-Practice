/*
    -Simulate removing all the updates one by one and get the maximum for each one with a segment tree.
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

//7:17
int n,q;
struct segTree{
    vector<ll> maxx,lazy;
    void init()
    {
        maxx.resize(4*n);
        lazy.resize(4*n);
    }
    void prop(int i)
    {
        maxx[2*i]+=lazy[i];
        maxx[2*i+1]+=lazy[i];
        lazy[2*i]+=lazy[i];
        lazy[2*i+1]+=lazy[i];
        lazy[i]=0;
    }
    void update(int i)
    {
        maxx[i]=max(maxx[2*i],maxx[2*i+1]);
    }
    void set(int qs,int qe,int x,int l=0,int r=n-1,int i=1)
    {
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            lazy[i]+=x;
            maxx[i]+=x;
            return;
        }
        prop(i);
        int m=(l+r)>>1;
        set(qs,qe,x,l,m,2*i);
        set(qs,qe,x,m+1,r,2*i+1);
        update(i);
    }
}st;
int main()
{
    printf("WUT!\n");
	scanf("%i %i",&n,&q);
	st.init();
    vector<pair<pair<int,int>,int> > qq(q);
    for(int i=0;i<q;i++)
    {
        scanf("%i %i %i\n",&qq[i].f.f,&qq[i].f.s,&qq[i].s);
        st.set(qq[i].f.f,qq[i].f.s,qq[i].s);
    }
    ll sol=st.maxx[1];
    for(int i=0;i<q;i++)
    {
        st.set(qq[i].f.f,qq[i].f.s,qq[i].s*-1);
        sol=min(sol,st.maxx[1]);
        st.set(qq[i].f.f,qq[i].f.s,qq[i].s);
    }
    printf("%lld\n",sol);
    return 0;
}
