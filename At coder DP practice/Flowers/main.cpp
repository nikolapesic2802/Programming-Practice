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
int N=2e5+5;
vector<ll> fen(N);
void add(int i,ll a)
{
    for(;i<N;i+=i&(-i))
    {
        fen[i]=max(fen[i],a);
    }
}
ll get(int i)
{
    ll m=0;
    for(;i;i-=i&(-i))
        m=max(m,fen[i]);
    return m;
}
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> hh(n);
    vector<ll> aa(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&hh[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&aa[i]);
    }
    for(int i=0;i<n;i++)
    {
        int h=hh[i];
        ll a=aa[i];
        ll best=get(h-1);
        add(h,(ll)a+best);
    }
    printf("%lld\n",get(n));
    return 0;
}
