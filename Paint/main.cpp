/*
    -Do dp[N][K] where N is the position we came to and K is the position in the array k we came to.
    -From a state we can do 2 transitions:
        Start the new chain of X's if the pattern allows it (can be checked with prefix sums) and if on the next space we can place a _ since we need to make a gap.
        Or just place a _ if possible
    -We can for each field record the biggest chain of X's that we can start at that chain and if we can place a _ or not and do line sweep to get the answer.
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

int n,m;
const int N=2e5+5;
int sum[N],cnt[2];
int getSum(int l,int r)
{
    int sol=sum[r];
    if(l)
        sol-=sum[l-1];
    return sol;
}
string st;
vector<int> k;
vector<pair<pair<int,int>,int> > e;
bool stavio[N];
int godDamnMemoryLimit[N];
short dp[N][101];
bool calc(int tr,int i)
{
    if(tr>=n)
        return i==m;
    if(dp[tr][i]!=-1)
        return dp[tr][i];
    dp[tr][i]=0;
    if(i<m&&n-tr>=k[i]&&getSum(tr,tr+k[i]-1)==0&&st[tr+k[i]]!='X')
        if(calc(tr+k[i]+1,i+1)){
            dp[tr][i]=1;
            if(godDamnMemoryLimit[tr]<k[i])
                godDamnMemoryLimit[tr]=k[i];
            if(!stavio[tr+k[i]])
                e.pb({{tr+k[i],1},0}),e.pb({{tr+1+k[i],-1},0}),stavio[tr+k[i]]=1;
        }
    if(st[tr]!='X'&&calc(tr+1,i)){
        dp[tr][i]=1;
        if(!stavio[tr])
            e.pb({{tr,1},0}),e.pb({{tr+1,-1},0}),stavio[tr]=1;
    }
    return dp[tr][i];
}
string solve_puzzle(string s,vector<int> c)
{
    memset(dp,-1,sizeof(dp));
    k=c;
    st=s;
    st+='_';
    n=s.size();
    m=c.size();
    for(int i=0;i<n;i++)
    {
        if(s[i]=='_')
            sum[i]++;
        if(i)
            sum[i]+=sum[i-1];
    }
    calc(0,0);
    for(int i=0;i<n;i++)
        if(godDamnMemoryLimit[i])
            e.pb({{i,1},1}),e.pb({{i+godDamnMemoryLimit[i],-1},1});
    string ans;
    sort(all(e));
    e.pb({{n,n},n});
    int j=0;
    for(int i=0;i<n;i++)
    {
        while(e[j].f.f==i)
            cnt[e[j].s]+=e[j].f.s,j++;
        if(cnt[0]==0)
            ans+='X';
        if(cnt[1]==0)
            ans+='_';
        if(cnt[0]!=0&&cnt[1]!=0)
            ans+='?';
    }
    return ans;
}

const int S_MAX_LEN = 200 * 1000;
char buf[S_MAX_LEN + 1];

int main() {
    assert(1 == scanf("%s", buf));
    std::string s = buf;
    int c_len;
    assert(1 == scanf("%d", &c_len));
    std::vector<int> c(c_len);
    for (int i = 0; i < c_len; i++) {
        assert(1 == scanf("%d", &c[i]));
    }
    std::string ans = solve_puzzle(s, c);


    printf("%s\n", ans.data());
    return 0;
}
