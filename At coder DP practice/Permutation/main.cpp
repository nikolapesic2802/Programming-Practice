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
int dp[N][N];
int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int mul(int a,int b)
{
    return ((ll)a*b)%mod;
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
    int n;
    scanf("%i",&n);
    string s;
    cin >> s;
    s='0'+s;
    dp[0][1]=1;
    for(int i=1;i<n;i++)
    {
        vector<int> sums(N);
        sums[0]=dp[i-1][0];
        assert(sums[0]==0);
        for(int j=1;j<=n;j++)
            sums[j]=add(sums[j-1],dp[i-1][j]);
        for(int j=1;j<=i+1;j++)
        {
            if(s[i]=='>')
                dp[i][j]=sub(sums[n],sums[j-1]);
            else
                dp[i][j]=sums[j-1];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=add(ans,dp[n-1][i]);
    printf("%i\n",ans);
    return 0;
}
