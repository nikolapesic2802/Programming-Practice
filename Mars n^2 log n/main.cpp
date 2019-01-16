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
const int K=9;
const int N=513;
int dist[N][N];
int dp[N][N];
int level[N];
vector<int> get(int prev,int nivo)
{
    //printf("Getujem %i %i\n",prev,nivo);
    int tr=prev;
    while(level[tr]<nivo)
        tr++;
    if(level[tr]==nivo)
    {
        int num=1<<(nivo-1);
        vector<int> sol;
        for(int i=1;i<=num;i++)
        {
            sol.pb(tr+i);
        }
        return sol;
    }
    tr=prev-1;
    while(level[tr]<nivo)
        tr--;
    assert(level[tr]==nivo);
    int num=1<<(nivo-1);
    vector<int> sol;
    for(int i=0;i<num;i++)
        sol.pb(tr-i);
    return sol;
}
int n;
int calc(int prev,int pos)
{
    if(pos==n+1)
        return 0;
    if(dp[prev][pos]!=-1)
        return dp[prev][pos];
    //printf("%i %i\n",prev,pos);
    int nivo=1,p=pos-1;
    while(p%2==0)
        p/=2,nivo++;
    vector<int> mog=get(prev,nivo);
    dp[prev][pos]=INT_MAX;
    for(auto p:mog)
    {
        dp[prev][pos]=min(dp[prev][pos],dist[prev][p]+calc(p,pos+1));
    }
    return dp[prev][pos];
}
int main()
{
    memset(dp,-1,sizeof(dp));
    int k;
    scanf("%i",&k);
    n=(int)pow(2,k);
    level[0]=100;
    for(int i=1;i<=n;i++)
    {
        int nivo=1,p=i;
        while(p%2==0)
            p/=2,nivo++;
        level[i]=nivo;
        //printf("%i: %i\n",i,nivo);
    }
    //level[n]=100;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%i",&dist[i][j]);
    int sol=INT_MAX;
    for(int i=1;i<=n;i++)
        sol=min(sol,calc(i,2));
    printf("%i\n",sol);
    return 0;
}
