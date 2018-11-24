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
const int Li=8005;
const ll inf=LLONG_MAX/2;
const int G=805;
ll dp[G][Li];
ll pre[Li];
ll get(int l,int r)
{
    ll tr=pre[r]-pre[l-1];
    return tr*(ll)(r-l+1);
}
void calc(int d,int l,int r,int L,int R)
{
    if(l>r)
        return;
    int mid=(l+r)>>1;
    pair<ll,int> sol=mp(inf,0);
    for(int i=L;i<=min(mid,R);i++)
    {
        sol=min(sol,mp(dp[d-1][i-1]+get(i,mid),i));
    }
    dp[d][mid]=sol.first;
    calc(d,l,mid-1,L,sol.second);
    calc(d,mid+1,r,sol.second,R);
}
int main()
{
	int l,g;
	scanf("%i %i",&l,&g);
	for(int i=1;i<=l;i++)
    {
        scanf("%lld",&pre[i]);
        pre[i]+=(ll)pre[i-1];
    }
    for(int i=1;i<=l;i++)
        dp[0][i]=inf;
    for(int i=1;i<=g;i++)
        calc(i,1,l,1,l);
    printf("%lld\n",dp[g][l]);
    return 0;
}
