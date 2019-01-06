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
const int N=101;
const int K=1e5+5;
const int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
int main()
{
    int n,k;
    scanf("%i %i",&n,&k);
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)
        cin >> a[i];
    int dp[n+1][k+1];
    dp[0][0]=1;
    for(int i=1;i<=k;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        int sums[k+1];
        sums[0]=dp[i-1][0];
        for(int j=1;j<=k;j++)
        {
            sums[j]=add(sums[j-1],dp[i-1][j]);
        }
        for(int j=0;j<=k;j++)
        {
            int tr=sums[j];
            int bottom=j-a[i]-1;
            if(bottom>=0)
                tr=sub(tr,sums[bottom]);
            dp[i][j]=tr;
        }
    }
    printf("%i\n",dp[n][k]);
    return 0;
}
