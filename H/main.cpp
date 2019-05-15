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

int n,m,ax1,ay1,ax2,ay2,bx1,by1,bx2,by2;
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
bool inside(int x,int y)
{
    return x>=0&&x<=n&&y>=0&&y<=m;
}
int solve()
{
    vector<vector<int> > oznaka(n+1,vector<int>(m+1));
    int visited[n+1][m+1][8];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k=0;k<8;k++)
                visited[i][j][k]=0;
    int x=ax1,y=ay1,dist=0;
    while(x!=ax2)
    {
        dist++;
        oznaka[x][y]|=1;
        if(x<ax2)
            x++;
        else
            x--;
    }
    while(y!=ay2)
    {
        dist++;
        oznaka[x][y]|=1;
        if(y<ay2)
            y++;
        else
            y--;
    }
    oznaka[x][y]=7;
    while(x!=ax1)
    {
        oznaka[x][y]|=2;
        if(x<ax1)
            x++;
        else
            x--;
    }
    while(y!=ay1)
    {
        oznaka[x][y]|=2;
        if(y<ay1)
            y++;
        else
            y--;
    }
    oznaka[x][y]=7;
    for(int i=min(ax1,ax2)+1;i<max(ax1,ax2);i++)
        for(int j=min(ay1,ay2)+1;j<max(ay1,ay2);j++)
            oznaka[i][j]|=4;
    queue<pair<pair<int,int>,int> > q;
    q.push({{bx1,by1},oznaka[bx1][by1]});
    visited[bx1][by1][oznaka[bx1][by1]]=1;
    while(q.size())
    {
        int x=q.front().f.f,y=q.front().f.s,oz=q.front().s;
        q.pop();
        for(int k=0;k<4;k++)
        {
            int xx=x+dx[k],yy=y+dy[k];
            if(!inside(xx,yy))
                continue;
            int novioz=oz|oznaka[xx][yy];
            if(visited[xx][yy][novioz])
                continue;
            visited[xx][yy][novioz]=visited[x][y][oz]+1;
            q.push({{xx,yy},novioz});
        }
    }
    int sol=INT_MAX/2;
    for(int i=0;i<7;i++)
    {
        if(i==3)
        {
            int dx=abs(ax1-ax2),dy=abs(ay1-ay2);
            if(dx<2||dy<2)
                continue;
            else
                if(visited[bx2][by2][i]!=0)
                    sol=min(sol,visited[bx2][by2][i]);
        }
        else
            if(visited[bx2][by2][i]!=0)
                sol=min(sol,visited[bx2][by2][i]);
    }
    return sol+dist-1;
}
void test()
{
    scanf("%i %i %i %i %i %i %i %i %i %i",&n,&m,&ax1,&ay1,&ax2,&ay2,&bx1,&by1,&bx2,&by2);
    int sol=INT_MAX;
    sol=min(sol,solve());
    swap(ax1,bx1);
    swap(ay1,by1);
    swap(ax2,bx2);
    swap(ay2,by2);
    sol=min(sol,solve());
    if(sol>INT_MAX/4)
    {
        if(ax1==ax2&&bx1==bx2&&ax1==bx1&&ax1!=0&&ax1!=n)
            sol=min(sol,abs(ay1-ay2)+abs(by1-by2)+4);
        if(ay1==ay2&&by1==by2&&ay1==by1&&ay1!=0&&ay1!=m)
            sol=min(sol,abs(ax1-ax2)+abs(bx1-bx2)+4);
    }
    if(sol>INT_MAX/4)
        printf("IMPOSSIBLE\n");
    else
        printf("%i\n",sol);
}
int main()
{
	int t;
	scanf("%i",&t);
	while(t--)
        test();
    return 0;
}
