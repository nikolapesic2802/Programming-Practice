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
const int N=3e3+5;
vector<int> niz(N);
int n;
vector<vector<ll> > dp(N,vector<ll>(N,-1));
ll calc(int l,int r)
{
    if(l>r)
        return 0;
    if(dp[l][r]!=-1)
        return dp[l][r];
    int po=l+n-1-r;
    if(po%2==0)
    {
        return dp[l][r]=max(calc(l+1,r)+niz[l],calc(l,r-1)+niz[r]);
    }
    return dp[l][r]=min(calc(l+1,r)-niz[l],calc(l,r-1)-niz[r]);
}
int main()
{
    scanf("%i",&n);
    for(int i=0;i<n;i++)
        cin >> niz[i];
    printf("%lld\n",calc(0,n-1));
    return 0;
}
