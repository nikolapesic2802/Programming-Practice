/*
    -Recursively calculate for every column and every k, how many ways are there to put k gases in the interval where that column is the lowers column(There will be only 1 interval)
*/

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
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int mod=1e9+7;
const int N=501,M=1e6;
vector<int> h(N),fact,inv;
int dp[N][N];
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int mul(int a,int b)
{
    return (ll)a*b%mod;
}
int powmod(int x,int k)
{
    int ans=1;
    for(;k;k>>=1,x=mul(x,x))
        if(k&1)
            ans=mul(ans,x);
    return ans;
}
int nCk(int n,int k)
{
    if(n<k||n<0||k<0)
        return 0;
    return mul(mul(fact[n],inv[k]),inv[n-k]);
}
int n,k;
int calc(int l,int r,int level)
{
    if(r<l)
        return n;
    int pos=l;
    for(int i=l;i<=r;i++)
        if(h[pos]>h[i])
            pos=i;
    int left=calc(l,pos-1,h[pos]);
    int right=calc(pos+1,r,h[pos]);
    vector<int> arr(k+1);
    for(int i=0;i<=k;i++)
        for(int j=0;j<=k&&i+j<=k;j++)
            arr[i+j]=add(arr[i+j],mul(dp[left][i],dp[right][j]));
    for(int i=0;i<=k;i++)
    {
        for(int j=0;j<=i&&j<=h[pos]-level;j++)
        {
            int sol=mul(fact[h[pos]-level],inv[h[pos]-level-j]);
            sol=mul(sol,nCk(r-l+1-i+j,j));
            sol=mul(sol,arr[i-j]);
            dp[pos][i]=add(dp[pos][i],sol);
        }
    }
    return pos;
}
int main()
{
    fact.pb(1);
    for(int i=1;i<M;i++)
        fact.pb(mul(fact.back(),i));
    for(auto p:fact)
        inv.pb(powmod(p,mod-2));
	scanf("%i %i",&n,&k);
	dp[n][0]=1;
	for(int i=0;i<n;i++)
        scanf("%i",&h[i]);
    int a=calc(0,n-1,0);
    printf("%i\n",dp[a][k]);
    return 0;
}
