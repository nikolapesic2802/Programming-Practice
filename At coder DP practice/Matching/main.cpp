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
const int N=21;
vector<vector<int> > graf(N);
const int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int dp[(1<<N)];
int calc(int tr)
{
    if(dp[tr]!=-1)
        return dp[tr];
    int n=__builtin_popcount(tr);
    if(n==0)
        return dp[tr]=1;
    n--;
    dp[tr]=0;
    for(auto p:graf[n])
    {
        if(tr&(1<<p))
        {
            int nx=tr^(1<<p);
            dp[tr]=add(dp[tr],calc(nx));
        }
    }
    return dp[tr];
}
int main()
{
    for(int i=0;i<(1<<N);i++)
        dp[i]=-1;
    int n;
    scanf("%i",&n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int a;
            scanf("%i",&a);
            if(a==1)
                graf[i].pb(j);
        }
    }
    printf("%i\n",calc((1<<n)-1));
    return 0;
}
