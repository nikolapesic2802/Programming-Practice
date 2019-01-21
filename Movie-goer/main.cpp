/*
    -Sweep from left to right saying if the current position is the right position of the interval we are taking, what is the optimal left border of the interval.
    -For every type of movie that is showing, we need to keep track of when we last had that movie and also the time before that, since when we get it again only taking a left border between the last occurrence and the current one will give us points for that movie.
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

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
int N;
struct segTree{
    vector<ll> lazy,m;
    void init()
    {
        lazy.resize(4*N);
        m.resize(4*N);
    }
    void prop(int i)
    {
        m[2*i]+=lazy[i];
        lazy[2*i]+=lazy[i];
        m[2*i+1]+=lazy[i];
        lazy[2*i+1]+=lazy[i];
        lazy[i]=0;
    }
    void update(int i)
    {
        m[i]=max(m[2*i],m[2*i+1]);
    }
    void add(int qs,int qe,ll x,int l=0,int r=N-1,int i=1)
    {
        if(qs>qe)
            return;
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            m[i]+=x;
            lazy[i]+=x;
            return;
        }
        int mi=(l+r)>>1;
        prop(i);
        add(qs,qe,x,l,mi,2*i);
        add(qs,qe,x,mi+1,r,2*i+1);
        update(i);
    }
}st;
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	vector<int> last(m),beforelast(m),movies(n+1),value(m);
	N=n+1;
	st.init();
	for(int i=1;i<=n;i++)
        scanf("%i",&movies[i]),movies[i]--;
    for(int i=0;i<m;i++)
        scanf("%i",&value[i]);
    ll sol=0;
    for(int i=1;i<movies.size();i++)
    {
        int a=movies[i];
        st.add(beforelast[a]+1,last[a],-1*value[a]);
        st.add(last[a]+1,i,value[a]);
        sol=max(sol,st.m[1]);
        beforelast[a]=last[a];
        last[a]=i;
    }
    printf("%lld\n",sol);
    return 0;
}
