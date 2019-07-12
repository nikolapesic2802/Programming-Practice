/*
    -For some given strings its always optimal to place all the letters they have in common at the beginning.
    -For each mask we will calculate the number of common letters and the answer will be calc(subset mask)+calc(subset mask^mask)-number of common letters since we will count them twice.
    -To go over all subset mask we can use a for loop and the total complexity will be O(3^n)
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=16,L=26;
int dp[1<<N],cnt[N][L],n;
int calc(int mask)
{
    int c=__builtin_popcount(mask);
    if(dp[mask]!=-1)
        return dp[mask];
    vector<int> minn(L,INT_MAX);
    int total=0;
    for(int i=0;i<n;i++)
        if(mask&(1<<i))
            for(int j=0;j<L;j++)
                minn[j]=min(minn[j],cnt[i][j]),total+=cnt[i][j];
    int sum=0;
    for(auto p:minn)
        sum+=p;
    if(total%c==0&&total/c==sum)
        return dp[mask]=sum;
    dp[mask]=INT_MAX;
    for(int j=(mask-1)&mask;j;j=(j-1)&mask)
        dp[mask]=min(dp[mask],calc(j)+calc(j^mask)-sum);
    return dp[mask];
}
int main()
{
    memset(dp,-1,sizeof(dp));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for(int i=0;i<n;i++)
    {
        string s;
        cin >> s;
        for(auto p:s)
            cnt[i][p-'a']++;
    }
    cout << calc((1<<n)-1)+1 << endl;
    return 0;
}
