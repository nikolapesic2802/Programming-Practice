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

const int N=2005,mod=1e9+7;
void add(int &a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
}
int dp[N][N],n;
string b;
int main()
{
	cin >> b;
	n=b.size();
	b='*'+b;
	int s,e;
	cin >> s >> e;
    dp[0][0]=1;
    for(int i=1,S=0,E=0;i<=n;i++){
        for(int j=1;j<=i;j++)
        {
            if(i==s)
            {
                if(b[i]!='L') add(dp[i][j],dp[i-1][j-1]);
                if(b[i]!='R') add(dp[i][j],dp[i-1][j]);
                continue;
            }
            if(i==e)
            {
                dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
                if(dp[i][j]>=mod)
                    dp[i][j]-=mod;
                continue;
            }
            if(b[i]!='L') add(dp[i][j],((ll)max(0,j-S-E)*dp[i-1][j-1] + (ll)(j-E)*dp[i-1][j])%mod);
            if(b[i]!='R') add(dp[i][j],((ll)j*dp[i-1][j+1]+(ll)(j-S)*dp[i-1][j])%mod);
        }
        if(i==s) S++;
        if(i==e) E++;
    }
    printf("%i\n",dp[n][1]);
    return 0;
}
