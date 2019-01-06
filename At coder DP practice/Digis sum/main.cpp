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
const int N=1e4+5;
int d;
vector<int> k;
int dp[N][101];
const int mod=1e9+7;
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
    b%=d;
    a-=b;
    if(a<0)
        a+=d;
    assert(a>=0&&a<d);
    return a;
}
int main()
{
    string s;
    cin >> s;
    int n=s.size();
    int sum=0;
    for(int i=0;i<n;i++)
        k.pb(s[i]-'0'),sum+=k.back();
    reverse(all(k));
    scanf("%i",&d);
    dp[0][0]=1;
    int ans=0;
    if(sum%d==0)
        ans++;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<d;j++)
        {
            for(int k=1;k<10;k++)
            {
                dp[i][j]=add(dp[i][j],dp[i-1][sub(j,k)]);
            }
        }
        ans=add(ans,dp[i][0]);
        //printf("%i %i\n",dp[i][0],ans);
        for(int j=0;j<d;j++)
        {
            dp[i][j]=add(dp[i][j],dp[i-1][j]);
        }
    }
    for(int i=0;i<n;i++)
    {
        //printf("%i %i\n",k[i],sum);
        sum-=k[i];
        for(int j=0;j<k[i];j++)
        {
            if(i==n-1&&j==0)
                continue;
            ans=add(ans,dp[i][sub(0,sum+j)]);
        }
    }
    printf("%i\n",ans);
    return 0;
}
