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
const int mod=10007;
int dp[51][50][50][2];
int ways[51][50][50];
void add(int &a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
}
void mul(int &a,int b)
{
    a=(ll)a*b%mod;
}
int main()
{
	int n,e,K;
	scanf("%i %i %i\n",&n,&e,&K);
	vector<int> road[n];
	vector<int> load[26][n],offload[26][n];
	for(int i=0;i<e;i++)
    {
        string c;
        getline(cin,c);
        for(int j=0;j<2;j++)
            c+=' ';
        //cout << c;
        int tr=0;
        int x=c[tr]-'0';tr++;
        if(c[tr]!=' ')
            x=x*10+c[tr]-'0',tr++;
        tr++;
        int y=c[tr]-'0';tr++;
        if(c[tr]!=' ')
            y=y*10+c[tr]-'0',tr++;
        tr++;
        x--;
        y--;
        if(c[tr]==' ')
        {
            road[x].pb(y);
            continue;
        }
        if(c[tr]>='A'&&c[tr]<='Z')
            load[c[tr]-'A'][x].pb(y);
        else
            offload[c[tr]-'a'][y].pb(x);
        x=-1;
    }
    for(int i=0;i<n;i++)
        dp[0][i][i][0]=1,dp[0][i][i][1]=1;
    int sol=0;
    for(int k=1;k<=K;k++)
    {
        if(k>=2)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    for(int t=0;t<26;t++)
                        for(auto p:load[t][i])
                            for(auto d:offload[t][j])
                                add(ways[k][i][j],dp[k-2][p][d][0]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int f=0;f<2;f++)
                {
                    for(auto p:road[i])
                        add(dp[k][i][j][f],dp[k-1][p][j][f]);
                    if(f)
                    {
                        for(int t=0;t<26;t++)
                            for(auto p:load[t][i])
                                add(dp[k][i][j][f],dp[k-1][p][j][f]);
                    }
                    for(int t=2;t<=k;t++)
                        for(int x=0;x<n;x++)
                            add(dp[k][i][j][f],(ll)ways[t][i][x]*dp[k-t][x][j][f]%mod);
                }
        add(sol,dp[k][0][n-1][1]);
    }
    printf("%i\n",sol);
    return 0;
}
