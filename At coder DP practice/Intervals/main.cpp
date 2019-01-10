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

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=2e5+5;
vector<ll> update(N);
vector<vector<pair<int,ll> > > up(N);
vector<ll> dp(N);
struct segTree{
    vector<ll> maxx;
    vector<ll> lazy;
    void init()
    {
        maxx.resize(4*N);
        lazy.resize(4*N);
    }
    void prop(int i)
    {
        lazy[2*i]+=lazy[i];
        maxx[2*i]+=lazy[i];
        lazy[2*i+1]+=lazy[i];
        maxx[2*i+1]+=lazy[i];
        lazy[i]=0;
    }
    void update(int i)
    {
        maxx[i]=max(maxx[2*i],maxx[2*i+1]);
    }
    void add(int qs,int qe,ll val,int l=0,int r=N-1,int i=1)
    {
        if(qs>qe)
            return;
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            lazy[i]+=val;
            maxx[i]+=val;
            return;
        }
        prop(i);
        int m=(l+r)>>1;
        add(qs,qe,val,l,m,2*i);
        add(qs,qe,val,m+1,r,2*i+1);
        update(i);
    }
    ll get(int qs,int qe,int l=0,int r=N-1,int i=1)
    {
        if(qs>qe)
            return 0;
        if(qs>r||qe<l)
            return LLONG_MIN;
        if(qs<=l&&qe>=r)
            return maxx[i];
        prop(i);
        int m=(l+r)>>1;
        ll sol=max(get(qs,qe,l,m,2*i),get(qs,qe,m+1,r,2*i+1));
        update(i);
        return sol;
    }
}st;
int main()
{
    st.init();
    int n,m;
    scanf("%i %i",&n,&m);
    for(int i=0;i<m;i++)
    {
        int l,r,a;
        scanf("%i %i %i",&l,&r,&a);
        update[l]+=a;
        up[r+1].pb({l,-1*a});
    }
    ll sol=0;
    for(int i=1;i<=n;i++)
    {
        st.add(0,i-1,update[i]);
        for(auto p:up[i])
        {
            st.add(0,p.f-1,p.s);
        }
        dp[i]=st.get(0,i-1);
        sol=max(sol,dp[i]);
        st.add(i,i,dp[i]);
    }
    printf("%lld\n",sol);
    return 0;
}
