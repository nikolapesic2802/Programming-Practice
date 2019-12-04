/*
    -Find all divisors of n, there will be at most 6720.
    -Do dp[n][k]-number of decompositions using only divisors of index n and up and we still have to make the divisor of index k.
    -To get the index use a hash table.
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

vector<ll> divs;
vector<vector<int> > dp;
gp_hash_table<ll,int> mapa;
int calc(int tr,int koji){
    if(koji==-1){
        return 1;
    }
    if(tr>koji)
        return 0;
    if(dp[tr][koji]!=-1)
        return dp[tr][koji];
    dp[tr][koji]=calc(tr+1,koji);
    if(divs[koji]%divs[tr]==0)
        dp[tr][koji]+=calc(tr,mapa[divs[koji]/divs[tr]]);
    return dp[tr][koji];
}
int k;
vector<ll> sol;
void gen(int tr,int koji){
    if(koji==-1)
        return;
    if(divs[koji]%divs[tr]==0){
        int cnt=calc(tr,mapa[divs[koji]/divs[tr]]);
        if(cnt>=k)
        {
            sol.pb(divs[tr]);
            gen(tr,mapa[divs[koji]/divs[tr]]);
            return;
        }
        k-=cnt;
    }
    gen(tr+1,koji);
}
int main()
{
	freopen("desc.in","r",stdin);
	freopen("desc.out","w",stdout);
	ll n;
	scanf("%lld %i",&n,&k);
	for(ll int i=2;i*i<=n;i++){
        if(n%i==0){
            divs.pb(i);
            if(n/i!=i)
                divs.pb(n/i);
        }
	}
	sort(all(divs));
	divs.pb(n);
	int m=divs.size();
	for(int i=0;i<m;i++)
        mapa[divs[i]]=i;
    mapa[1]=-1;
	dp.resize(m,vector<int>(m,-1));
    printf("%i\n",calc(0,m-1));
    gen(0,m-1);
    for(auto p:sol)
        printf("%lld ",p);
    return 0;
}
