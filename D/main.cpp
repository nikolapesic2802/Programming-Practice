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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int n;
vector<int> niz(n);
vector<vector<int> > dp(1<<20,vector<int>(7,-1));
int calc(int mask,int ostalo)
{
    if(mask==(1<<n)-1)
        return 0;
    if(dp[mask][ostalo]!=-1)
        return dp[mask][ostalo];
    dp[mask][ostalo]=INT_MAX/2;
    for(int i=0;i<n;i++)
    {
        if((mask&(1<<i))==0)
        {
            int tr=max(1,niz[i]-ostalo);
            dp[mask][ostalo]=min(dp[mask][ostalo],tr+calc(mask|(1<<i),tr-1));
        }
    }
    return dp[mask][ostalo];
}
int main()
{
	scanf("%i",&n);
	niz.resize(n);
	for(int i=0;i<n;i++)
        scanf("%i",&niz[i]);
    printf("%i\n",calc(0,0));
    return 0;
}
