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
const int N=16,M=(1<<16);
ll dp[M];
int number[M];
vector<int> yes[N+1];
ll a[N][N];
ll sum[M];
int main()
{
    for(int i=0;i<M;i++)
        dp[i]=-1;
    sum[0]=0;
    dp[0]=0;
    int n;
    scanf("%i",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%lld",&a[i][j]);
    for(int i=0;i<(1<<n);i++)
    {
        int k=__builtin_popcount(i);
        yes[k].pb(i);
    }
    for(int i=1;i<=n;i++)
    {
        for(auto p:yes[i])
        {
            for(int j=0;j<n;j++)
            {
                if((1<<j)&p)
                {
                    sum[p]=sum[(1<<j)^p];
                    for(int l=j+1;l<n;l++)
                    {
                        if((1<<l)&p)
                        {
                            sum[p]+=a[j][l];
                        }
                    }
                    break;
                }
            }
        }
    }
    for(int i=1;i<(1<<n);i++)
        for(int j=i;j;j=(j-1)&i)
            dp[i]=max(dp[i],dp[i^j]+sum[j]);
    printf("%lld\n",dp[(1<<n)-1]);
    return 0;
}
