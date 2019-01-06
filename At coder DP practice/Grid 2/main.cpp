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
const int N=3005,mod=1e9+7;
int add(int x,int y)
{
    x+=y;
    if(x>=mod)
        x-=mod;
    return x;
}
int sub(int x,int y)
{
    x-=y;
    if(x<0)
        x+=mod;
    return x;
}
int mul(int a,int b)
{
    return ((ll)a*b)%mod;
}
int powmod(int x,int k) {int ans=1;for(;k;k>>=1,x=mul(x,x))if(k&1)ans=mul(ans,x);return ans;}
int inv(int i)
{
    return powmod(i,mod-2);
}
int dp[N];
const int l=2e5+5;
int fact[l];
int ways(int x,int y,int a,int b)
{
    x=abs(x-a);
    y=abs(y-b);
    int ans=mul(fact[x+y],inv(fact[x]));
    ans=mul(ans,inv(fact[y]));
    return ans;
}
vector<int> r[N];
vector<pair<int,int> > block;
int main()
{
    fact[0]=1;
    fact[1]=1;
    for(int i=2;i<l;i++)
        fact[i]=mul(fact[i-1],i);
    int n,m,k;
    scanf("%i %i %i",&n,&m,&k);
    block.pb({1,1});
    block.pb({n,m});
    for(int i=0;i<k;i++)
    {
        int x,y;
        scanf("%i %i",&x,&y);
        block.pb({x,y});
    }
    sort(all(block));
    n=block.size();
    dp[n-1]=1;
    //cout << block << endl;
    for(int i=1;i<n;i++)
    {
        dp[i]=ways(1,1,block[i].f,block[i].s);
    }
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(block[j].f>=block[i].f&&block[j].s>=block[i].s)
            {
                dp[j]=sub(dp[j],mul(dp[i],ways(block[i].f,block[i].s,block[j].f,block[j].s)));
            }
        }
    }
    printf("%i\n",dp[n-1]);
    return 0;
}
