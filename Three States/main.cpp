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
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
bool inside(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >> n>> m;
    vector<string> mat(n);
    for(int i=0;i<n;i++)
        cin >> mat[i];
    vector<vector<vector<int> > > dist(3,vector<vector<int> >(n,vector<int>(m,-1)));
    vector<queue<pair<int,int> > > q(3);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            if(mat[i][j]=='.'||mat[i][j]=='#')
                continue;
            dist[mat[i][j]-'1'][i][j]=0;
            q[mat[i][j]-'1'].push({i,j});
        }
    for(int k=0;k<3;k++)
    {
        while(q[k].size())
        {
            int x=q[k].front().f;
            int y=q[k].front().s;
            q[k].pop();
            for(int l=0;l<4;l++)
            {
                int xx=x+dx[l];
                int yy=y+dy[l];
                if(!inside(xx,yy)||dist[k][xx][yy]!=-1||mat[xx][yy]=='#')
                    continue;
                dist[k][xx][yy]=dist[k][x][y]+1;
                q[k].push({xx,yy});
            }
        }
    }
    int best=INT_MAX;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(dist[0][i][j]!=-1&&dist[1][i][j]!=-1&&dist[2][i][j]!=-1)
                best=min(best,dist[0][i][j]+dist[1][i][j]+dist[2][i][j]-2);
    vector<int> mindist(3,INT_MAX/2);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(dist[0][i][j]!=-1&&dist[1][i][j]!=-1)
                mindist[0]=min(mindist[0],dist[0][i][j]+dist[1][i][j]-1);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(dist[0][i][j]!=-1&&dist[2][i][j]!=-1)
                mindist[1]=min(mindist[1],dist[0][i][j]+dist[2][i][j]-1);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(dist[1][i][j]!=-1&&dist[2][i][j]!=-1)
                mindist[2]=min(mindist[2],dist[1][i][j]+dist[2][i][j]-1);
    for(int i=0;i<3;i++)
    {
        int d=0;
        for(int j=0;j<3;j++)
            if(i!=j)
                d+=mindist[j];
        best=min(best,d);
    }
    if(best>INT_MAX/5)
        printf("-1\n");
    else
        printf("%i\n",best);
    return 0;
}
