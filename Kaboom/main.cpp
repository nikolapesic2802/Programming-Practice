/*
    -Do DP[a][n] as the number of ways to fold a strip such that the first a cells are explosive and the n next ones are not such that we need to end up with the whole tape being explosive.
    -We can do the brute force transitions of choosing every possible next fold we can make, it will sum up to around 8e7 operations for all dp states.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=1e3+1,mod=10301;
int add(int a,int b){
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int mul(int a,int b){
    return a*b%mod;
}
int dp[N][N];
int calc(int a,int n){
    if(n==0)
        return 1;
    if(dp[a][n]!=-1)
        return dp[a][n];
    dp[a][n]=0;
    for(int i=0;n-a-2*i>=0;i++)
        dp[a][n]=add(dp[a][n],calc(a+i,n-a-2*i));
    return dp[a][n];
}
int main()
{
    memset(dp,-1,sizeof(dp));
    int n,a,b,ans=0;
    scanf("%i %i %i",&n,&a,&b);
    n-=a+b;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n-i;j++)
            ans=add(ans,mul(calc(a,i),calc(b,j)));
    printf("%i\n",ans);
    return 0;
}
