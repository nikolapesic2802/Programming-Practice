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
vector<string> mat;
vector<pair<int,pair<int,int> > > resorts;
const int N=20;
vector<pair<int,int> > graf[N][N];
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
int n,m;
bool inside(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
int broj[N][N];
int dist[14][14];
vector<int> dist_to_start;
int sx,sy;
int dp[14][1<<14];
int calc(int tr,int mask)
{
    if(tr==14)
    {
        assert(mask==0);
        dp[tr][mask]=0;
        for(int i=0;i<resorts.size();i++)
        {
            dp[tr][mask]=max(dp[tr][mask],-2*dist_to_start[i]+resorts[i].f+calc(i,mask|(1<<i)));
        }
        return dp[tr][mask];
    }
    if(dp[tr][mask]!=-1)
        return dp[tr][mask];
    dp[tr][mask]=-2*dist_to_start[tr];
    for(int i=0;i<resorts.size();i++)
    {
        if((mask&(1<<i))==0)
        {
            dp[tr][mask]=max(dp[tr][mask],-2*dist[tr][i]+resorts[i].f+calc(i,mask|(1<<i)));
        }
    }
    return dp[tr][mask];
}
int main()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            broj[i][j]=-2;
    for(int i=0;i<14;i++)
        for(int j=0;j<(1<<14);j++)
            dp[i][j]=-1;
	scanf("%i %i",&n,&m);
	mat.resize(n);
	for(int i=0;i<n;i++)
        cin >> mat[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            if(mat[i][j]=='~')
                continue;
            for(int k=0;k<4;k++)
            {
                int x=i+dx[k];
                int y=j+dy[k];
                if(!inside(x,y))
                    continue;
                if(mat[x][y]!='~')
                    graf[i][j].pb({x,y});
            }
            if(mat[i][j]>='2'&&mat[i][j]<='9')
            {
                broj[i][j]=resorts.size();
                resorts.pb({mat[i][j]-'0',{i,j}});
            }
            if(mat[i][j]=='C')
                sx=i,sy=j,broj[i][j]=-1;
        }
    for(int i=0;i<resorts.size();i++)
    {
        vector<vector<int> > visited(n,vector<int>(m));
        queue<pair<int,int> > q;
        visited[resorts[i].s.f][resorts[i].s.s]=1;
        q.push({resorts[i].s.f,resorts[i].s.s});
        while(q.size())
        {
            int x=q.front().f;
            int y=q.front().s;
            q.pop();
            if(broj[x][y]!=-2)
            {
                if(broj[x][y]==-1)
                   dist_to_start.pb(visited[x][y]-1);
                else
                    dist[i][broj[x][y]]=visited[x][y]-1;
            }
            for(auto p:graf[x][y])
            {
                if(visited[p.f][p.s]==0)
                {
                    visited[p.f][p.s]=visited[x][y]+1;
                    q.push({p.f,p.s});
                }
            }
        }
    }
    printf("%i\n",calc(14,0));
    return 0;
}
